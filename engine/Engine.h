#ifndef UNTITLED_ENGINE_H
#define UNTITLED_ENGINE_H

#include <SFML/Graphics.hpp>

#include "EventWatcher.h"
#include "Camera.h"
#include "WorldTimeHolder.h"
#include "../map/TileMap.h"
#include "../entity/EntityHolder.h"
#include "../menus/MenusHolder.h"

class Engine
{
public:
    Engine();
    int run_engine();

private:
    void check_events();
    void draw();

private:
    sf::RenderWindow window;
    sf::RenderTexture worldRenderTexture;
    sf::RenderTexture menuRenderTexture;
    sf::Clock clock;
    float dt;

private:
    WorldTimeHolder worldTimeHolder;
    Camera camera;
    TileMap map;
    EntityHolder entityHolder;
    MenusHolder menusHolder;
};


#endif
