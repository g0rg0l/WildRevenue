#ifndef UNTITLED_BLUEFLOWERSPLANT_H
#define UNTITLED_BLUEFLOWERSPLANT_H

#include <iostream>
#include "../StaticEntity.h"

class BlueFlowersPlant : public StaticEntity
{
public:
    explicit BlueFlowersPlant(sf::Vector2f pos)
            : StaticEntity("blue flowers", "blue_flowers_item", 2, 0.2, 8.0, pos)
    { }

private:
    Item* action() override
    {
        std::cout << "blue flowers executed." << std::endl;

        return new BlueFlowers;
    }

};

#endif
