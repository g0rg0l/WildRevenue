#ifndef GAME_STRUCTUREHOLDER_H
#define GAME_STRUCTUREHOLDER_H

#include "shops.h"
#include <vector>

class StructureHolder
{
public:
    StructureHolder();

public:
    void add(shops::types structure_type, sf::Vector2f pos);

public:
    void drawUpper(sf::RenderTarget& target) const;
    void drawBottom(sf::RenderTarget& target) const;

public:
    std::vector<sf::FloatRect> hitboxes;

private:
    std::vector<std::shared_ptr<Structure>> structures;
};


#endif
