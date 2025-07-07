#pragma once

namespace demo {

class GameScene;

class BackgroundLayout
{
public:
    BackgroundLayout() = default;
    ~BackgroundLayout() = default;

    static void initScene(GameScene*);
};

} // namespace demo