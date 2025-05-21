#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>

#include <entity/bullet/factory.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void initBulletData(
    string_view path, unordered_map<string, BulletSupport*>& res
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
        auto data = new BulletSupport{
            SizeType(
                value["size"][0].asFloat(),
                value["size"][1].asFloat()
            ),
            value["piercing"].asBool(),
            value["speed"].asInt(),
            value["animation"].asString()
        };
        res[key] = data;
    }
}

BulletFactory::BulletFactory()
{
    initBulletData(
        "/home/wlle/code/demo/sfml2/json/bullet.json", m_data
    );
}