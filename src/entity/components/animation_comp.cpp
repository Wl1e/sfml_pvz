#include <entity/components/animation_comp.hpp>

using namespace std;
using namespace sf;
using namespace demo;

namespace demo {

bool read_frames2(
    filesystem::path, unordered_map<string, vector<anime_frame>>&
);

// bool demo::read_frames(
//     const string& path,
//     unordered_map<string, vector<anime_frame>>& result
// )
// {
//     filesystem::path frame_path(path);
//     return read_frames2(frame_path, result);
// }

bool demo::read_frames(
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

void AnimationComp::setScene(GameScene* scene)
{
    m_scene = scene;
    setPosFunc([scene, this]() -> const sf::Vector2i& {
        return AnimationComp::defaultPosFunction(scene);
    });
}

} // namespace demo