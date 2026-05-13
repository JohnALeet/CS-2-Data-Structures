#pragma once
#include <string>
#include <iostream>
#include "combatant.h"

using namespace std;

namespace dungeon
{

class Enemy : public Combatant
{
protected:
    std::string enemyType;
    bool boss;

public:
    Enemy(std::string para = "Dungeon Enemy", 
          std::string desc = "A hostile creature blocks your path", 
          int helf = 75, 
          int atk = 20, 
          std::string type = "Normal Enemy", 
          bool isBoss = false):
        Combatant(para, desc, helf, atk), enemyType(type), boss(isBoss){}

    virtual ~Enemy(){}

    std::string getEnemyType() {return enemyType;}
    bool isBoss() {return boss;}

    void setEnemyType(std::string type){enemyType = type;}
    void setBoss(bool isBoss){boss = isBoss;}

    virtual void enemyIntro()
    {
        if (boss == true)
        {
            cout << "The boss appears: " << name << "!" << endl;
        }
        else
        {
            cout << "An enemy appears: " << name << "!" << endl;
        }
    }

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }

    // bool operator==(const Enemy& rhs);
    // bool operator!=(const Enemy& rhs);
    // bool operator<(const Enemy& rhs);
    // bool operator>(const Enemy& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Enemy& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Description: " << obj.description << endl;
        os << "Health: " << obj.health << endl;
        os << "Attack Power: " << obj.attackPower << endl;
        os << "Enemy Type: " << obj.enemyType << endl;
        os << "Boss: ";

        if (obj.boss == true)
        {
            os << "Yes" << endl;
        }
        else
        {
            os << "No" << endl;
        }

        return os;
    }
};

class Goblin : public Enemy
{
public:
    Goblin(std::string temp = "Cave Goblin"):
        Enemy(temp, "Just a lil guy", 50, 15, "Goblin", false){}

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }
};

class Skeleton : public Enemy
{
public:
    Skeleton(std::string temp = "Old Skeleton"):
        Enemy(temp, "He's dead, Jim.", 70, 25, "Skeleton", false){}

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }
};

class Troll : public Enemy
{
public:
    Troll(std::string temp = "Bridge Troll"):
        Enemy(temp, "A massive troll guarding the path ahead", 120, 35, "Troll", false){}

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }
};

class FinalBoss : public Enemy
{
public:
    FinalBoss(std::string temp = "Dungeon Lord"):
        Enemy(temp, "The final boss of the dungeon", 200, 50, "Final Boss", true){}

    void takeDamage(int damage) override
    {
        Combatant::takeDamage(damage);
    }
};

}