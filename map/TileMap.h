#ifndef UNTITLED_TILEMAP_H
#define UNTITLED_TILEMAP_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

#include "Tileset.h"
#include "Layer.h"

class TileMap
{
public:
    void load();
    void clip(sf::FloatRect viewRect);

private:
    mutable std::vector<Tileset> tilesets;
    mutable std::vector<Layer> layers = std::vector<Layer>(3);

public:
    Layer& terrain = layers[0];
    Layer& decor = layers[1];
    Layer& trees = layers[2];
};


#endif
