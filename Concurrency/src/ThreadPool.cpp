#include "ThreadPool.hpp"

#if __cplusplus >= 202302L
#include <print>
#else
#include <iostream>
#endif

namespace fatpound::concurrency
{
    ThreadPool::ThreadPool(const std::size_t threadCount)
    {
        m_workers_.reserve(threadCount);

        for (std::size_t i{ 0U }; i < threadCount; ++i)
        {
            m_workers_.emplace_back(
                [this]() -> void
                {
                    WorkerLoop_();
                }
            );
        }
    }
    ThreadPool::~ThreadPool() noexcept
    {
        {
            const std::lock_guard<std::mutex> sl{ m_mtx_ };

            m_stop_ = true;
        }

        m_cv_.notify_all();
    }


    void ThreadPool::WorkerLoop_()
    {
        while (true)
        {
            {
                std::unique_lock<std::mutex> ulock{ m_mtx_ };

                m_cv_.wait(
                    ulock,
                    [this]() -> bool
                    {
                        return m_stop_ or not m_tasks_.Empty();
                    }
                );

                if (m_stop_ and m_tasks_.Empty())
                {
                    return;
                }
            }

            try
            {
                m_tasks_.PopAndExecute();
            }
            catch (...)
            {
#if __cplusplus >= 202302L
                std::println<>("Thread {} failed while running task!", std::this_thread::get_id());
#else
                std::cout << "Thread " << std::this_thread::get_id() << " failed while running task!";
#endif
            }
        }
    }
}
