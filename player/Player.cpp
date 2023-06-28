#include "Player.h"

Player::Player()
{
    /* Загрузка изображений */
    TextureHolder& textureHolder = TextureHolder::getInstance();

    textureHolder.loadFromFile("../player/src/idle/left.png","player_left_idle");
    textureHolder.loadFromFile("../player/src/idle/right.png","player_right_idle");
    textureHolder.loadFromFile("../player/src/idle/up.png","player_up_idle");
    textureHolder.loadFromFile("../player/src/idle/down.png","player_down_idle");

    textureHolder.loadFromFile("../player/src/walk/left.png","player_left_walk");
    textureHolder.loadFromFile("../player/src/walk/right.png","player_right_walk");
    textureHolder.loadFromFile("../player/src/walk/up.png","player_up_walk");
    textureHolder.loadFromFile("../player/src/walk/down.png","player_down_walk");

    auto texture = textureHolder.getResource("player_down_idle");
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 16, 36));

    sprite.setPosition(0, 0);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Player::update(float dt, const std::vector<sf::FloatRect> &wallBounds)
{
    update_movement(dt, wallBounds);
    update_sprite();
}

void Player::update_sprite()
{
    if (animation_clock.getElapsedTime().asSeconds() >= animation_speed)
    {
        animation_clock.restart();

        sf::Texture* new_texture;
        TextureHolder& textureHolder = TextureHolder::getInstance();

        if (isMoving)
        {
            animation_stage = (++animation_stage) % 6;
            new_texture = textureHolder.getResource("player_" + direction + "_walk");
        }
        else
        {
            animation_stage = (++animation_stage) % 5;
            new_texture = textureHolder.getResource("player_" + direction + "_idle");
        }

        sprite.setTexture(*new_texture);
        sprite.setTextureRect(sf::IntRect(
                animation_stage * 16,
                0, 16, 36
        ));
    }
}

void Player::update_movement(float dt, const std::vector<sf::FloatRect> &wallBounds)
{
    sf::Vector2f acceleration;
    bool move_flag = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    { acceleration.y -= speed; direction = "up"; move_flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    { acceleration.y += speed; direction = "down"; move_flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    { acceleration.x -= speed; direction = "left"; move_flag = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    { acceleration.x += speed; direction = "right"; move_flag = true; }

    isMoving = move_flag;

    if (acceleration.x != 0 && acceleration.y != 0) acceleration *= diagonal_move_damping_coef;
    velocity += acceleration;

    check_for_collisions(dt, wallBounds);
    sprite.move(velocity * dt);

    velocity *= velocity_damping_coef;
}

void Player::check_for_collisions(float dt, const std::vector<sf::FloatRect> &wallBounds)
{
    sf::FloatRect player_global_bounds = get_bounds();
    sf::FloatRect player_hitbox_bounds = get_hitbox();

    sf::FloatRect player_next_pos(
            player_global_bounds.left + velocity.x * dt,
            player_global_bounds.top + velocity.y * dt,
            player_global_bounds.width,
            player_global_bounds.height
    );
    sf::FloatRect hitbox_next_pos(
            player_next_pos.left,
            player_next_pos.top + player_next_pos.height / 2,
            player_next_pos.width,
            player_next_pos.height / 2
    );

    for (auto& cur_wallBounds : wallBounds)
        if (cur_wallBounds.intersects(hitbox_next_pos))
        {
            // Bottom collision
            if (player_hitbox_bounds.top < cur_wallBounds.top
                && player_hitbox_bounds.top + player_hitbox_bounds.height < cur_wallBounds.top + cur_wallBounds.height
                && player_hitbox_bounds.left < cur_wallBounds.left + cur_wallBounds.width
                && player_hitbox_bounds.left + player_hitbox_bounds.width > cur_wallBounds.left)
            {
                velocity.y = 0.f;
                sprite.setPosition(player_hitbox_bounds.left, cur_wallBounds.top - 2*player_hitbox_bounds.height);
            }
            // Top collision
            else if (player_hitbox_bounds.top > cur_wallBounds.top
                     && player_hitbox_bounds.top + player_hitbox_bounds.height > cur_wallBounds.top + cur_wallBounds.height
                     && player_hitbox_bounds.left < cur_wallBounds.left + cur_wallBounds.width
                     && player_hitbox_bounds.left + player_hitbox_bounds.width > cur_wallBounds.left)
            {
                velocity.y = 0.f;
                sprite.setPosition(player_hitbox_bounds.left, cur_wallBounds.top + cur_wallBounds.height - player_hitbox_bounds.height);
            }
            // Right collision
            else if (player_hitbox_bounds.left < cur_wallBounds.left
                     && player_hitbox_bounds.left + player_hitbox_bounds.width < cur_wallBounds.left + cur_wallBounds.width
                     && player_hitbox_bounds.top < cur_wallBounds.top + cur_wallBounds.height
                     && player_hitbox_bounds.top + player_hitbox_bounds.height > cur_wallBounds.top)
            {
                velocity.x = 0.f;
                sprite.setPosition(cur_wallBounds.left - player_hitbox_bounds.width, player_hitbox_bounds.top - player_hitbox_bounds.height);
            }
            // Left collision
            else if (player_hitbox_bounds.left > cur_wallBounds.left
                     && player_hitbox_bounds.left + player_hitbox_bounds.width > cur_wallBounds.left + cur_wallBounds.width
                     && player_hitbox_bounds.top < cur_wallBounds.top + cur_wallBounds.height
                     && player_hitbox_bounds.top + player_hitbox_bounds.height > cur_wallBounds.top)
            {
                velocity.x = 0.f;
                sprite.setPosition(cur_wallBounds.left + cur_wallBounds.width, player_hitbox_bounds.top - player_hitbox_bounds.height);
            }
        }
}

sf::FloatRect Player::get_bounds() const
{
    return sprite.getGlobalBounds();
}

sf::FloatRect Player::get_hitbox() const
{
    sf::FloatRect bounds = get_bounds();

    sf::FloatRect hitbox (
            bounds.left,
            bounds.top + bounds.height / 2,
            bounds.width,
            bounds.height / 2
    );

    return hitbox;
}
