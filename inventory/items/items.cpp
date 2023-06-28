#include "items.h"

namespace items
{
    std::shared_ptr<ItemBase> create(types type)
    {
        ItemBase* newItem;
        switch (type)
        {
            case types::tomato: newItem = new Tomato; break;
            case types::potato: newItem = new Potato; break;
            case types::blue_flowers: newItem = new BlueFlowers; break;

            default: newItem = nullptr; break;
        }

        return std::shared_ptr<ItemBase>(newItem);
    }

    std::shared_ptr<ItemBase> create(const std::string& id)
    {
        ItemBase* newItem;

        if (id == "tomato_item") newItem = new Tomato;
        if (id == "potato_item") newItem = new Potato;
        if (id == "blue_flowers_item") newItem = new BlueFlowers;

        return std::shared_ptr<ItemBase>(newItem);
    }
}