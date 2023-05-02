#ifndef UNTITLED_TOMATOPLANT_H
#define UNTITLED_TOMATOPLANT_H

#include <iostream>
#include "../StaticEntity.h"

class TomatoPlant : public StaticEntity
{
public:
    explicit TomatoPlant(sf::Vector2f pos)
        : StaticEntity("tomato plant", 5, 2.0, 8.0, pos)
    { }

private:
    void action() override
    {
        std::cout << "tomato executed." << std::endl;
    }

};

#endif
