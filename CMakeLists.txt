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
        entity/entities.h entity/entities.cpp
        entity/CollectableEntity.h entity/CollectableEntity.cpp
	entity/Trader.cpp entity/Trader.h

        player/Player.h player/Player.cpp

        inventory/Inventory.h inventory/Inventory.cpp
        inventory/items/ItemBase.h inventory/items/ItemBase.cpp
        inventory/items/items.h inventory/items/items.cpp

        map/TileMap.h map/TileMap.cpp
        map/Tileset.h map/Layer.h

        menus/InventoryMenu.h menus/InventoryMenu.cpp

        structures/StructureHolder.cpp structures/StructureHolder.h
        structures/Structure.cpp structures/Structure.h
 	structures/shops.cpp structures/shops.h
)

target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-audio sfml-network)