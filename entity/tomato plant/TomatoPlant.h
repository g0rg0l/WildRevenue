#ifndef UNTITLED_TOMATOPLANT_H
#define UNTITLED_TOMATOPLANT_H

#include <iostream>
#include "../StaticEntity.h"

class TomatoPlant : public StaticEntity
{
public:
    explicit TomatoPlant(sf::Vector2f pos)
        : StaticEntity("tomato plant", "tomato_item", 5, 0.2, 8.0, pos)
    { }

private:
    Item* action() override
    {
        std::cout << "tomato executed." << std::endl;

        return new Tomato;
    }

};

#endif
