#include <SFML/Graphics/RenderWindow.hpp>

#include <animation/gamescene.hpp>
#include <components/animation_comp.hpp>
#include <components/position_comp.hpp>
#include <entity/entity.hpp>
#include <entity/frame.hpp>
#include <event_manager.hpp>

using namespace std;
using namespace sf;
using namespace demo;

namespace demo {

static unordered_map<EntityType, Vector2i> ANIMATION_OFFSET{
    {EntityType::PLANT, Vector2i(0, 0)},
    {EntityType::ZOMBIE, Vector2i(-10, -10)},
    {EntityType::BULLET, Vector2i(0, 0)},
};

void read_frames2(
    filesystem::path, unordered_map<string, vector<AnimeFrame>>&
);

void read_frames(
    string_view path,
    unordered_map<string, vector<AnimeFrame>>& result
)
{
    filesystem::path frame_path(path);
    read_frames2(frame_path, result);
}

void read_frames2(
    filesystem::path frame_path,
    unordered_map<string, vector<AnimeFrame>>& res
)
{
    if(!filesystem::exists(frame_path)) {
        return;
    }
    if(!filesystem::is_directory(frame_path)) {
        if(filesystem::is_regular_file(frame_path)) {
            std::string name = frame_path.filename().stem();
            res[name].resize(2);
            res[name][1] = AnimeFrame(frame_path);
            return;
        }
        return;
    }

    for(const auto& type :
        filesystem::directory_iterator(frame_path)) {
        if(!type.is_directory()) {
            continue;
        }
        string typeName = type.path().filename().stem();
        res[typeName];
        for(auto& entity : filesystem::directory_iterator(type)) {
            int idx = stoi(entity.path().filename().stem());
            if(res[typeName].size() <= idx) {
                res[typeName].resize(idx + 1);
            }
            res[typeName][idx] = AnimeFrame(entity.path());
        }
    }
}

} // namespace demo

AnimationComp::AnimationComp(std::string_view resource_path) :
    m_frames(
        std::make_unique<std::unordered_map<
            std::string,
            std::vector<AnimeFrame>>>()
    ),
    m_idx(1), m_last_frame(0), m_interval(1)
{
    read_frames(resource_path, *m_frames);
    if(filesystem::is_regular_file(resource_path)) {
        m_status = filesystem::path(resource_path).filename().stem();
    } else {
        m_status = "normal";
    }
    m_sprite =
        std::make_unique<sf::Sprite>(m_frames->at(m_status)[m_idx]);
}

void AnimationComp::update(Entity* entity)
{
    if(auto posComp = entity->getComp<CompType::POSITION>();
       posComp) {
        auto pos = posComp->getPos();
        if(ANIMATION_OFFSET.find(entity->getType())
           != ANIMATION_OFFSET.end()) {
            pos += PositionType(ANIMATION_OFFSET[entity->getType()]);
        }
        _updatePos(pos);
    };

    if(_validUpdateAnimation()) {
        if(_updateAnimation() == m_frames->at(m_status).size()) {
            trigger(
                entity,
                EventType::FinishAnimation,
                std::make_any<string>(getStatus())
            );
        }
    }

    entity->getScene()->draw(*m_sprite);
}

bool AnimationComp::_validUpdateAnimation()
{
    Frame now = FrameManager::getInstance().getFrame();
    if(now - m_last_frame < m_interval) {
        return false;
    }
    m_last_frame = now;
    return true;
}

int AnimationComp::_updateAnimation()
{
    int ret = m_idx;

    if(m_idx >= m_frames->at(m_status).size()) {
        m_idx = 1;
    }
    m_sprite->setTexture(m_frames->at(m_status)[m_idx++], false);
    // if(m_sprite->getColor() != Color::White) {
    //     m_sprite->setColor(Color::White);
    // }

    return ret;
}
bool AnimationComp::updateAnimationStatus(string_view status)
{
    if(m_status == status) {
        return true;
    }
    if(m_frames->find(status.data()) == m_frames->end()) {
        return false;
    }
    m_status = status;
    m_idx = 1;
    return true;
}

void AnimationComp::_updatePos(const PositionType& pos)
{
    m_sprite->setPosition(pos);
}

void AnimationComp::setColor(const sf::Color& color)
{
    m_sprite->setColor(color);
}

void AnimationComp::resetColor()
{
    setColor(Color(255, 255, 255, 255));
}