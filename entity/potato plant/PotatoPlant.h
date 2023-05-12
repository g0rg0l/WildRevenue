#ifndef UNTITLED_POTATOPLANT_H
#define UNTITLED_POTATOPLANT_H

#include <iostream>
#include "../StaticEntity.h"

class PotatoPlant : public StaticEntity
{
public:
    explicit PotatoPlant(sf::Vector2f pos)
            : StaticEntity("potato plant", "potato_item", 5, 0.2, 8.0, pos)
    { }

private:
    Item* action() override
    {
        std::cout << "potato executed." << std::endl;

        return new Potato;
    }

};

#endif
