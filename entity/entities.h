#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

#include <memory>

#include "../entity/CollectableEntity.h"

namespace entity
{
    enum class collectable
    {
        tomato,
        potato,
        blue_flowers
    };

    std::shared_ptr<CollectableEntity> create(collectable type, sf::Vector2f pos);
}

namespace entity
{
    class Tomato : public CollectableEntity
    {
    public:
        explicit Tomato(sf::Vector2f pos) : CollectableEntity(
                "tomato plant", "tomato_item",
                5, 0.2, 8.0,
                pos, items::types::tomato) { }
    };

    class Potato : public CollectableEntity
    {
    public:
        explicit Potato(sf::Vector2f pos) : CollectableEntity(
                "potato plant", "potato_item",
                5, 0.2, 8.0,
                pos, items::types::potato) { }
    };

    class BlueFlowers : public CollectableEntity
    {
    public:
        explicit BlueFlowers(sf::Vector2f pos) : CollectableEntity(
                "blue flowers", "blue_flowers_item",
                2, 0.2, 8.0,
                pos, items::types::blue_flowers) { }
    };
}

#endif
