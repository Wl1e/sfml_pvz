#include <fstream>
#include <iostream>
#include <json/json.h>

#include <base/attack_range.hpp>
#include <entity/plant/factory.hpp>
#include <entity/plant/plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void initPlantData(
    string_view path,
    unordered_map<string, std::unique_ptr<PlantData>>& res
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
        AttackRange* range = nullptr;
        string range_type = value["range"]["type"].asString();
        if(range_type == "Rectangle") {
            range = new AttackRange(
                rangeType::Rectangle,
                SizeType(

                    value["range"]["data"][0].asFloat()
                        + value["range"]["data"][1].asFloat(),
                    0
                )
            );
        } else if(range_type == "Circle") {
            range = new AttackRange(
                rangeType::Circle,
                SizeType(value["range"]["data"][0].asFloat(), 0)
            );
        }

        res[key] = make_unique<PlantData>(PlantData{
            value["HP"].asFloat(),
            value["CD"].asInt(),
            value["damage"].asFloat(),
            std::move(*range),
            value["animation"].asString(),
            value["frame2animation"].asInt(),
            SizeType(
                value["size"][0].asFloat(),
                value["size"][1].asFloat()
            ),
            value["bullet_type"].asString()
        });
    }
}

PlantFactory::PlantFactory()
{
    initPlantData(
        "/home/wlle/code/demo/sfml2/json/plant.json", m_data
    );
}

Plant* PlantFactory::create(const string& name, const Vector2i& pos)
{
    if(m_data.find(name) == m_data.end()) {
        return nullptr;
    }

    return new Plant(*m_data[name], pos);
    // 或许factory应该负责plant组件的添加
}