#ifndef CXX_PRACTICE_CHAIN_H
#define CXX_PRACTICE_CHAIN_H

#include "ThreadPool.h"

template< typename T >
class Chain;

template< typename R, typename... Args >
class Chain< R(Args...) >
{
public:
    using TFunc = std::function< R(Args...) >;

    Chain(const TFunc& f)
    {
        inFunc = std::make_shared< TFunc >(f);
    }

    Chain(TFunc&& f) 
    {
        inFunc = std::make_shared< TFunc >(std::move(f));
    }

    template< typename F >
    Chain& SetFunc(F&& f)
    {
        mFunc = std::forward< F >(f);
        return (*this);
    }

    std::future< R > Run(Args&&... args)
    {
        if(!mFunc)
        {
            mPool.execute(
                [this](Args&&... args) 
                {
                    auto task = std::packaged_task< R(Args...) >(*inFunc);
                    task(std::forward< Args >(args)...);
                    result = task.get_future(); 
                }, 
                std::forward< Args >(args)...);
        }
        else
        {
            mPool.execute(mFunc, std::forward< Args >(args)...);
        }
        
        return std::move(result);
    }

    template< typename F >
    auto Then(F&& f)
        -> Chain< typename std::result_of< F(R) >::type(Args...) >
    {
        using rtype = typename std::result_of< F(R) >::type;

        F _inFunc(std::forward< F >(f)); // function< rtype(R) >

        *inFunc = [_inFunc, this](Args&&... args) {
            R value = (*inFunc)(std::forward< Args >(args)...);
            result = mPool.execute(_inFunc, value);
            return value;
        };

        if(!mFunc)
        {
            mFunc = *inFunc;
        }

        Chain< rtype(Args...) > chain(_inFunc);
        chain.SetFunc(mFunc);

        return std::move(chain);
    }

private:
    std::shared_ptr< TFunc > inFunc;
    TFunc mFunc;
    std::future< R > result;
    static ThreadPool mPool;
};

template< typename R, typename... Args >
ThreadPool Chain< R(Args...) >::mPool(1);

#endif // CXX_PRACTICE_CHAIN_H