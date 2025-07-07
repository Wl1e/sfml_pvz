# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(demo VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/UI/defines.cpp
    src/UI/ui_layout.cpp
    src/UI/background.cpp

    src/base/tools.cpp
    src/base/direction.cpp
    src/base/range.cpp

    src/event_manager.cpp

    src/components/movement_comp.cpp
    src/components/position_comp.cpp
    src/components/animation_comp.cpp
    src/components/attack_comp.cpp
    src/components/hp_comp.cpp

    src/entity/entity.cpp
    src/entity/attack.cpp
    src/entity/plant/plant.cpp
    src/entity/plant/shooter_plant.cpp
    src/entity/plant/mine_plant.cpp
    src/entity/zombie/zombie.cpp
    src/entity/bullet/bullet.cpp
    src/entity/tool/plant_creator.cpp

    src/entity/bullet/factory.cpp
    src/entity/plant/factory.cpp
    src/entity/zombie/factory.cpp

    src/system/base.cpp
    src/system/init.cpp
    src/system/collision_system.cpp

    src/animation/event_handler.cpp
    src/animation/gamescene.cpp
    
    src/demo.cpp
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src/)

# Link libraries (e.g., SFML)
# find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} jsoncpp)

# add_subdirectory(src/entity)

target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_DEBUG)
