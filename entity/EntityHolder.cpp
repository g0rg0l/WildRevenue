#include "EntityHolder.h"

EntityHolder::EntityHolder()
{
    player = new Player;
}

EntityHolder::~EntityHolder()
{
    delete player;
}

void EntityHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*player, states);
}

void EntityHolder::update_entity(float dt, const std::vector<sf::FloatRect>& wallBounds)
{
    player->update(dt, wallBounds);
}

sf::FloatRect EntityHolder::get_player_bounds() const
{
    return player->get_bounds();
}
