#include <animation/gamescene.hpp>
#include <base/tools.hpp>
#include <entity/tool/zombie_creator.hpp>
#include <entity/zombie/factory.hpp>
#include <UI/defines.hpp>

using namespace std;
using namespace demo;

int getRandomPath()
{
    return randomInt(0, UI_DEFINE::GRASS_PATH);
}

static vector<string> ZOMBIE_TYPE{
    "NormalZombie",
};

const string& getRandomZombie()
{
    return ZOMBIE_TYPE[randomInt(0, ZOMBIE_TYPE.size() - 1)];
}

bool ZombieCreator::_validCreate() const
{
    return m_cd.valid();
}

void ZombieCreator::update()
{
    m_cd.update();
    if(!_validCreate()) {
        return;
    }
    m_cd.reset();

    _createZombie("NormalZombie", getRandomPath());
}

void ZombieCreator::_createZombie(const std::string& type, int path)
{
    auto zombie =
        ZombieFactory::getFactory()->create("NormalZombie", path);
    if(!zombie) {
        printf("create zombie error\n");
        return;
    }

    getScene()->addZombie(zombie);
}