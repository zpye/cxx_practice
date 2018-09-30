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

    Chain(const TFunc& f, bool _noThen = true)
        : noThen(_noThen) 
    {
        mFunc = std::make_shared< TFunc >(f);
    }

    Chain(TFunc&& f, bool _noThen = true)
        : noThen(_noThen)
    {
        mFunc = std::make_shared< TFunc >(std::move(f));
    }

    Chain& SetThreadPool(std::shared_ptr< ThreadPool > pool)
    {
        mPool = pool;
    }

    std::future< R > Run(Args&&... args)
    {
        if(!mPool)
        {
            mPool = std::make_shared< ThreadPool >(1);
        }

        if(noThen) // without then
        {
            return mPool->execute(*mFunc, std::forward< Args >(args)...);
        }
        else
        {
            return (*mFunc)(std::forward< Args >(args)...);
        }
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

        std::shared_ptr< ThreadPool > mPool_ = mPool;
        
        if(noThen)
        {
            std::shared_ptr< TFunc > mFunc__ = mFunc;
            std::shared_ptr< std::function< std::future< R >(Args...) > > mFunc_ = 
            std::make_shared< std::function< std::future< R >(Args...) > >(
                [mFunc__, mPool_](Args&&... args) {
                    return mPool_->execute(mFunc__, std::forward< Args >(args)...);
                }
            );

            return Chain< std::future< rtype >(Args...) >(
                [mFunc_, inFunc, mPool_](Args&&... args) {
                    std::future< R > prev = (*mFunc_)(std::forward< Args >(args)...);
                    return mPool_->execute(inFunc, std::move(prev));
                }, false).SetThreadPool(mPool_);
        }
        else
        {
            std::shared_ptr< TFunc > mFunc_ = mFunc;

            return Chain< std::future< rtype >(Args...) >(
                [mFunc_, inFunc, mPool_](Args&&... args) {
                    std::future< R > prev = (*mFunc_)(std::forward< Args >(args)...);
                    return mPool_->execute(inFunc, std::move(prev));
                }, false).SetThreadPool(mPool_);
        }
    }

private:
    std::shared_ptr< TFunc > mFunc;
    std::shared_ptr< ThreadPool > mPool;
    bool noThen;
};

#endif // CXX_PRACTICE_CHAIN_H