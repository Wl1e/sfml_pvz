#include <string>
#include <unordered_map>

#include <system/base.hpp>
#include <system/collision_system.hpp>
#include <system/init.hpp>

using namespace std;

namespace demo {

static unordered_map<string, BaseSystem*> SYSTEMS;

void initSystems()
{
    SYSTEMS["collision"] = new CollisionSystem();
    printf("init %s systems\n", "collision");
}

void updateSystems()
{
    for(auto& [_, system] : SYSTEMS) {
        system->update();
    }
}

} // namespace demo