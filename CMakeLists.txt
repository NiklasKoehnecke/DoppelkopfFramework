cmake_minimum_required(VERSION 3.12)
project(doppelkopf)

set(CMAKE_CXX_STANDARD 17)

add_executable(doppelkopf src/main.cpp src/Game.cpp src/Game.h src/card.cpp src/card.h src/Player.cpp src/Player.h src/Ruleset.cpp src/Ruleset.h src/helper.cpp src/helper.h)