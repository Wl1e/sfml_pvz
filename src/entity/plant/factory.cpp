#include <fstream>
#include <iostream>
#include <json/json.h>

#include <entity/plant/factory.hpp>
#include <entity/plant/plant.hpp>

using namespace std;
using namespace sf;
using namespace demo;

void initPlantData(
    string_view path, unordered_map<string, PlantData*>& res
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
        AttackRange range;
        string range_type = value["range"]["type"].asString();
        if(range_type == "Rectangle") {
            range = RectangleShape(
                {value["range"]["data"][0].asFloat(),
                 value["range"]["data"][1].asFloat()}
            );
        } else if(range_type == "Circle") {
            range = CircleShape(value["range"]["data"].asFloat());
        }
        auto data = new PlantData{
            value["HP"].asInt(),
            value["CD"].asInt(),
            value["damage"].asInt(),
            std::move(range),
            value["animation"].asString()
        };
        res[key] = data;
    }
}

PlantFactory::PlantFactory()
{
}