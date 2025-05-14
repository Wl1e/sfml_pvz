#include <filesystem>
#include <iostream>
#include <unordered_set>

#include <animation/animation.h>

using namespace std;
using namespace sf;
using namespace demo;

bool read_frames2(
    filesystem::path, unordered_map<string, vector<anime_frame>>&
);

optional<unordered_map<string, vector<anime_frame>>>
demo::read_frames(const string& path)
{
    unordered_map<string, vector<anime_frame>> res;
    filesystem::path frame_path(path);
    if(!read_frames2(frame_path, res)) {
        return {};
    }
    return res;
}

optional<unordered_map<string, vector<anime_frame>>>
demo::read_frames(string_view path)
{
    unordered_map<string, vector<anime_frame>> res;
    filesystem::path frame_path(path);
    if(!read_frames2(frame_path, res)) {
        return {};
    }
    return res;
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
        if(mid != string::npos) {
            string pre_idx = name.substr(0, mid);
            int suf_idx = stoi(name.substr(mid + 1));
            if(res[pre_idx].size() <= suf_idx) {
                res[pre_idx].resize(suf_idx + 1);
            }
            res[pre_idx][suf_idx] = Texture(entity.path());
        } else {
            res[name].emplace_back(entity.path());
        }
    }
    return !res.empty();
}

// ===============BaseAnimation===============

BaseAnimation::BaseAnimation(GameScene* window) : Drawable(window)
{
}
BaseAnimation::~BaseAnimation()
{
}

// ===============Animation===============

Animation::Animation(
    GameScene* window, const vector<anime_frame>& source
) : BaseAnimation(window), m_data(source), m_idx(0)
{
    setDrawContent(m_data[m_idx]);
}

Animation::Animation(GameScene* window, string_view source_path) :
    BaseAnimation(window)
{
    auto result = read_frames(source_path);
    if(!result.has_value()) {
        cerr << "error source_path: " << source_path << endl;
    } else {
        m_data = result.value().begin()->second;
    }
    setDrawContent(m_data[0]);
}

Animation::~Animation()
{
}

void Animation::update()
{
    // setDrawContent(m_data[m_idx]);
    draw();
}

void Animation::reset()
{
    m_idx = 0;
}

// ===============AutoAnimation===============

AutoAnimation::AutoAnimation(
    GameScene* window, const vector<anime_frame>& source
) : Animation(window, source), m_update_func(nullptr)
{
}

void AutoAnimation::update()
{
    if(m_update_func && !m_update_func(nullptr)) {
        return;
    }
    if(m_idx >= m_data.size()) {
        m_idx = 0;
    }
    setDrawContent(m_data[m_idx++]);
}
