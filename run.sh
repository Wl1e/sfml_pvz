#!/bin/bash
g++ src/base/tools.hpppp \
    src/draw/drawable.cpp \
    src/animation/animation.cpp \
    src/animation/gamescene.cpp \
    src/entity/entity.cpp \
    src/demo.cpp -o demo -I src/ -lsfml-graphics -lsfml-window -lsfml-system


