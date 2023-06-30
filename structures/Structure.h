#ifndef GAME_STRUCTURE_H
#define GAME_STRUCTURE_H

#include <SFML/Graphics.hpp>
#include "../engine/TextureHolder.h"
#include <string>

class Structure
{
public:
    explicit Structure(const std::string& srcDirName, sf::Vector2f pos);
    virtual ~Structure() = default;
    void moveHitboxes(sf::Vector2f pos);

    void drawUpper(sf::RenderTarget& target) const;
    void drawBottom(sf::RenderTarget& target) const;

protected:
    sf::Sprite upper_layer;
    sf::Sprite bottom_layer;

public:
    std::vector<sf::FloatRect> hitboxes;
};


#endif
