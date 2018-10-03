#ifndef CXX_PRACTICE_CHAIN_H
#define CXX_PRACTICE_CHAIN_H

#include "ThreadPool.h"

#include <iostream>
#include <type_traits>

template< typename T >
class Chain;

template< typename R, typename... Args >
class Chain< R(Args...) >
{
public:
    using TFunc = std::function< R(Args...) >;
    using MFunc = std::function< std::future< R >(Args...) >;

    Chain(const TFunc& f)
    {
        mPool = std::make_shared< ThreadPool >(1);
        mFunc = std::make_shared< MFunc >(
            [=](Args&&... args) {
                return mPool->execute(f, 
                                      std::forward< Args >(args)...);
            }
        );
    }

    Chain(TFunc&& f)
    {
        mPool = std::make_shared< ThreadPool >(1);
        mFunc = std::make_shared< MFunc >(
            [=](Args&&... args) {
                return mPool->execute(std::move(f), 
                                      std::forward< Args >(args)...);
            }
        );
    }

    Chain(const MFunc& f, std::shared_ptr< ThreadPool > pool)
        : mPool(pool)
    {
        mFunc = std::make_shared< MFunc >(f);
    }

    Chain(MFunc&& f, std::shared_ptr< ThreadPool > pool)
        : mPool(pool)
    {
        mFunc = std::make_shared< MFunc >(std::move(f));
    }

    std::future< R > Run(Args&&... args)
    {
        return (*mFunc)(std::forward< Args >(args)...);
    }

    template< typename F >
    auto Then(F&& f)
        -> Chain< typename std::result_of< F(R) >::type(Args...) >
    {
        using rtype = typename std::result_of< F(R) >::type;

        return Chain< rtype(Args...) >(
            [=](Args&&... args) {
                std::future< R > prev = (*mFunc)(std::forward< Args >(args)...);
                return mPool->execute(Convert(f), prev.share());
            }, mPool);
    }

    template< typename M >
    class Converter
    {
    public:
        template< typename F >
        static auto cast(F&& f)
            -> std::function< typename std::result_of< F(M) >::type(std::shared_future< M >) >
        {
            return [f](std::shared_future< M > p) {
                return f(p.get());
            };
        }
    };

    template<>
    class Converter< void >
    {
    public:
        template< typename F >
        static auto cast(F&& f)
            -> std::function< typename std::result_of< F(void) >::type(std::shared_future< void >) >
        {
            return [f](std::shared_future< void > p) {
                p.get();
                return f();
            };
        }
    };

    template< typename F >
    auto Convert(F&& f)
        -> std::function< typename std::result_of< F(R) >::type(std::shared_future< R >) >
    {
        return Converter< R >::cast(std::forward< F >(f));
    }

private:
    std::shared_ptr< MFunc > mFunc;
    std::shared_ptr< ThreadPool > mPool;
};

#endif // CXX_PRACTICE_CHAIN_H