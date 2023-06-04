#include "Item.h"

#include <utility>

Item::Item(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{

}

std::string Item::get_id() const { return id; }
int Item::get_count() const { return count; }
std::string Item::get_name() const { return name; }

void Item::increase(int n) { count += n; }
void Item::decrease(int n) { count -= n; }
