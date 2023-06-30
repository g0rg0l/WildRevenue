#include "EntityHolder.h"


EntityHolder::EntityHolder()
{
    collectable_entities.push_back(entity::create(entity::collectable::tomato, {16, 16}));
    collectable_entities.push_back(entity::create(entity::collectable::potato, {64, 64}));
    collectable_entities.push_back(entity::create(entity::collectable::blue_flowers, {128, 128}));

    traders.push_back(entity::create(entity::traders::blacksmith, {20*16 + 56, 80*16 + 39}));
    traders.push_back(entity::create(entity::traders::herbalist, {46*16 + 30, 35*16 + 49}));
    traders.push_back(entity::create(entity::traders::potion_maker, {100*16 + 50, 100*16 + 43}));
}

void EntityHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& entity : collectable_entities)
        target.draw(*entity);

    for (auto& entity : traders)
        target.draw(*entity);
}

void EntityHolder::update()
{
    for (auto& entity : traders)
        entity->update();

    for (auto& entity : collectable_entities)
        entity->update();
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
