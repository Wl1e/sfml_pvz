#include <SFML/Graphics/RenderWindow.hpp>

#include <animation/gamescene.h>
#include <entity/components/animation_comp.hpp>
#include <entity/components/position_comp.hpp>
#include <entity/entity.hpp>

using namespace std;
using namespace sf;
using namespace demo;

namespace demo {

bool read_frames2(
    filesystem::path, unordered_map<string, vector<anime_frame>>&
);

// bool read_frames(
//     const string& path,
//     unordered_map<string, vector<anime_frame>>& result
// )
// {
//     filesystem::path frame_path(path);
//     return read_frames2(frame_path, result);
// }

bool read_frames(
    string_view path,
    unordered_map<string, vector<anime_frame>>& result
)
{
    filesystem::path frame_path(path);
    return read_frames2(frame_path, result);
}

bool read_frames2(
    filesystem::path frame_path,
    unordered_map<string, vector<anime_frame>>& res
)
{
    if(!filesystem::exists(frame_path)) {
        return false;
    }
    if(!filesystem::is_directory(frame_path)) {
        return false;
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
    return !res.empty();
}

} // namespace demo

void AnimationComp::update(Entity* entity)
{
    updateAnimation();
    updatePos(entity);
    // FIXME
    entity->getScene()->getNativeWindow()->draw(*m_sprite);
}

void AnimationComp::updateAnimation()
{
    if(m_idx >= m_frames->at(m_status).size()) {
        m_idx = 0;
    }
    m_sprite->setTexture(m_frames->at(m_status)[m_idx++]);
}
void AnimationComp::updateAnimationStatus(string_view status)
{
    if(!m_frames->count(status.data())) {
        return;
    }
    m_status = status;
    m_idx = 0;
    updateAnimation();
}
void AnimationComp::updatePos(Entity* entity)
{
    Component* posComp;
    if(posComp = entity->getComp(CompType::POSITION); !posComp) {
        return;
    }

    auto p = castTo<type2cls<CompType::POSITION>::type>(posComp);
    m_sprite->setPosition(sf::Vector2f(p->getPos()));
}
