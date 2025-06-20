#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>

#include <entity/bullet/factory.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void initBulletData(
    string_view path,
    unordered_map<string, std::unique_ptr<BulletSupport>>& res
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
    }

    for(auto it = root.begin(); it != root.end(); ++it) {
        const auto& key = it.name();
        const auto& value = *it;

        res[key] = make_unique<BulletSupport>(BulletSupport{
            SizeType(
                value["size"][0].asFloat(),
                value["size"][1].asFloat()
            ),
            value["piercing"].asBool(),
            value["speed"].asInt(),
            value["animation"].asString()
        });
    }
}

BulletFactory::BulletFactory()
{
    initBulletData(
        "/home/wlle/code/demo/sfml2/json/bullet.json", m_data
    );
}

// FIXME: 后续参考component改成枚举
Bullet* BulletFactory::create(
    const std::string& type, const PlantSupport& data
)
{
    if(m_data.find(type) == m_data.end()) {
        return nullptr;
    }
    return new Bullet(BulletData{type, *m_data[type], data});
}