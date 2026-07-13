#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <functional>
#include <type_traits>
#include <stdexcept>
#include <utility>

class ThreadPool {
public:
    explicit ThreadPool(size_t threads);

    ~ThreadPool();

    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    std::vector<std::thread> workers;

    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;

    std::condition_variable condition;

    bool stop;
};

template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)
    -> std::future<typename std::invoke_result<F, Args...>::type>
{
    using ReturnType = typename std::invoke_result<F, Args...>::type;

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<ReturnType> result = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex);

        if(stop)
            throw std::runtime_error("submit on stopped ThreadPool");

        tasks.emplace([task]() {
            (*task)();
        });
    }

    condition.notify_one();

    return result;
}

#endif