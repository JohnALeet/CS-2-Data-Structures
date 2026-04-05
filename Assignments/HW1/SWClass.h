#pragma once
#include <string>


namespace starwars{


    class Jedi{

        private: std::string _name;
            int _health = 100;
            int _lightsaberSkill = 50;
            int _forcePower = 75;
            void fridayCatShirt (){_health = 600; _lightsaberSkill =6969; _forcePower = 4242;}


        public:
        std::string getName()  {return _name;}
        int getHealth() {return _health;}
        int getlightsaberSkill() {return _lightsaberSkill;}
        int getforcePower(){return _forcePower;}

        void setName(std::string name){_name = name;}
        void setHealth(int health){_health = health;}
        void setlightsaberSkill(int lightsaberSkill){_lightsaberSkill = lightsaberSkill;}
        void setforcePower(int forcePower){_forcePower = forcePower;}

        void saveToFile(std::string userFile);
        void loadFromFile(std::string userFile);

        Jedi (std::string name = "Jeremy 'Iceberg' Bergen", 
            int health = 100, 
            int lightsaberSkill = 69, 
            int forcePower = 42):
            _name(name), _health(health), 
            _lightsaberSkill(lightsaberSkill),
            _forcePower(forcePower)//"How fast does your car go?" "Oh, about 500 forcepower."
        {}

        int attack() {return _lightsaberSkill;}
        void takeDamage(int damage){_health -= damage;}
        int useForce( int power) {return _forcePower -= power;}

    };



class Sith{

    private:  std::string _nameSith;
        int _health = 120;
        int _lightsaberSkill = 60;

    public:
    Sith(std::string nameSith = "Anakin",
        int lightsaberSkill = 60,
        int health = 120) :
        _nameSith(nameSith), _health(health), _lightsaberSkill(lightsaberSkill)
    {}

    std::string getName() { return _nameSith; }
    int getHealth() { return _health; }
    int getlightsaberSkill() { return _lightsaberSkill; }

    void setName(const std::string& name){ _nameSith = name; }
    void setHealth(int h){ _health = h; }
    void setlightsaberSkill(int s){ _lightsaberSkill = s; }

    void takeDamage(int damage){_health -= damage;}
    int attack() {return _lightsaberSkill;}
};

}