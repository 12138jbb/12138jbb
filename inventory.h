#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "types/item.h"

class Inventory {
public:
    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    void listItems() const;

private:
    std::vector<Item> items;
};

#endif // INVENTORY_H