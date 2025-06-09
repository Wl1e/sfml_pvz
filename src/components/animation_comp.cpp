#include <SFML/Graphics/RenderWindow.hpp>

#include <animation/gamescene.hpp>
#include <components/animation_comp.hpp>
#include <components/position_comp.hpp>
#include <entity/entity.hpp>
#include <entity/frame.hpp>

using namespace std;
using namespace sf;
using namespace demo;

namespace demo {

static unordered_map<EntityType, Vector2i> ANIMATION_OFFSET{
    {EntityType::PLANT, Vector2i(0, 0)},
    {EntityType::ZOMBIE, Vector2i(-10, -10)},
    {EntityType::BULLET, Vector2i(0, 0)},
};

std::string read_frames2(
    filesystem::path, unordered_map<string, vector<anime_frame>>&
);

std::string read_frames(
    string_view path,
    unordered_map<string, vector<anime_frame>>& result
)
{
    filesystem::path frame_path(path);
    return read_frames2(frame_path, result);
}

std::string read_frames2(
    filesystem::path frame_path,
    unordered_map<string, vector<anime_frame>>& res
)
{
    if(!filesystem::exists(frame_path)) {
        return "";
    }
    if(!filesystem::is_directory(frame_path)) {
        if(filesystem::is_regular_file(frame_path)) {
            std::string name = frame_path.filename().stem();
            res[name].emplace_back(frame_path);
            return name;
        }
        return "";
    }

    for(const auto& entity :
        filesystem::directory_iterator(frame_path)) {
        if(!entity.is_regular_file()) {
            continue;
        }
        std::string name = entity.path().filename().stem();
        size_t mid = name.find('-');
        if(mid == string::npos) {
            continue;
        }
        string pre_idx = name.substr(0, mid);
        int suf_idx = stoi(name.substr(mid + 1));
        if(res[pre_idx].size() <= suf_idx) {
            res[pre_idx].resize(suf_idx + 1);
        }
        res[pre_idx][suf_idx] = Texture(entity.path());
    }
    return "normal";
}

} // namespace demo

void AnimationComp::update(Entity* entity)
{
    _updateAnimation();
    if(auto posComp = entity->getComp<CompType::POSITION>();
       posComp) {
        auto pos = posComp->getPos();
        if(ANIMATION_OFFSET.find(entity->getType())
           != ANIMATION_OFFSET.end()) {
            pos += PositionType(ANIMATION_OFFSET[entity->getType()]);
        }
        _updatePos(pos);
        ;
    };

    entity->getScene()->draw(*m_sprite);
}

void AnimationComp::_updateAnimation()
{
    Frame now = FrameManager::getInstance().getFrame();
    if(now - m_last_frame < m_interval) {
        return;
    }
    m_last_frame = now;

    if(m_idx >= m_frames->at(m_status).size()) {
        m_idx = 0;
    }
    m_sprite->setTexture(m_frames->at(m_status)[m_idx++], true);
}
void AnimationComp::updateAnimationStatus(string_view status)
{
    if(m_status == status) {
        return;
    }
    if(m_frames->find(status.data()) == m_frames->end()) {
        return;
    }
    m_status = status;
    m_idx = 0;
    _updateAnimation();
}
void AnimationComp::_updatePos(const PositionType& pos)
{
    m_sprite->setPosition(pos);
}
