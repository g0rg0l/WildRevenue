#include "Inventory.h"

std::vector<std::string> Inventory::get_id_vector() const
{
    std::vector<std::string> result;
    result.reserve(data.size());

    for (auto& item : data)
    {
        if (item) result.push_back(item->get_id());
        else result.emplace_back("");
    }

    return result;
}

std::vector<int> Inventory::get_count_vector() const
{
    std::vector<int> result;
    result.reserve(data.size());

    for (auto& item : data)
    {
        if (item) result.push_back(item->get_count());
        else result.emplace_back(0);
    }

    return result;
}

std::string Inventory::get_item_name(int id) const { return data[id]->get_name(); }
int Inventory::get_item_count(int id) const { return data[id]->get_count(); }


bool Inventory::can_be_placed_in(const std::string &item_id) const
{
    for (auto& item : data)
    {
        if (item)
        {
            if (item->get_id() == item_id && item->get_count() < stack)
                return true;
        }
        else return true;
    }

    return false;
}

void Inventory::add(Item *itemToadd)
{
    for (auto& item : data)
    {
        if (item)
        {
            if (item->get_id() == itemToadd->get_id() && item->get_count() < stack)
            {
                item->increase(itemToadd->get_count());
                delete itemToadd;

                break;
            }
        }
        else
        {
            item = itemToadd;
            break;
        }
    }
}

void Inventory::pop(int id)
{
    if (data[id])
    {
        delete data[id];
        data[id] = nullptr;

        reshape();
    }
}

void Inventory::reshape()
{
    std::vector<Item*> new_data(5);
    for (int i = 0, i_ = 0; i < data.size(); ++i)
        if (data[i]) new_data[i_++] = data[i];

    std::swap(data, new_data);
}

Inventory::~Inventory()
{
    for (auto& item : data)
        delete item;
}
