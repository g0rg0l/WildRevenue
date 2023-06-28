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
}