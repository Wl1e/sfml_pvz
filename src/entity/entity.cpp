#include <animation/base.h>
#include <entity/entity.h>

using namespace std;
using namespace sf;
using namespace demo;

Entity::Entity(EntityType type, string_view source_path) :
    m_scene(nullptr), m_type(type), m_pos({0, 0}), m_size({0, 0}),
    m_animation(make_unique<Animation>(nullptr, "source/sun"))
{
}

void Entity::setScene(GameScene* scene)
{
    m_scene = scene;
    m_animation->setScene(m_scene);
}

void Entity::updateAnimation()
{
    // 这里需要改
    m_animation->update(nullptr);
}