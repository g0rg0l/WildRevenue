#include "StructureHolder.h"

StructureHolder::StructureHolder()
{
    add(shops::types::blacksmith_shop, {20*16, 80*16});
    add(shops::types::herbalist_shop, {46*16, 35*16});
    add(shops::types::potion_maker_shop, {100*16, 100*16});
}

void StructureHolder::add(shops::types structure_type, sf::Vector2f pos)
{
    auto structureToAdd = shops::create(structure_type, pos);
    structures.push_back(structureToAdd);

    for (auto& hitbox : structureToAdd->hitboxes)
        hitboxes.push_back(hitbox);
}

void StructureHolder::drawUpper(sf::RenderTarget &target) const
{
    for (auto& structure : structures)
        structure->drawUpper(target);
}

void StructureHolder::drawBottom(sf::RenderTarget &target) const
{
    for (auto& structure : structures)
        structure->drawBottom(target);
}
