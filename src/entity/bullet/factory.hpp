#pragma once

#include <unordered_map>

#include <entity/bullet/bullet.hpp>

namespace demo {

class BulletFactory
{
public:
    BulletFactory()
    {
        // read json
        // init m_data
    }
    ~BulletFactory() = default;

    // FIXME: 后续参考component改成枚举
    Bullet* create(const std::string& type)
    {
        if(m_data.count(type) == 0) {
            return nullptr;
        }
        return new Bullet(m_data[type]);
    }

    static BulletFactory* getFactory()
    {
        BulletFactory factory;
        return &factory;
    }

private:
    std::unordered_map<std::string, BulletData> m_data;
};

} // namespace demo