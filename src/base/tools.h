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

int getPath(const sf::Vector2i& pos);

int getLength(const sf::Vector2i& pos);

sf::Vector2i pos2axis(const sf::Vector2i& pos);

sf::Vector2i axis2pos(const sf::Vector2i& axis);

} // namespace demo