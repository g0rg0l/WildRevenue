#ifndef UNTITLED_STATICENTITY_H
#define UNTITLED_STATICENTITY_H

#include <SFML/Graphics.hpp>

#include "../inventory/items/items.h"

class CollectableEntity : public sf::Drawable
{
public:
    CollectableEntity(const std::string& src_name, std::string  item_id,
                      int stages_count, float stage_time, float hitbox_range,
                      sf::Vector2f pos, items::types ret_item_type);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual void update();
    virtual std::shared_ptr<ItemBase> execute();
    virtual bool is_see_player(sf::FloatRect player_hitbox);

public:
    virtual std::string get_returning_item_id() const;

protected:
    virtual sf::FloatRect get_hitbox() const;

protected:
    virtual void next_stage();

protected:
    sf::Sprite sprite;
    const std::string src_name;
    sf::Vector2f sprite_size;
    const float hitbox_range;

protected:
    sf::Clock stage_clock;
    const int stages_count;
    int stage = stages_count - 1;
    const float stage_time;

protected:
    const std::string item_id;
    const items::types ret_item_type;

};


#endif
