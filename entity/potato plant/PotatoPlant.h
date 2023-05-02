#ifndef UNTITLED_POTATOPLANT_H
#define UNTITLED_POTATOPLANT_H

#include <iostream>
#include "../StaticEntity.h"

class PotatoPlant : public StaticEntity
{
public:
    explicit PotatoPlant(sf::Vector2f pos)
            : StaticEntity("potato plant", 5, 3.0, 4.0, pos)
    { }

private:
    void action() override
    {
        std::cout << "potato executed." << std::endl;
    }

};

#endif
