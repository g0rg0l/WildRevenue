#include "Trader.h"


Trader::Trader(const std::string &src, sf::Vector2f stages,
               sf::FloatRect hitbox, sf::Vector2f pos)
    : hitbox(hitbox), stages_count(stages)
{
    TextureHolder& textureHolder = TextureHolder::getInstance();
    key1 = "trader_" + src + "_state1";
    key2 = "trader_" + src + "_state2";

    textureHolder.loadFromFile("../entity/src/traders/" + src + "/state1.png", key1);
    textureHolder.loadFromFile("../entity/src/traders/" + src + "/state2.png", key2);

    auto texture = textureHolder.getResource(key1);
    src_size = {(float)texture->getSize().x / stages.x, (float)texture->getSize().y};

    sprite.setTexture(*texture);
    sprite.setTextureRect({
        0, 0,
        (int) ((float) texture->getSize().x / stages.x),
        (int) texture->getSize().y
    });
    setPositionByHitbox(pos);
}

void Trader::update()
{
    if (animation_clock.getElapsedTime().asSeconds() >= animation_speed)
    {
        animation_clock.restart();
        sf::Texture* texture;
        TextureHolder& textureHolder = TextureHolder::getInstance();

        if (change_animation_flag)
        {
            animation_stage = (++animation_stage) % (int)stages_count.x;
            texture = textureHolder.getResource(key1);
        }
        else
        {
            animation_stage = (++animation_stage) % (int)stages_count.y;
            texture = textureHolder.getResource(key2);
        }

        change_animation_flag = (animation_stage == 0) ? !change_animation_flag : change_animation_flag;
        sprite.setTexture(*texture);
        sprite.setTextureRect(sf::IntRect(
                animation_stage * (int)src_size.x,0,
                (int)src_size.x, (int)src_size.y
        ));
    }
}

void Trader::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Trader::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Trader::setPositionByHitbox(sf::Vector2f pos)
{
    sf::Vector2f final_position = {
        pos.x - hitbox.left,
        pos.y - hitbox.top
    };

    sprite.setPosition(final_position);
}
