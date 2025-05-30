#include <base/tools.hpp>
#include <iostream>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

using namespace std;

namespace demo {

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
    auto inter =
        duration_cast<milliseconds>(nowTime - last_update_time());

    if(inter >= internal()) {
        last_update_time() = nowTime;
        return;
    }
    cout << "sleep: "
         << duration_cast<milliseconds>(internal() - inter).count()
         << "ms" << std::endl;
    sf::sleep(internal() - inter);
    last_update_time() = getNowTime();
}

int getPath(const PositionType& pos)
{
    return (pos.y - GRASS_START_Y) / GRASS_WIDE;
}

int getLength(const sf::Vector2i& pos)
{
    return pos.x - GRASS_START_X;
}

sf::Vector2i pos2axis(const PositionType& pos)
{

    return sf::Vector2i(
        (pos - PositionType(GRASS_START_X, GRASS_START_Y))
            .componentWiseDiv({GRASS_LENGTH, GRASS_WIDE})
    );
}

PositionType axis2pos(const sf::Vector2i& axis)
{
    return PositionType(
        axis.componentWiseMul({GRASS_LENGTH, GRASS_WIDE})
        + sf::Vector2i(GRASS_START_X, GRASS_START_Y)
    );
}

} // namespace demo