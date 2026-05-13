#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace dungeon
{

class Item
{
protected:
    std::string name;
    std::string effect;
    int value;

public:
    Item(std::string para = "Unknown Item", std::string eff = "none", int val = 0):
        name(para), effect(eff), value(val){}

    virtual ~Item(){}

    std::string getName() {return name;}
    std::string getEffect() {return effect;}
    int getValue() {return value;}

    void setName(std::string para){name = para;}
    void setEffect(std::string eff){effect = eff;}
    void setValue(int val){value = val;}

    virtual void describe()
    {
        cout << "Item: " << name << endl;
        cout << "Effect: " << effect << endl;
        cout << "Value: " << value << endl;
    }

    bool operator==(const Item& rhs)
    {
        return name == rhs.name && effect == rhs.effect && value == rhs.value;
    }

    bool operator!=(const Item& rhs)
    {
        return !(*this == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Item& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Effect: " << obj.effect << endl;
        os << "Value: " << obj.value << endl;
        return os;
    }
};

}