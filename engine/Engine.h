#ifndef UNTITLED_ENGINE_H
#define UNTITLED_ENGINE_H

#include <SFML/Graphics.hpp>

#include "../player/Player.h"
#include "EventWatcher.h"
#include "Camera.h"
#include "WorldTimeHolder.h"
#include "../map/TileMap.h"
#include "../entity/EntityHolder.h"
#include "../structures/StructureHolder.h"
#include "../menus/InventoryMenu.h"

class Engine
{
public:
    Engine();
    int run_engine();

private:
    void check_events();
    void draw();

private:
    std::vector<sf::FloatRect> get_all_hitboxes();

private:
    sf::RenderWindow window;
    sf::RenderTexture worldRenderTexture;
    sf::RenderTexture menuRenderTexture;
    sf::Clock clock;
    float dt = 0;

private:
    WorldTimeHolder worldTimeHolder;
    Camera camera;
    TileMap map;

private:
    StructureHolder structureHolder;

private:
    Player player;
    EntityHolder entityHolder;

private:
    InventoryMenu inventory_menu;
};


#endif
