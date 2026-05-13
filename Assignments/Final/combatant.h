#pragma once
#include <string>
#include <iostream>
#include "character.h"

using namespace std;

namespace dungeon
{

class Combatant : public Character
{
protected:
    int health;
    int attackPower;

public:
    Combatant(std::string para = "Unknown Combatant", std::string desc = "A mysterious fighter", int helf = 100, int atk = 25):
        Character(para, desc), health(helf), attackPower(atk){}

    virtual ~Combatant(){}

    int getHealth() const {return health;}
    int attack() const {return attackPower;}
    int getAttackPower() const {return attackPower;}

    void setHealth(int helf)
    {
        health = helf;

        if (health < 0)
        {
            health = 0;
        }
    }

    void setAttackPower(int atk)
    {
        attackPower = atk;
    }

    virtual void takeDamage(int damage)
    {
        health -= damage;

        if (health < 0)
        {
            health = 0;
        }
    }

    virtual void heal(int amount)
    {
        health += amount;
    }

    virtual void boostAttack(int amount)
    {
        attackPower += amount;
    }

    bool isAlive() const
    {
        return health > 0;
    }

    virtual void displayHealth() const
    {
        cout << name << " has " << health << " health." << endl;
    }

    virtual void attackTarget(Combatant& target)
    {
        cout << name << " attacks " << target.getName() << " for " << attackPower << " damage!" << endl;
        target.takeDamage(attackPower);
        target.displayHealth();
    }

    virtual void fightRound(Combatant& opponent)
    {
        if (isAlive() && opponent.isAlive())
        {
            attackTarget(opponent);
        }

        if (opponent.isAlive() && isAlive())
        {
            opponent.attackTarget(*this);
        }
    }

    virtual void fightUntilDefeated(Combatant& opponent)
    {
        cout << "Combat begins!" << endl;
        cout << name << " vs. " << opponent.getName() << endl;

        while (isAlive() && opponent.isAlive())
        {
            cout << endl;
            fightRound(opponent);
        }

        cout << endl;

        if (isAlive())
        {
            cout << name << " defeated " << opponent.getName() << "!" << endl;
        }
        else
        {
            cout << name << " was defeated by " << opponent.getName() << "!" << endl;
        }
    }

    //Combatant operator+(int nums);
    //Combatant operator-(int nums);
    //Combatant operator*(int nums);

    friend std::ostream& operator<<(std::ostream& os, const Combatant& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Description: " << obj.description << endl;
        os << "Health: " << obj.health << endl;
        os << "Attack Power: " << obj.attackPower << endl;
        return os;
    }
};

}