#ifndef ITEM_HPP
#define ITEM_HPP

#include "Player.hpp"
#include <string>

class Item {
    std::string name;
    bool stackeable;
public:
    Item(const std::string &name, bool stackeable) : name(name), stackeable(stackeable) {};
    virtual ~Item();

    const std::string& getName() const {return name;}
    const bool getStackeable() const {return stackeable;}

    virtual void use(player& player) = 0;

};


#endif