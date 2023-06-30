#include "CollectableEntity.h"

CollectableEntity::CollectableEntity(
        const std::string& src_name, std::string  item_id,
        int stages_count, float stage_time, float hitbox_range, sf::Vector2f pos,
        items::types ret_item_type)

    : src_name(src_name), stages_count(stages_count), stage_time(stage_time),
        hitbox_range(hitbox_range), item_id(std::move(item_id)), ret_item_type(ret_item_type)
{
    TextureHolder& textureholder = TextureHolder::getInstance();
    textureholder.loadFromFile("../entity/src/collectables/" + src_name + ".png", src_name);

    auto texture = textureholder.getResource(src_name);

    auto texture_size = texture->getSize();
    sprite_size = {(float) texture_size.x / (float) stages_count, (float) texture_size.y };

    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(
            (int) sprite_size.x * (stages_count - 1), 0,
            (int) sprite_size.x, (int) sprite_size.y
    ));
    sprite.setPosition(pos);
}

void CollectableEntity::update()
{
    if (stage != stages_count - 1 &&  stage_clock.getElapsedTime().asSeconds() >= stage_time)
        next_stage();
}

void CollectableEntity::next_stage()
{
    stage_clock.restart();
    stage = (++stage) % stages_count;
    sprite.setTextureRect(sf::IntRect(stage * sprite_size.x, 0, sprite_size.x, sprite_size.y));
}

void CollectableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::FloatRect CollectableEntity::get_hitbox() const
{
    auto bounds = sprite.getGlobalBounds();

    return {
            bounds.left - hitbox_range, bounds.top - hitbox_range,
            bounds.width + 2*hitbox_range, bounds.height + 2*hitbox_range
    };
}

std::string CollectableEntity::get_returning_item_id() const { return item_id; }

std::shared_ptr<ItemBase> CollectableEntity::execute()
{
    std::shared_ptr<ItemBase> result(nullptr);

    if (stage == stages_count - 1)
    {
        result = items::create(ret_item_type);
        next_stage();
    }

    return result;
}

bool CollectableEntity::is_see_player(sf::FloatRect player_hitbox)
{
    return get_hitbox().intersects(player_hitbox);
}