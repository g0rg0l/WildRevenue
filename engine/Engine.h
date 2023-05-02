#ifndef UNTITLED_ENGINE_H
#define UNTITLED_ENGINE_H

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "../map/TileMap.h"
#include "../entity/EntityHolder.h"

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
    sf::RenderTexture renderTexture;
    sf::Clock clock;

private:
    Camera camera;
    TileMap map;
    EntityHolder entityHolder;
};


#endif
