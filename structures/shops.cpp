#include "shops.h"

namespace shops
{
    std::shared_ptr<Structure> create(types type, sf::Vector2f pos)
    {
        Structure* p_newStructure;
        switch (type)
        {
            case types::blacksmith_shop: p_newStructure = new BlacksmithShop(pos); break;
            case types::herbalist_shop: p_newStructure = new HerbalistShop(pos); break;
            case types::potion_maker_shop: p_newStructure = new PotionMakerShop(pos); break;
            case types::mistery_shop: p_newStructure = new MisteryShop(pos); break;

            default:  p_newStructure = nullptr; break;
        }

        return std::shared_ptr<Structure>(p_newStructure);
    }
}
