#ifndef UNTITLED_STATICENTITY_H
#define UNTITLED_STATICENTITY_H

#include <SFML/Graphics.hpp>
#include "../engine/TextureHolder.h"

class StaticEntity : public sf::Drawable
{
public:
    StaticEntity(const std::string& src_name, int stages_count, float stage_time, float hitbox_range, sf::Vector2f pos);

    virtual void update();
    virtual bool execute();
    virtual bool is_see_player(sf::FloatRect player_hitbox);

protected:
    virtual void next_stage();

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    virtual sf::FloatRect get_hitbox() const;

protected:
    virtual void action() = 0;

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

};


#endif
