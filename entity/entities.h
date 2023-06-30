#ifndef GAME_ENTITIES_H
#define GAME_ENTITIES_H

#include <memory>

#include "../entity/CollectableEntity.h"
#include "../entity/Trader.h"

namespace entity
{
    enum class collectable
    {
        tomato,
        potato,
        blue_flowers
    };

    enum class traders
    {
        blacksmith,
        herbalist,
        potion_maker,
        mistery
    };

    std::shared_ptr<CollectableEntity> create(collectable type, sf::Vector2f pos);
    std::shared_ptr<Trader> create(traders type, sf::Vector2f pos);
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

namespace entity
{
    class BlackSmith : public Trader
    {
    public:
        explicit BlackSmith(sf::Vector2f pos) : Trader(
                "blacksmith", {8, 23},
                {8, 4,15, 27},
                pos) {  }
    };

    class Herbalist : public Trader
    {
    public:
        explicit Herbalist(sf::Vector2f pos) : Trader(
                "herbalist", {8, 8},
                {0, 0,0, 0},
                pos) {  }
    };

    class PotionMaker : public Trader
    {
    public:
        explicit PotionMaker(sf::Vector2f pos) : Trader(
                "potion_maker", {19, 9},
                {0, 4,25, 29},
                pos) {  }
    };
}

#endif
