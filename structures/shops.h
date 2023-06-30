#ifndef GAME_SHOPS_H
#define GAME_SHOPS_H

#include "Structure.h"
#include <memory>

namespace shops
{
    enum class types
    {
        blacksmith_shop,
        herbalist_shop,
        mistery_shop,
        potion_maker_shop
    };

    std::shared_ptr<Structure> create(types type, sf::Vector2f pos = {0, 0});
}

namespace shops
{
    class BlacksmithShop : public Structure
    {
    public:
        explicit BlacksmithShop(sf::Vector2f pos) : Structure("blacksmith_shop", pos)
        {
            hitboxes.emplace_back(14, 61, 16, 11); // точильный камень
            hitboxes.emplace_back(50, 24, 17, 18); // печь
            hitboxes.emplace_back(31, 22, 14, 28); // стенд с бронёй
            hitboxes.emplace_back(19, 50, 19, 16); // блок с оружием
            hitboxes.emplace_back(26, 25, 3, 26); // левая балка
            hitboxes.emplace_back(70, 30, 3, 30); // правая балка
            hitboxes.emplace_back(56, 42, 15, 24); // кузнец

            moveHitboxes(pos);
        }
    };

    class HerbalistShop : public Structure
    {
    public:
        explicit HerbalistShop(sf::Vector2f pos) : Structure("herbalist_shop", pos)
        {
            hitboxes.emplace_back(0, 40, 25, 30); // левый столик
            hitboxes.emplace_back(87, 60, 3, 8); // склянка
            hitboxes.emplace_back(90, 71, 12, 14); // котёл
            hitboxes.emplace_back(95, 46, 10, 18); // горшок
            hitboxes.emplace_back(28, 22, 64, 29); // палатка
            hitboxes.emplace_back(29, 46, 4, 9); // левая балка
            hitboxes.emplace_back(87, 46, 4, 9); // правая балка
            hitboxes.emplace_back(29, 55, 26, 24); // травник

            moveHitboxes(pos);
        }
    };

    class PotionMakerShop : public Structure
    {
    public:
        explicit PotionMakerShop(sf::Vector2f pos) : Structure("potion_maker_shop", pos)
        {
            hitboxes.emplace_back(17, 15, 64, 37); // палатка
            hitboxes.emplace_back(1, 49, 9, 36); // 1 левый столик
            hitboxes.emplace_back(10, 49, 16, 21); // 2 левый столик
            hitboxes.emplace_back(76, 58, 10, 18); // верхний куст
            hitboxes.emplace_back(86, 42, 10, 18); // нижний куст
            hitboxes.emplace_back(50, 51, 25, 21); // зельевар

            moveHitboxes(pos);
        }
    };

    class MisteryShop : public Structure
    {
    public:
        explicit MisteryShop(sf::Vector2f pos) : Structure("mistery_shop", pos)
        {
            hitboxes.emplace_back(0, 16, 14, 33);
            hitboxes.emplace_back(14, 16, 16, 25);
            hitboxes.emplace_back(30, 16, 16, 33);

            moveHitboxes(pos);
        }
    };
}

#endif
