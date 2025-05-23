#include <fstream>
#include <iostream>
#include <json/json.h>

#include <base/direction.hpp>
#include <entity/zombie/factory.hpp>
#include <entity/zombie/zombie.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void initPlantData(
    string_view path,
    unordered_map<string, std::unique_ptr<ZombieData>>& res
)
{
    if(!filesystem::is_regular_file(path)) {
        return;
    }

    ifstream ifs(path.data());
    assert(ifs.is_open());

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(ifs, root, false)) {
        cerr << "parse " << path << " error\n";
        return;
    }

    for(auto it = root.begin(); it != root.end(); ++it) {
        const auto& key = it.name();
        const auto& value = *it;
        Direction::DIR dir(Direction::DIR::STOP);
        std::string dir_str = value["dir"].asString();
        if(dir_str == "left") {
            dir = Direction::DIR::LEFT;
        } else if(dir_str == "right") {
            dir = Direction::DIR::RIGHT;
        }
        res[key] = make_unique<ZombieData>(ZombieData{
            value["HP"].asFloat(),
            SizeType(
                value["size"][0].asFloat(),
                value["size"][1].asFloat()
            ),

            Direction(dir),
            value["speed"].asFloat(),

            value["animation"].asString(),
            value["frame2animation"].asInt(),

            value["cd"].asFloat(),
            value["damage"].asFloat(),
        });
    }
}

ZombieFactory::ZombieFactory()
{
    initPlantData(
        "/home/wlle/code/demo/sfml2/json/zombie.json", m_data
    );
}

Zombie* ZombieFactory::create(const string& name, int path)
{
    if(m_data.find(name) == m_data.end()) {
        return nullptr;
    }

    return new Zombie(*m_data[name], path);
    // 或许factory应该负责plant组件的添加
}