#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include <string>
#include "../engine/TextureHolder.h"

class Item
{
public:
    Item(std::string id, std::string name);
    virtual ~Item() = default;

public:
    virtual void increase(int n);
    virtual void decrease(int n);
    [[nodiscard]] virtual Item* makeNewSame() const = 0;

public:
    [[nodiscard]] virtual std::string get_id() const;
    [[nodiscard]] virtual std::string get_name() const;
    [[nodiscard]] virtual int get_count() const;

protected:
    const std::string id;
    const std::string name;
    int count = 1;
};


class Tomato : public Item
{
public:
    Tomato() : Item("tomato_item", "tomato")
    {
        TextureHolder& textureHolder = TextureHolder:: getInstance();
        textureHolder.loadFromFile("../inventory/src/tomato.png", id);
    }

    [[nodiscard]] Item* makeNewSame() const override { return new Tomato; }
};

class Potato : public Item
{
public:
    Potato() : Item("potato_item", "potato")
    {
        TextureHolder& textureHolder = TextureHolder:: getInstance();
        textureHolder.loadFromFile("../inventory/src/potato.png", id);
    }

    [[nodiscard]] Item* makeNewSame() const override { return new Potato; }
};

class BlueFlowers : public Item
{
public:
    BlueFlowers() : Item("blue_flowers_item", "blue_flowers")
    {
        TextureHolder& textureHolder = TextureHolder:: getInstance();
        textureHolder.loadFromFile("../inventory/src/blue flowers.png", id);
    }

    [[nodiscard]] Item* makeNewSame() const override { return new BlueFlowers; }
};


#endif
