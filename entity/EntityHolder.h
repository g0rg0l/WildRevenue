#ifndef UNTITLED_ENTITYHOLDER_H
#define UNTITLED_ENTITYHOLDER_H

#include "entities.h"
#include "../player/Player.h"

class EntityHolder : public sf::Drawable
{
public:
    EntityHolder();

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
    void entity_collect_check(Player* player);

private:
    std::vector<std::shared_ptr<CollectableEntity>> collectable_entities;
};

#endif
