cmake_minimum_required(VERSION 3.17)
project(COMP_345)

set(CMAKE_CXX_STANDARD 14)

include_directories("Part 1")
include_directories("Part 2")
include_directories("Part 3")
include_directories("Part 4")
include_directories("Part 5")

add_executable(COMP_345
        "Part 1/Map.cpp"
        "Part 1/Map.h"
        "Part 1/MapDriver.cpp"
        "Part 2/MapLoader.cpp"
        "Part 2/MapLoader.h"
        "Part 2/MapLoaderDriver.cpp"
        "Part 3/Orders.cpp"
        "Part 3/Orders.h"
        "Part 3/OrdersDriver.cpp"
        "Part 4/Player.cpp"
        "Part 4/Player.h"
        "Part 4/PlayerDriver.cpp"
        "Part 5/Cards.cpp"
        "Part 5/Cards.h"
        "Part 5/CardsDriver.cpp"
        main.cpp)
