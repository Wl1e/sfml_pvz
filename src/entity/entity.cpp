#include <animation/base.h>
#include <entity/entity.h>

using namespace std;
using namespace sf;
using namespace demo;

Entity::Entity(EntityType type) :
    m_scene(nullptr), m_type(type), m_pos({0, 0}), m_size({0, 0}),
    m_animation(nullptr)
{
}

Entity::Entity(EntityType type, string_view source_path) :
    m_scene(nullptr), m_type(type), m_pos({0, 0}), m_size({0, 0}),
    m_animation(new Animation(nullptr, source_path))
{
}

void Entity::setScene(GameScene* scene)
{
    m_scene = scene;
    if(m_animation) {
        m_animation->setScene(m_scene);
    }
}

void Entity::setAniamtion(string_view source_path)
{
    m_animation = new Animation(m_scene, source_path);
}

void Entity::updateAnimation()
{
    // 这里需要改
    m_animation->update(nullptr);
}