#ifndef UNTITLED_TILEMAP_H
#define UNTITLED_TILEMAP_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

#include "Tileset.h"
#include "Layer.h"


class TileMap : public sf::Drawable
{
public:
    bool load();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void clip(sf::FloatRect viewRect);

private:
    mutable std::vector<Tileset> tilesets;
    mutable std::vector<Layer> layers;
};


#endif
