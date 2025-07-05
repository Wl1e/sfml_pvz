#pragma once

namespace demo {

enum class EntityType
{
    NONE = 0,
    PLANT,
    ZOMBIE,
    BULLET,
    TOOL
};

enum class EntityStatus
{
    Normal,
    Attack,
    Death,

    Clicked,
};

} // namespace demo