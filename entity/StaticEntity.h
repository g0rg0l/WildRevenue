#ifndef UNTITLED_STATICENTITY_H
#define UNTITLED_STATICENTITY_H

#include <SFML/Graphics.hpp>
#include "../engine/TextureHolder.h"
#include "../inventory/Item.h"

class StaticEntity : public sf::Drawable
{
public:
    StaticEntity(const std::string& src_name, const std::string& item_id,
                 int stages_count, float stage_time, float hitbox_range, sf::Vector2f pos);

    virtual void update();
    virtual Item* execute();
    virtual bool is_see_player(sf::FloatRect player_hitbox);

    virtual std::string get_returning_item_id() const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    virtual void next_stage();

protected:
    virtual sf::FloatRect get_hitbox() const;

protected:
    virtual Item* action() = 0;

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

};


#endif
