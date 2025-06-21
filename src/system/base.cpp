#include <system/base.hpp>

using namespace std;
using namespace demo;

void BaseSystem::addEntity(Entity* entity)
{
    m_targets.insert(entity);
}

void BaseSystem::delEntity(Entity* entity)
{
    m_targets.erase(entity);
}