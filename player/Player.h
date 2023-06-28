#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <cmath>

#include "../engine/TextureHolder.h"
#include "../inventory/Inventory.h"

class Player : public sf::Drawable
{
public:
    Player();

public:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void update(float dt, const std::vector<sf::FloatRect>& wallBounds);
    void update_sprite();
    void update_movement(float dt, const std::vector<sf::FloatRect>& wallBounds);
    void check_for_collisions(float dt, const std::vector<sf::FloatRect>& wallBounds);

public:
    sf::FloatRect get_bounds() const;
    sf::FloatRect get_hitbox() const;

private:
    /* Анимация */
    sf::Clock animation_clock;
    float animation_speed = 0.125;
    sf::Sprite sprite;
    int animation_stage = 0;

    /* Движение */
    sf::Vector2f velocity;
    const float diagonal_move_damping_coef = 0.707;
    const float velocity_damping_coef = 0.9;
    const float speed = 6;
    std::string direction = "down";
    mutable bool isMoving = false;

    /* Коллизия */
    const sf::FloatRect hitboxSizes = {0, 0, 16, 18};

public:
    Inventory inventory;
};

#endif
