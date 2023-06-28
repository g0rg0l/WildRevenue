#ifndef UNTITLED_INVENTORY_H
#define UNTITLED_INVENTORY_H

#include <vector>

#include "items/items.h"

class Inventory
{
public:
    [[nodiscard]] std::vector<std::string> get_id_vector() const;
    [[nodiscard]] std::vector<int> get_count_vector() const;

public:
    [[nodiscard]] bool can_be_placed_in(const std::string &item_id) const;

    void add(const std::shared_ptr<ItemBase>& itemToadd);
    void pop(int id);
    void transfuse(int id, float delta);

private:
    std::vector<std::shared_ptr<ItemBase>> data = { nullptr, nullptr, nullptr, nullptr, nullptr };
    const int stack = 16;
};


#endif
