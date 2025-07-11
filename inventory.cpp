#include "inventory.h"
#include <iostream>

void Inventory::addItem(const Item& item) {
    items.push_back(item);
    std::cout << "Item added: " << item.getName() << std::endl;
}

void Inventory::removeItem(const std::string& itemName) {
    auto it = std::remove_if(items.begin(), items.end(), 
        [&itemName](const Item& item) { return item.getName() == itemName; });
    
    if (it != items.end()) {
        items.erase(it, items.end());
        std::cout << "Item removed: " << itemName << std::endl;
    } else {
        std::cout << "Item not found: " << itemName << std::endl;
    }
}

void Inventory::listItems() const {
    if (items.empty()) {
        std::cout << "Inventory is empty." << std::endl;
        return;
    }
    
    std::cout << "Inventory items:" << std::endl;
    for (const auto& item : items) {
        std::cout << "Name: " << item.getName() 
                  << ", Quantity: " << item.getQuantity() 
                  << ", Price: " << item.getPrice() << std::endl;
    }
}