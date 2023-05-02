#ifndef UNTITLED_BLUEFLOWERS_H
#define UNTITLED_BLUEFLOWERS_H

#include <iostream>
#include "../StaticEntity.h"

class BlueFlowers : public StaticEntity
{
public:
    explicit BlueFlowers(sf::Vector2f pos)
            : StaticEntity("blue flowers", 2, 5.0, 2.0, pos)
    { }

private:
    void action() override
    {
        std::cout << "blue flowers executed." << std::endl;
    }

};

#endif
