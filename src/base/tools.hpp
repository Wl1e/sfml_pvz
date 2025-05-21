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
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::system_clock;

using TimerPoint = std::chrono::system_clock::time_point;
using TimerInterval = std::chrono::milliseconds;

bool isZero(TimerInterval interval);

TimerPoint& last_update_time();

TimerInterval& internal();

TimerPoint getNowTime();

void wait();

// 我是真不知道该用Vector2i、Vector2u还是Vector2f
using PositionType = sf::Vector2f;
using SizeType = sf::Vector2f;

int getPath(const PositionType& pos);

int getLength(const PositionType& pos);

sf::Vector2i pos2axis(const sf::Vector2f& pos);

sf::Vector2f axis2pos(const sf::Vector2i& axis);

template<class srcT, class dstT>
dstT* castTo(srcT* src)
{
    return dynamic_cast<dstT*>(src);
}

} // namespace demo