# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(demo VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/base/tools.cpp
    src/base/direction.cpp

    src/components/movement_comp.cpp
    src/components/position_comp.cpp
    src/components/animation_comp.cpp
    src/components/attack_comp.cpp

    src/entity/entity.cpp
    src/entity/attack.cpp
    src/entity/plant/plant.cpp
    src/entity/zombie/zombie.cpp
    src/entity/bullet/bullet.cpp

    src/entity/bullet/factory.cpp
    src/entity/plant/factory.cpp
    src/entity/zombie/factory.cpp

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

target_compile_definitions(${PROJECT_NAME} PRIVATE DEMO_DEBUG)