set(ENTITY_SRC
    entity.cpp
    attack.cpp
    plant/plant.cpp
    zombie/zombie.cpp
    bullet/bullet.cpp
    tool/plant_creator.cpp

    bullet/factory.cpp
    plant/factory.cpp
    zombie/factory.cpp
)

add_library(demo-entity ${ENTITY_SRC})

target_include_directories(demo-entity PRIVATE ../)

target_link_libraries(demo-entity sfml-system sfml-window sfml-graphics)