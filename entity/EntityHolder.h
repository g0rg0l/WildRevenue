#ifndef UNTITLED_ENTITYHOLDER_H
#define UNTITLED_ENTITYHOLDER_H

#include "StaticEntity.h"
#include "../entity/tomato plant/TomatoPlant.h"
#include "../entity/potato plant/PotatoPlant.h"
#include "../entity/blue flowers/BlueFlowersPlant.h"

#include <SFML/Graphics.hpp>
#include "player/Player.h"


class EntityHolder : public sf::Drawable
{
public:
    EntityHolder();
    ~EntityHolder() override;

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void update_entity(float dt, const std::vector<sf::FloatRect>& wallBounds);

public:
    Inventory* get_player_inventory();
    sf::FloatRect get_player_bounds();

private:
    Player* player;
    std::vector<StaticEntity*> static_entities;
};


class StaticEntityFactory
{
public:
    static StaticEntity* getEntity(const std::string& type  )
    {
        if (type == "tomato plant") return new TomatoPlant({16, 16});
        if (type == "potato plant") return new PotatoPlant({64, 64});
        if (type == "blue flowers") return new BlueFlowersPlant({128, 128});

        return nullptr;
    }
};

#endif
