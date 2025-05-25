#pragma once

namespace demo {

// 后面改称读配置文件,不然改起来太麻烦了
// 太磨人了

// sfml的横轴是x轴，纵轴是y轴

struct UI
{};

const int WINDOW_LENGTH = 1280;
const int WINDOW_WIDE = 720;

// 草地横向长度
const int GRASS_LENGTH = 75;
// 草地纵向长度
const int GRASS_WIDE = 90;

const int GRASS_START_X = 234;
const int GRASS_START_Y = 100;

const int GRASS_PATH = 6;
const int GRASS_COUNT = 9;

using Frame = unsigned long long;
using FrameInterval = unsigned long long;

} // namespace demo