#pragma once
#include <string>
#include <iostream>
#include "enemy.h"
#include "item.h"

using namespace std;

namespace dungeon
{

class Room
{
protected:
    std::string description;
    Enemy* enemy;
    Item* item;
    bool treasureRoom;

public:
    Room(std::string desc = "An empty room", Enemy* en = nullptr, Item* it = nullptr, bool treasure = false):
        description(desc), enemy(en), item(it), treasureRoom(treasure){}

    virtual ~Room()
    {
        if (enemy != nullptr)
        {
            delete enemy;
            enemy = nullptr;
        }

        if (item != nullptr)
        {
            delete item;
            item = nullptr;
        }
    }

    std::string getDescription() {return description;}
    Enemy* getEnemy() {return enemy;}
    Item* getItem() {return item;}
    bool isTreasureRoom() {return treasureRoom;}

    void setDescription(std::string desc){description = desc;}
    void setEnemy(Enemy* en){enemy = en;}
    void setItem(Item* it){item = it;}
    void setTreasureRoom(bool treasure){treasureRoom = treasure;}

    bool hasEnemy()
    {
        return enemy != nullptr && enemy->isAlive();
    }

    bool hasItem()
    {
        return item != nullptr;
    }

    void removeEnemy()
    {
        if (enemy != nullptr)
        {
            delete enemy;
            enemy = nullptr;
        }
    }

    void removeItem()
    {
        if (item != nullptr)
        {
            delete item;
            item = nullptr;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Room& obj)
    {
        os << "Description: " << obj.description << endl;

        if (obj.enemy != nullptr && obj.enemy->isAlive())
        {
            os << "Enemy: " << obj.enemy->getName() << endl;
        }
        else
        {
            os << "Enemy: None" << endl;
        }

        if (obj.item != nullptr)
        {
            os << "Item: " << obj.item->getName() << endl;
        }
        else
        {
            os << "Item: None" << endl;
        }

        if (obj.treasureRoom == true)
        {
            os << "This room contains the final treasure." << endl;
        }

        return os;
    }

    bool operator==(const Room& rhs)
    {
        return description == rhs.description && treasureRoom == rhs.treasureRoom;
    }

    bool operator!=(const Room& rhs)
    {
        return !(*this == rhs);
    }
};

}