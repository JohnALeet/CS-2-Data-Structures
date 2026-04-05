#include <iostream>
#include "SWClass.h"
#include <fstream>

using namespace std;
using namespace starwars;

int main(){

    string name;
    cout <<"Enter your name: ";
    getline(cin, name);

    Jedi jed1(name, 100, 50,75);
    string file ="StarWars_save.txt";
    jed1.saveToFile(file);

    Jedi jediSave;
    jediSave.loadFromFile(file);

    cout<< "Name: " << jediSave.getName()<< "\n";
    cout<< "Health: " << jediSave.getHealth()<< "\n";
    cout<< "Lightsaber Skill: " << jediSave.getlightsaberSkill()<< "\n";
    cout<< "Force: " << jediSave.getforcePower()<< "\n";

    Sith sit1("Count Dooku", 120, 60);

    cout << "\n""Fight!""\nThe fate of the galaxy rests in your hands!""\n";

    while (jediSave.getHealth() > 0 && sit1.getHealth()>0)
    {
        int jedDmg = jediSave.attack();//Jedi gets to go first, because he's a good guy.
        sit1.setHealth(jedDmg);

            cout << jediSave.getName() << " attacks for " << jedDmg << " damage!\n";
            cout << sit1.getName() << "'s health is: " << sit1.getHealth() << "\n";
                if (sit1.getHealth() <= 0)//This breaks the loop if the Sith dies.
                    break;

        int sithDMG = sit1.attack();
        jediSave.setHealth(jediSave.getHealth()-sithDMG);

        cout << sit1.getName() << " attacks and does " << sithDMG << " damage!" << "\n";
        cout << jediSave.getName() << "'s health is: " << jediSave.getHealth() << "\n";

    }

    if (jediSave.getHealth()>0 && sit1.getHealth() <=0 ) cout << "\nYou won! The galaxy is safe once more.";
    else cout << "\nYou've lost. The Sith have triumphed on this day!";

    return 0;

}

void Jedi::saveToFile(std::string userFile)
{
    ofstream fout(userFile);

   fout << _name << "\n"
    << _health << "\n"
    << _lightsaberSkill << "\n"
    << _forcePower << "\n";


}

void Jedi::loadFromFile(string userFile)
{
    ifstream fin(userFile);

    getline(fin, _name);
    fin >> _health;
    fin >> _lightsaberSkill;
    fin >> _forcePower;
}

