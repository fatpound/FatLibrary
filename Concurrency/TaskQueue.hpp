#pragma once

#if FAT_BUILDING_WITH_MSVC

#include <deque>
#include <future>
#include <functional>

namespace fatpound::concurrency
{
	class TaskQueue final
    {
        using WrappedTask = std::move_only_function<void()>;

    public:
        explicit TaskQueue()                     = default;
        explicit TaskQueue(const TaskQueue&)     = delete;
        explicit TaskQueue(TaskQueue&&) noexcept = delete;

        auto operator = (const TaskQueue&)     -> TaskQueue& = delete;
        auto operator = (TaskQueue&&) noexcept -> TaskQueue& = delete;
        ~TaskQueue() noexcept                                = default;


    public:
        void ExecuteFirstAndPopOff()
        {
            WrappedTask wtask{};

            {
                const std::lock_guard lck{ m_mtx_ };

                wtask = std::move<>(m_tasks_.front());

                m_tasks_.pop_front();
            }

            wtask();
        }


    public:
        template <typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto Push(F&& func, Args&&... args) -> auto
        {
            using T = std::invoke_result_t<F, Args...>;

            auto pkgTask = std::packaged_task<T(Args...)>{ std::bind<>(std::forward<F>(func), std::forward<Args>(args)...) };
            auto future = pkgTask.get_future();

            Push_([&, task = std::move<>(pkgTask)]() mutable -> void { static_cast<void>(task(args...)); });

            return future;
        }


    protected:


    private:
        void Push_(WrappedTask wtask)
        {
            const std::lock_guard lck{ m_mtx_ };

            m_tasks_.push_back(std::move<>(wtask));
        }


    private:
        std::deque<WrappedTask> m_tasks_;

        std::mutex m_mtx_;
    };
}

#endif
