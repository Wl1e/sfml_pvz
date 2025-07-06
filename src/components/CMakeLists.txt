# 未使用
# 各模块之间耦合严重，切不开

set(COMPONENT_SRC
    movement_comp.cpp
    position_comp.cpp
    animation_comp.cpp
    attack_comp.cpp
    hp_comp.cpp
)

add_library(demo-component ${COMPONENT_SRC})

target_include_directories(demo-component PRIVATE ../)

target_link_libraries(demo-component sfml-system sfml-window sfml-graphics)
