#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace dungeon
{

class Character
{
protected:
    std::string name;
    std::string description;

public:
    Character(std::string para = "Unknown Character", std::string desc = "No description"):
        name(para), description(desc){}

    virtual ~Character(){}

    std::string getName() const {return name;}
    std::string getDescription() const {return description;}

    void setName(std::string para){name = para;}
    void setDescription(std::string desc){description = desc;}

    virtual void introduce()
    {
        cout << name << ": " << description << endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Character& obj)
    {
        os << "Name: " << obj.name << endl;
        os << "Description: " << obj.description << endl;
        return os;
    }
};

}