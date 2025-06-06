#pragma once

#include <memory>
#include <unordered_map>

#include <entity/bullet/bullet.hpp>

namespace demo {

class BulletFactory
{
public:
    ~BulletFactory() = default;

    // FIXME: 后续参考component改成枚举
    Bullet* create(const std::string&, const PlantSupport&);

    static BulletFactory* getFactory()
    {
        static BulletFactory factory;
        return &factory;
    }

private:
    explicit BulletFactory();

private:
    std::unordered_map<std::string, std::unique_ptr<BulletSupport>>
        m_data;
};

} // namespace demo