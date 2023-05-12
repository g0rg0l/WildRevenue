#include "EntityHolder.h"

EntityHolder::EntityHolder()
{
    player = new Player;

    static_entities.push_back(StaticEntityFactory::getEntity("tomato plant"));
    static_entities.push_back(StaticEntityFactory::getEntity("potato plant"));
    static_entities.push_back(StaticEntityFactory::getEntity("blue flowers"));
}

EntityHolder::~EntityHolder()
{
    delete player;

    for (auto& entity : static_entities)
        delete entity;
}

void EntityHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& entity : static_entities)
        target.draw(*entity, states);

    target.draw(*player, states);
}

void EntityHolder::update_entity(float dt, const std::vector<sf::FloatRect>& wallBounds)
{
    player->update(dt, wallBounds);

    for (auto& entity : static_entities)
        entity->update();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        for (auto& entity : static_entities)
            if (entity->is_see_player(player->get_hitbox()))
                if (player->inventory.can_be_placed_in(entity->get_returning_item_id()))
                {
                    Item* resultOfTryingExecute = entity->execute();
                    if (resultOfTryingExecute)
                    {
                        player->inventory.add(resultOfTryingExecute);
                        break;
                    }
                }
}

sf::FloatRect EntityHolder::get_player_bounds()
{
    return player->get_bounds();
}

Inventory* EntityHolder::get_player_inventory()
{
    return &player->inventory;
}
