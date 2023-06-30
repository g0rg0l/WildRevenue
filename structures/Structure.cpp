#include "Structure.h"

Structure::Structure(const std::string& srcDirName, sf::Vector2f pos)
{
    TextureHolder& textureHolder = TextureHolder::getInstance();

    textureHolder.loadFromFile("../structures/src/" + srcDirName + "/upper.png",srcDirName + "_shop_upper");
    textureHolder.loadFromFile("../structures/src/" + srcDirName + "/bottom.png",srcDirName + "_shop_bottom");

    auto texture = textureHolder.getResource(srcDirName + "_shop_upper");
    upper_layer.setTexture(*texture);
    texture = textureHolder.getResource(srcDirName + "_shop_bottom");
    bottom_layer.setTexture(*texture);

    upper_layer.setPosition(pos);
    bottom_layer.setPosition({pos.x, pos.y + upper_layer.getGlobalBounds().height});
}

void Structure::drawUpper(sf::RenderTarget& target) const
{
    target.draw(upper_layer);
}

void Structure::drawBottom(sf::RenderTarget& target) const
{
    target.draw(bottom_layer);
}

void Structure::moveHitboxes(sf::Vector2f pos)
{
    for (auto& hitbox : hitboxes)
    {
        hitbox.left += pos.x;
        hitbox.top += pos.y;
    }
}
