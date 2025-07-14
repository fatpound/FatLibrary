#include "TaskQueue.hpp"

namespace fatpound::concurrency
{
    void TaskQueue::ExecuteFirstAndPopOff()
    {
        WrappedTask wtask{};

        {
            const std::lock_guard<std::mutex> lck{ m_mtx_ };

            if (m_tasks_.empty())
            {
                return;
            }

            wtask = std::move<>(m_tasks_.front());

            m_tasks_.pop_front();
        }

        wtask();
    }


    void TaskQueue::Push_(WrappedTask wtask)
    {
        const std::lock_guard<std::mutex> lck{ m_mtx_ };

        m_tasks_.push_back(std::move<>(wtask));
    }
}