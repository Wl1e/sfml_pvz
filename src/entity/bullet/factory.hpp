#pragma once

#include <unordered_map>

#include <entity/bullet/bullet.hpp>

namespace demo {

class BulletFactory
{
public:
    BulletFactory()
    {
        m_data["Pea"] = new BulletData{
            100,
            sf::Vector2i(100, 100),
            Direction::DIR::RIGHT,
            10000,

            sf::Vector2u(10, 10),
            false,
            1,
            "/home/wlle/code/demo/sfml2/resource/sun"
        };
    }
    ~BulletFactory() = default;

    // FIXME: 后续参考component改成枚举
    Bullet* create(const std::string& type)
    {
        if(m_data.find(type) == m_data.end()) {
            return nullptr;
        }
        return new Bullet(*m_data[type]);
    }

    static BulletFactory* getFactory()
    {
        static BulletFactory factory;
        return &factory;
    }

private:
    std::unordered_map<std::string, BulletData*> m_data;
};

} // namespace demo