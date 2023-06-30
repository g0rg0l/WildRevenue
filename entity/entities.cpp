#include "entities.h"

namespace entity
{
    std::shared_ptr<CollectableEntity> create(collectable type, sf::Vector2f pos = {0, 0})
    {
        CollectableEntity* p_newEntity;
        switch (type)
        {
            case collectable::tomato: p_newEntity = new Tomato(pos); break;
            case collectable::potato: p_newEntity = new Potato(pos); break;
            case collectable::blue_flowers: p_newEntity = new BlueFlowers(pos); break;

            default:  p_newEntity = nullptr; break;
        }

        return std::shared_ptr<CollectableEntity>(p_newEntity);
    }

    std::shared_ptr<Trader> create(traders type, sf::Vector2f pos)
    {
        Trader* p_newEntity;
        switch (type)
        {
            case traders::blacksmith: p_newEntity = new BlackSmith(pos); break;
            case traders::herbalist: p_newEntity = new Herbalist(pos); break;
            case traders::potion_maker: p_newEntity = new PotionMaker(pos); break;

            default:  p_newEntity = nullptr; break;
        }

        return std::shared_ptr<Trader>(p_newEntity);
    }
}