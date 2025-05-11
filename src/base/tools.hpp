#pragma once

#include <chrono>
#include <cstdint>
#include <thread>

#include <SFML/System/Vector2.hpp>

#include <defines.h>

namespace demo {

using namespace std::chrono_literals;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::system_clock;

using TimerPoint = std::chrono::system_clock::time_point;
using TimerInterval = std::chrono::milliseconds;

bool isZero(TimerInterval interval)
{
    return interval == system_clock::duration::zero();
}

TimerPoint& last_update_time()
{
    static TimerPoint last_update_time(
        system_clock::duration::zero()
    );
    return last_update_time;
}

TimerInterval& internal()
{
    static TimerInterval internal = 0ms;
    return internal;
}

TimerPoint getNowTime()
{
    return system_clock::now();
}

void wait()
{
    if(isZero(internal())) {
        last_update_time() = getNowTime();
        return;
    }
    auto nowTime = getNowTime();
    auto inter = nowTime - last_update_time();
    last_update_time() = nowTime;
    if(inter >= internal()) {
        return;
    }
    std::this_thread::sleep_for(inter);
}

int getPath(const sf::Vector2i& pos)
{
    return (pos.x - grass_start_x) / grass_length;
}

int getLength(const sf::Vector2i& pos)
{
    return pos.y - grass_start_y;
}

sf::Vector2i pos2axis(const sf::Vector2i& pos)
{
    return (pos - sf::Vector2i(grass_start_x, grass_start_y))
        .componentWiseDiv({grass_length, grass_wide});
}

} // namespace demo