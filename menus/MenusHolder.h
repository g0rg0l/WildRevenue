#ifndef UNTITLED_MENUSHOLDER_H
#define UNTITLED_MENUSHOLDER_H

#include <SFML/Graphics.hpp>
#include "InventoryMenu.h"

class MenusHolder : public sf::Drawable
{
public:
    void create(Inventory* player_inv)
    {
        inventory_menu.create(player_inv);
    }

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(inventory_menu, states);
    }

    void update(sf::Vector2f camera_position, sf::Vector2f mousePosition)
    {
        inventory_menu.update(camera_position, mousePosition);
    }

public:
    void executeInventory() { inventory_menu.execute(); }

private:
    InventoryMenu inventory_menu;
};

#endif