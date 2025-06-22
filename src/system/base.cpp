#include <system/base.hpp>

using namespace std;
using namespace demo;

BaseSystem::~BaseSystem()
{
    m_targets.clear();
}

void BaseSystem::addEntity(Entity* entity)
{
    m_targets.insert(entity);
}

void BaseSystem::delEntity(Entity* entity)
{
    m_targets.erase(entity);
}