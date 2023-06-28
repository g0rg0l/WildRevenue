#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include <string>
#include "../../engine/TextureHolder.h"

class ItemBase
{
public:
    ItemBase(const std::string& id, std::string name, const std::string& src);
    virtual ~ItemBase() = default;

public:
    virtual void increase(int n);
    virtual void decrease(int n);

public:
    [[nodiscard]] virtual std::string get_id() const;
    [[nodiscard]] virtual std::string get_name() const;
    [[nodiscard]] virtual int get_count() const;

protected:
    const std::string id;
    const std::string name;
    const std::string src;
    int count = 1;
};


#endif
