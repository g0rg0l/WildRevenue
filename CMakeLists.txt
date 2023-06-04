cmake_minimum_required(VERSION 3.25)
project(game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include/SFML)

add_executable(game
        main.cpp
        engine/Camera.h engine/Camera.cpp
        engine/Engine.h engine/Engine.cpp
        engine/EventWatcher.h
        engine/TextureHolder.h
        engine/WorldTimeHolder.h engine/WorldTimeHolder.cpp

        entity/EntityHolder.h entity/EntityHolder.cpp
        entity/StaticEntity.h entity/StaticEntity.cpp

        "entity/blue flowers/BlueFlowersPlant.h"
        "entity/tomato plant/TomatoPlant.h"
        "entity/potato plant/PotatoPlant.h"

        entity/player/Player.h entity/player/Player.cpp

        inventory/Inventory.h inventory/Inventory.cpp
        inventory/Item.h inventory/Item.cpp

        map/TileMap.h map/TileMap.cpp
        map/Tileset.h map/Layer.h

        menus/InventoryMenu.h menus/InventoryMenu.cpp
        )

target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)