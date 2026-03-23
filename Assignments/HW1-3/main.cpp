#include <iostream>
#include "SWClass.h"
#include <random>

using namespace std;
using namespace starwars;

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
        int dmg = select ->attack();
        bad_guy->takeDamage(dmg);

        cout << select->getName() << " attacks for " << dmg << " damage!\n";
        cout << bad_guy->getName() << "'s health is: " << bad_guy->getHealth() << "\n";
        if (bad_guy->getHealth() <= 0)
            break;

        int dmgBG = bad_guy->attack();
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

