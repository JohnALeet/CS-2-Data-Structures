#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace starwars
{

class Character
{
protected:
    std::string name;
    int health;
    int attackPower;

public: 
    Character(std::string para = "The Anchorman: Jeremy Bergendy", int helf = 100, int atk = 50): 
        name(para), health(helf), attackPower(atk){}
    
    virtual ~Character(){}

    std::string getName() {return name;}
    int getHealth() {return health;}
    int attack() {return attackPower;}

    void setName(std::string para){name = para;}
    void setHealth(int helf){health=helf;}
    void setAttackPower(int atk){attackPower = atk;}

    virtual void takeDamage(int damage)
    {
        health -= damage;
        if (health < 0) health =0;

    }
    
    void saveToFile(std::string userFile);
    void loadFromFile(std::string userFile);

    Character operator+(int nums);
    Character operator-(int nums);
    Character operator*(int nums);
    
    friend std::ostream& operator<<(std::ostream& os, const Character& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Health: " << obj.health << endl;
        os << "Attack Power: " << obj.attackPower << endl;
        return os;
    };

};
class Jedi : public Character
    {
protected:
        int forcePower;

        
public:
        Jedi(std::string para = "Jeremy 'Iceberg' Bergen", int helf = 100, int atk = 69, int powa = 69):
            Character(para, helf, atk), forcePower(powa) {}




virtual void takeDamage(int damage)
       {
        Character::takeDamage(damage);
       }
       
       bool operator==(const Jedi& rhs);
       bool operator!=(const Jedi& rhs);
       bool operator<(const Jedi& rhs);
       bool operator>(const Jedi& rhs);
    
    };

class Guardian : public Jedi
{
public:
        Guardian(std::string temp = "Randy Savage"):
        Jedi(temp, 150, 70, 75){}

        void takeDamage(int damage) override
        {
            Character::takeDamage(damage);
        }

};

class Consular : public Jedi
{
public:
        Consular(std::string temp = "Bilbo Bergens"):
        Jedi(temp, 100, 50, 120){}

        void takeDamage(int damage) override
        {
            Character::takeDamage(damage);
        }

};

class Sith: public Character
{
public:
    Sith(std::string temp = "hamBergenler", int helf = 120, int atk = 60):
        Character(temp, helf, atk){}

    void takeDamage(int damage) override
    {
        Character::takeDamage(damage);
    }

    bool operator==(const Sith& rhs);
    bool operator!=(const Sith& rhs);
    bool operator<(const Sith& rhs);
    bool operator>(const Sith& rhs);
};
class Acolyte : public Sith
{
public:
    Acolyte(std::string temp = "Beef Bergenoff"):
        Sith(temp, 80, 40){}
};

class Darth : public Sith
{
public:
    Darth(std::string temp = "Bergenator"):
        Sith(temp, 200, 100){}
};

}