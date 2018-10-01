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
        
        std::function< rtype(std::future< R >) > inFunc = 
            [f](std::future< R > p) {
                return f(p.get());
            };

        std::function< std::future< rtype >(Args...) > mFunc_ = 
            [=](Args&&... args) {
                std::future< R > prev = (*mFunc)(std::forward< Args >(args)...);
                return mPool->execute(inFunc, std::move(prev));
            };

        return Chain< rtype(Args...) >(mFunc_, mPool);
    }

private:
    std::shared_ptr< MFunc > mFunc;
    std::shared_ptr< ThreadPool > mPool;
};

#endif // CXX_PRACTICE_CHAIN_H