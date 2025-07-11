#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& name, int quantity, double price);

    std::string getName() const;
    int getQuantity() const;
    double getPrice() const;

    void setQuantity(int quantity);
    void setPrice(double price);

private:
    std::string name;
    int quantity;
    double price;
};

#endif // ITEM_H