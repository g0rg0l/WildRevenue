#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include <memory>
#include <unordered_map>

#include "ItemBase.h"

namespace items
{
    enum class types
    {
        tomato,
        potato,
        blue_flowers
    };

    std::shared_ptr<ItemBase> create(types type);
    std::shared_ptr<ItemBase> create(const std::string& id);
}

namespace items
{
    class Tomato : public ItemBase
    {
    public:
        Tomato() : ItemBase("tomato_item", "tomato", "tomato") {  }
    };

    class Potato : public ItemBase
    {
    public:
        Potato() : ItemBase("potato_item", "potato", "potato") {  }
    };

    class BlueFlowers : public ItemBase
    {
    public:
        BlueFlowers() : ItemBase("blue_flowers_item", "blue_flowers", "blue flowers") {  }
    };
}

#endif
