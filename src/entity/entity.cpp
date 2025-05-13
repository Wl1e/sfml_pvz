#include <animation/animation.h>
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
    m_size = m_animation->getSize();
}

// 显示的图像和Entity的中心不一样，Entity的在正中间，animation的在左上角
// ？
void Entity::setPos(const Vector2i& pos)
{
    m_pos = pos;
    m_animation->setDrawPosition(pos - Vector2i(m_size) / 2);
}

void Entity::setSize(const sf::Vector2u& size)
{
    m_size = size;
    m_animation->setDrawSize(m_size);
}

void Entity::updateAnimation()
{
    // 这里需要改
    m_animation->update(nullptr);
}