#pragma once

#include "TaskQueue.hpp"

#include <cstddef>

#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <type_traits>
#include <concepts>
#include <condition_variable>

namespace fatpound::concurrency
{
    /// @brief A thread pool for managing and executing tasks concurrently
    ///
    class ThreadPool final
    {
    public:
        explicit ThreadPool(std::size_t threadCount = std::thread::hardware_concurrency());

        explicit ThreadPool(const ThreadPool&)     = delete;
        explicit ThreadPool(ThreadPool&&) noexcept = delete;
        auto operator = (const ThreadPool&)     -> ThreadPool& = delete;
        auto operator = (ThreadPool&&) noexcept -> ThreadPool& = delete;
        ~ThreadPool() noexcept;


    public:
        template <typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto Submit(F&& func, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
        {
            auto future = m_tasks_.Push(std::forward<F>(func), std::forward<Args>(args)...);

            {
                const std::lock_guard<std::mutex> sl{ m_mtx_ };
            }

            m_cv_.notify_one();

            return future;
        }


    protected:


    private:
        void WorkerLoop_();


    private:
        TaskQueue                   m_tasks_;
        std::vector<std::jthread>   m_workers_;

        std::mutex                  m_mtx_;
        std::condition_variable     m_cv_;
        bool                        m_stop_{};
    };
}
