#pragma once

#include <SFML/System/Vector2.hpp>

namespace demo {

class Direction
{
public:
    enum class DIR
    {
        STOP = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,

    };

    Direction() = delete;
    Direction(DIR dir) :
        m_dir(Direction::mask[static_cast<int>(dir)])
    {
    }
    explicit Direction(const sf::Vector2i& dir) :
        m_dir(dir.normalized())
    {
    }

    void setDir(const sf::Vector2i& dir)
    {
        m_dir = dir.normalized();
    }
    void setDir(DIR dir)
    {
        m_dir = Direction::mask[static_cast<int>(dir)];
    }

    const sf::Vector2i& getOffset() const
    {
        return m_dir;
    }

private:
    sf::Vector2i m_dir;

    static sf::Vector2i mask[];
};

} // namespace demo