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

void Inventory::add(const std::shared_ptr<ItemBase>& itemToadd)
{
    for (auto& item : data)
    {
        if (item)
        {
            if (item->get_id() == itemToadd->get_id() && item->get_count() < stack)
            {
                item->increase(itemToadd->get_count());
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
        data[id].reset();

//        reshape();
    }
}

void Inventory::transfuse(int id, float delta)
{
    if (data[id])
    {
        if (delta < 0)
        {
            /* Поиск предметов с таким же id */
            for(int i = 0; i < data.size(); ++i)
            {
                if (data[i] && i != id)
                {
                    if (data[id]->get_id() == data[i]->get_id() && data[i]->get_count() < stack)
                    {
                        data[i]->increase(1);

                        data[id]->decrease(1);
                        if (data[id]->get_count() == 0) pop(id);

                        return;
                    }
                }
            }

            /* Поиск пустых мест */
            for(auto& item : data)
            {
                if (!item)
                {
                    item = items::create(data[id]->get_id());

                    data[id]->decrease(1);
                    if (data[id]->get_count() == 0) pop(id);

                    return;
                }
            }
        }
        if (delta > 0)
        {
            for(int i = 0; i < data.size(); ++i)
            {
                if (data[i] && i != id)
                {
                    if (data[id]->get_id() == data[i]->get_id() && data[id]->get_count() < stack)
                    {
                        data[id]->increase(1);
                        data[i]->decrease(1);

                        if (data[i]->get_count() == 0) pop(i);

                        return;
                    }
                }
            }
        }
    }
}
