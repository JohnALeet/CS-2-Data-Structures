#include <iostream>
#include "SWClass.h"
#include <random>
#include <fstream>

using namespace std;
using namespace starwars;


void Character::saveToFile(std::string userFile)
{
    std::ofstream fout(userFile);
    if(!fout) return;

    fout << name << "\n";
    fout << health << "\n";
    fout << attackPower << "\n";


}

void Character::loadFromFile(string userFile)
{
    ifstream fin(userFile);
    if (!fin) return; //Base case!

    getline(fin, name);
    fin >> health;
    fin >> attackPower;
}


int main()
{

    string name;
    cout <<"Enter your name: \n";
    getline(cin, name);

    int temp;
    cout << "Choose your Jedi: \n";
    cout << "1.) Guardian\n";
    cout << "2.) Consular\n";
    cin >> temp;
    
    
    //This is Mersenne Twister RNG.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    std::uniform_int_distribution<int> critHit(1,100);

    Character* select = nullptr;
    if (temp == 1) select = new Guardian(name);
    else select = new Consular(name);

    Character* bad_guy = nullptr;
    int a = dist(gen);
        if ( a == 0) bad_guy = new Acolyte("Acolyte");
        else bad_guy = new Darth("Darth");

    cout << "\n""Fight!""\nThe fate of the galaxy rests in your hands!""\n";

    while ( select -> getHealth() > 0 && bad_guy -> getHealth() > 0 )
    {
        int dmg = select -> attack();
        int roll = critHit(gen);
        if (roll <= 20)//This is just a critical hit I wanted to add to the combat loop.
        {
            dmg = dmg * 2;
            cout << "CRITICAL HIT! It's super effective!\n";
        }
        bad_guy->takeDamage(dmg);

        cout << select->getName() << " attacks for " << dmg << " damage!\n";
        cout << bad_guy->getName() << "'s health is: " << bad_guy->getHealth() << "\n";
        if (bad_guy->getHealth() <= 0)
            break;

        int dmgBG = bad_guy->attack();
        int roll2 = critHit(gen);
        if (roll2 <= 10)//Bad guys don't get as much good luck.
        {
            dmgBG = dmgBG * 2;
            cout << "CRITICAL HIT! It's super effective!\n";
        }
        select->takeDamage(dmgBG);

        cout << bad_guy->getName() << " attacks and does " << dmgBG << " damage!" << "\n";
        cout << select->getName() << "'s health is: " << select->getHealth() << "\n";

    }

    if (select->getHealth()>0 && bad_guy->getHealth() <=0 ) cout << "\nYou won! The galaxy is safe once more.";
    else cout << "\nYou've lost. The Sith have triumphed on this day!";

    delete select;
    delete bad_guy;

    return 0;

}

