#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_set>

#include <base/tools.h>

namespace demo {

const int max_timer_size = 1000;

using TimerID = uint64_t;
static TimerID tID = 0;

using TimerCallback = std::function<void()>;

struct Timer
{
    TimerID id;
    TimerPoint timeout;
    TimerCallback cb;
    TimerInterval interval;
    Timer(
        const TimerPoint& point,
        TimerCallback callback,
        const TimerInterval& ti
    ) :
        id(++tID), timeout(point), cb(std::move(callback)),
        interval(ti)
    {
    }

    void update(const TimerPoint& now)
    {
        timeout = now + interval;
    }
};

#define OPERATOR(x)                                   \
    bool operator x(const Timer& t1, const Timer& t2) \
    {                                                 \
        return t1.timeout x t2.timeout;               \
    }

OPERATOR(>)
OPERATOR(<)
OPERATOR(>=)
OPERATOR(<=)
OPERATOR(==)

class TimerQueue
{

public:
    TimerID addTimer(
        TimerInterval timeout,
        TimerCallback cb,
        TimerInterval interval
    )
    {
        if(!checkTimer()) {
            return 0;
        }
        if(timeout <= 0ms) {
            cb();
            if(interval > 0ms) {
                addTimer(interval, cb, interval);
            }
            return 0;
        }

        auto now = getNowTime();
        auto newTimer =
            std::make_shared<Timer>(now + timeout, cb, interval);
        addTimerToQueue(newTimer);

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
        auto now = getNowTime();
        if(m_queue.top()->timeout > now) {
            return;
        }

        while(!m_queue.empty()) {
            auto timer = m_queue.top();
            if(m_id_set.count(timer->id) == 0) {
                m_queue.pop();
                continue;
            }
            if(timer->timeout > now) {
                return;
            }
            m_queue.pop();
            timer->cb();
            if(timer->interval > 0ms) {
                timer->update(now);
                m_queue.push(timer);
            }
        }
    }

    void reset()
    {
        m_id_set.clear();
        std::priority_queue<std::shared_ptr<Timer>> tmp;
        m_queue.swap(tmp);
        // tID = 0; ?
    }

private:
    bool checkTimer()
    {
        return m_id_set.size() <= max_timer_size;
    }

    void addTimerToQueue(std::shared_ptr<Timer> timer)
    {
        m_queue.push(timer);
        m_id_set.insert(timer->id);
    }

private:
    std::priority_queue<std::shared_ptr<Timer>> m_queue;
    std::unordered_set<TimerID> m_id_set;
};

} // namespace demo