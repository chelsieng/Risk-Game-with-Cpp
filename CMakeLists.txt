cmake_minimum_required(VERSION 3.17)
project(COMP_345)

set(CMAKE_CXX_STANDARD 14)

include_directories("Game Engine")
include_directories("Map")
include_directories("MapLoader")
include_directories("Orders")
include_directories("Player")
include_directories("Cards")

add_executable(COMP_345
        "Game Engine/GameEngine.cpp"
        "Game Engine/GameEngine.h"
        "Game Engine/GameObservers.cpp"
        "Game Engine/GameObservers.h"
#        "Game Engine/MainGameLoopDriver.cpp"
#        "Game Engine/StartupPhase Driver.cpp"
#        "Game Engine/Testing.cpp"
#        "Map/GameStart.cpp"
        "Map/GameStart.h"
        "Map/Graph.h"
        "Map/Map.cpp"
        "Map/Map.h"
#        "Map/MapDriver.cpp"
        "MapLoader/MapLoader.cpp"
        "MapLoader/MapLoader.h"
#        "MapLoader/MapLoaderDriver.cpp"
        "Orders/Orders.cpp"
        "Orders/Orders.h"
#        "Orders/OrdersDriver.cpp"
        "Player/Player.cpp"
        "Player/Player.h"
#        "Player/PlayerDriver.cpp"
        "Cards/Cards.cpp"
        "Cards/Cards.h"
#        "Cards/CardsDriver.cpp"
        "Player/PlayerStrategies.cpp"
        "Player/PlayerStrategies.h"
        )
