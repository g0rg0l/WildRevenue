#include "ItemBase.h"

ItemBase::ItemBase(const std::string& id, std::string name, const std::string& src)
    : id(id), name(std::move(name)), src(src)
{
    TextureHolder& textureHolder = TextureHolder::getInstance();
    textureHolder.loadFromFile("../inventory/items/src/" + src + ".png", id);
}

std::string ItemBase::get_id() const { return id; }

int ItemBase::get_count() const { return count; }

std::string ItemBase::get_name() const { return name; }

void ItemBase::increase(int n) { count += n; }

void ItemBase::decrease(int n) { count -= n; }