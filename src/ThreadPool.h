#ifndef CXX_PRACTICE_THREAD_POOL_H
#define CXX_PRACTICE_THREAD_POOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <vector>
#include <queue>

template< typename T >
class TaskQueue
{
public:
    inline T getFront() // queue must not empty
    {
        T f = std::move(tasks.front());
        tasks.pop();
        return std::move(f);
    }

    // getFront and empty should be used with mutex
    inline bool empty()
    {
        return tasks.empty();
    }

    inline void emplace(T&& task)
    {
        std::lock_guard< std::mutex > lk(mtx);
        tasks.emplace(std::forward< T >(task));
    }

    inline void emplace(T&& task, bool& stop)
    {
        std::lock_guard< std::mutex > lk(mtx);
        if(!stop)
        {
            tasks.emplace(std::forward< T >(task));
        }
    }

    inline void clean()
    {
        std::lock_guard< std::mutex > lk(mtx);
        tasks = std::queue< T >();
    }

    inline std::unique_lock< std::mutex > getLock()
    {
        return std::move(std::unique_lock< std::mutex >(mtx));
    }

    inline void wait(std::unique_lock< std::mutex >& lk)
    {
        cond.wait(lk);
    }

    inline void notify_one()
    {
        cond.notify_one();
    }

    inline void notify_all()
    {
        cond.notify_all();
    }

private:
    std::mutex mtx;
    std::condition_variable cond;
    std::queue< T > tasks;
};

class ThreadPool
{
public:
    explicit ThreadPool(size_t num_threads)
        : stop(false)
    {
        for(size_t i = 0; i < num_threads; ++i)
        {
            threads.emplace_back(std::thread(
            [&]() {
                std::unique_lock< std::mutex > lk(tq.getLock());
                while(true)
                {
                    if(!tq.empty())
                    {
                        std::function< void() > task = tq.getFront();
                        lk.unlock();
                        task();
                        lk.lock();
                    }
                    else if(stop)
                    {
                        break;
                    }
                    else
                    {
                        tq.wait(lk);
                    }
                }
            }));
        }
    }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    ~ThreadPool()
    {
        {
            std::unique_lock< std::mutex > lk(tq.getLock());
            stop = true;
        }

        tq.notify_all();

        for(auto& t : threads)
        {
            if(t.joinable())
            {
                t.join();
            }
        }
    }

    template< typename F, typename... Args >
    auto execute(F&& f, Args&&... args)
        -> std::future< decltype(f(args...)) >
    {
        using rtype = decltype(f(args...));
        
        auto taskPtr = std::make_shared< std::packaged_task< rtype() > >(
            std::bind(std::forward< F >(f), std::forward< Args >(args)...));

        tq.emplace([taskPtr]() { (*taskPtr)(); }, stop);

        tq.notify_one();

        return taskPtr->get_future();
    }

    void clean()
    {
        tq.clean();
    }

private:
    bool stop;
    TaskQueue< std::function< void() > > tq;
    std::vector< std::thread > threads;
};

#endif // CXX_PRACTICE_THREAD_POOL_H