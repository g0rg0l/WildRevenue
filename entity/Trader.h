#ifndef GAME_TRADER_H
#define GAME_TRADER_H

#include "../engine/TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <string>

class Trader : public sf::Drawable
{
public:
    explicit Trader(const std::string& src, sf::Vector2f stages,
                    sf::FloatRect hitbox, sf::Vector2f pos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void update();

public:
    void setPosition(sf::Vector2f pos);
    void setPositionByHitbox(sf::Vector2f pos);

protected:
    /* Sprite */
    sf::Sprite sprite;
    const sf::FloatRect hitbox;

    /* Animation */
    sf::Vector2f src_size;
    std::string key1;
    std::string key2;
    bool change_animation_flag = true;
    sf::Clock animation_clock;
    const float animation_speed = 0.125;
    int animation_stage = 0;
    sf::Vector2f stages_count;
};


#endif
