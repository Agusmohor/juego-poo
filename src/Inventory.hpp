#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include "Item.hpp"

class inventory {
    std::vector<Item> items;
public:
    inventory();
    ~inventory();

    bool addItem(int slot);
    bool removeItem(int slot);

    void selectItem(int slot);
    void useItem();

    Item& getItem(int slot);
};


#endif