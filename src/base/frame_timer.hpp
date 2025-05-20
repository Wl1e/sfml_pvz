/**
 * 单纯把timer.hpp的东西拷贝过来做了部分修改
 *
 */

#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_set>

#include <entity/frame.hpp>

namespace demo {

const int max_timer_size = 1000;

using TimerID = uint64_t;
static TimerID tID = 0;

using FramePoint = Frame;

using TimerCallback = std::function<void()>;

struct FrameTimer
{
    TimerID id;
    FramePoint timeout;
    TimerCallback cb;
    FrameInterval interval;
    FrameTimer(
        FramePoint point, TimerCallback callback, FrameInterval ti
    ) :
        id(++tID), timeout(point), cb(std::move(callback)),
        interval(ti)
    {
    }

    void update(const FramePoint& nowFrame)
    {
        timeout = nowFrame + interval;
    }
};

#define OPERATOR(x)                                             \
    bool operator x(const FrameTimer& t1, const FrameTimer& t2) \
    {                                                           \
        return t1.timeout x t2.timeout;                         \
    }

OPERATOR(>)
OPERATOR(<)
OPERATOR(>=)
OPERATOR(<=)
OPERATOR(==)
OPERATOR(!=)

class FrameTimerQueue
{

public:
    ~FrameTimerQueue() = default;

    TimerID addTimer(
        FrameInterval timeout,
        TimerCallback cb,
        FrameInterval interval
    )
    {
        if(!_checkTimer()) {
            return 0;
        }

        if(timeout == 0) {
            cb();
            if(interval > 0) {
                addTimer(interval, cb, interval);
            }
        }

        auto now = FrameManager::getInstance().getFrame();
        auto newTimer = std::make_shared<FrameTimer>(
            now + timeout, cb, interval
        );
        _addTimerToQueue(newTimer);

        return newTimer->id;
    }

    void delTimer(TimerID id)
    {
        m_id_set.erase(id);
    }

    void update()
    {
        if(m_queue.empty()) {
            return;
        }
        auto now = FrameManager::getInstance().getFrame();
        if(m_queue.top()->timeout > now) {
            return;
        }

        while(!m_queue.empty()) {
            auto timer = m_queue.top();
            if(m_id_set.find(timer->id) == m_id_set.end()) {
                m_queue.pop();
                continue;
            }
            if(timer->timeout > now) {
                return;
            }
            m_queue.pop();
            timer->cb();
            if(timer->interval != 0) {
                timer->update(now);
                m_queue.push(timer);
            }
        }
    }

    void reset()
    {
        m_id_set.clear();
        std::priority_queue<std::shared_ptr<FrameTimer>> tmp;
        m_queue.swap(tmp);
        // tID = 0; ?
    }

    static FrameTimerQueue& getInstance()
    {
        static FrameTimerQueue frameTimerQueue;
        return frameTimerQueue;
    }

private:
    FrameTimerQueue() = default;

    bool _checkTimer()
    {
        return m_id_set.size() <= max_timer_size;
    }

    void _addTimerToQueue(std::shared_ptr<FrameTimer> timer)
    {
        m_queue.push(timer);
        m_id_set.insert(timer->id);
    }

private:
    std::priority_queue<std::shared_ptr<FrameTimer>> m_queue;
    std::unordered_set<TimerID> m_id_set;
};

} // namespace demo