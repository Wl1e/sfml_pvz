#include <assert.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <unordered_map>

#include <UI/defines.hpp>

using namespace demo;
using namespace std;

unordered_map<std::string, Json::Value>
parseUIData(const string_view path)
{
    unordered_map<std::string, Json::Value> res;
    if(!filesystem::is_regular_file(path)) {
        return res;
    }

    ifstream ifs(path.data());
    assert(ifs.is_open());

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(ifs, root, false)) {
        cerr << "parse " << path << " error\n";
    }

    res["window_length"] = root["window_length"];
    res["window_wide"] = root["window_wide"];
    res["grass_length"] = root["grass_length"];
    res["grass_wide"] = root["grass_wide"];
    res["grass_start_x"] = root["grass_start_x"];
    res["grass_start_y"] = root["grass_start_y"];
    res["grass_path"] = root["grass_path"];
    res["grass_count"] = root["grass_count"];

    return res;
}

static unordered_map<std::string, Json::Value> config =
    parseUIData("/home/wlle/sfml2/json/UI.json");

const uint UI_DEFINE::WINDOW_LENGTH =
    config["window_length"].asUInt();
const uint UI_DEFINE::WINDOW_WIDE = config["window_wide"].asUInt();
const int UI_DEFINE::GRASS_LENGTH = config["grass_length"].asInt();
const int UI_DEFINE::GRASS_WIDE = config["grass_wide"].asInt();
const int UI_DEFINE::GRASS_START_X = config["grass_start_x"].asInt();
const int UI_DEFINE::GRASS_START_Y = config["grass_start_y"].asInt();
const int UI_DEFINE::GRASS_PATH = config["grass_path"].asInt();
const int UI_DEFINE::GRASS_COUNT = config["grass_count"].asInt();