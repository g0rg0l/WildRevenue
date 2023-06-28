#include "EntityHolder.h"


void EntityHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& entity : collectable_entities)
        target.draw(*entity);
}

void EntityHolder::update()
{
    for (auto& entity : collectable_entities)
        entity->update();
}

EntityHolder::EntityHolder()
{
    collectable_entities.push_back(entity::create(entity::collectable::tomato, {16, 16}));
    collectable_entities.push_back(entity::create(entity::collectable::potato, {64, 64}));
    collectable_entities.push_back(entity::create(entity::collectable::blue_flowers, {128, 128}));
}

void EntityHolder::entity_collect_check(Player *player)
{
    for (auto& entity : collectable_entities)
        if (player->inventory.can_be_placed_in(entity->get_returning_item_id()))
        {
            auto resultOfTryingExecute = entity->execute();
            if (resultOfTryingExecute)
            {
                player->inventory.add(resultOfTryingExecute);
                break;
            }
        }
}
