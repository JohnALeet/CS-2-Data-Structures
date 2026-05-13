#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "combatant.h"
#include "item.h"

using namespace std;

namespace dungeon
{

class Player : public Combatant
{
protected:
    std::vector<Item> inventory;

public:
    Player(std::string para = "Dungeon Hero", std::string desc = "A brave dungeon explorer", int helf = 100, int atk = 25):
        Combatant(para, desc, helf, atk){}

    virtual ~Player(){}

    void addToInventory(Item item)
    {
        inventory.push_back(item);
    }

    void showInventory()
    {
        if (inventory.empty())
        {
            cout << "Inventory is empty." << endl;
            return;
        }

        cout << "Inventory:" << endl;

        for (int i = 0; i < inventory.size(); i++)
        {
            cout << i + 1 << ". " << inventory[i].getName() << endl;
        }
    }

    int inventorySize()
    {
        return inventory.size();
    }

    Item getInventoryItem(int index)
    {
        if (index < 0 || index >= inventory.size())
        {
            cout << "Invalid inventory index." << endl;
            return Item();
        }

        return inventory[index];
    }

    void removeInventoryItem(int index)
    {
        if (index < 0 || index >= inventory.size())
        {
            cout << "Invalid inventory index." << endl;
            return;
        }

        inventory.erase(inventory.begin() + index);
    }

    void useInventoryItem(int index)
    {
        if (index < 0 || index >= inventory.size())
        {
            cout << "Invalid inventory index." << endl;
            return;
        }

        Item item = inventory[index];

        if (item.getEffect() == "heal")
        {
            heal(item.getValue());
            cout << name << " used " << item.getName() << " and healed for " << item.getValue() << "." << endl;
            removeInventoryItem(index);
        }
        else if (item.getEffect() == "attack")
        {
            boostAttack(item.getValue());
            cout << name << " used " << item.getName() << " and gained " << item.getValue() << " attack power." << endl;
            removeInventoryItem(index);
        }
        else
        {
            cout << item.getName() << " had no effect." << endl;
            removeInventoryItem(index);
        }
    }

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Description: " << obj.description << endl;
        os << "Health: " << obj.health << endl;
        os << "Attack Power: " << obj.attackPower << endl;
        os << "Inventory Size: " << obj.inventory.size() << endl;
        return os;
    }
};

}