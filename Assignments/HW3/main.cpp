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

Character Character::operator+(int nums)
{
    Character toReturn(name, health + nums, attackPower);
    return toReturn;
}

Character Character::operator-(int nums)
{
    int newHealth = health - nums;
    if (newHealth < 0)
        newHealth = 0;
    
    Character toReturn (name, newHealth, attackPower);
    return toReturn;
}
Character Character::operator*(int nums)
{
    Character toReturn(name, health, attackPower * nums);
    return toReturn;
}

bool Jedi::operator==(const Jedi& rhs)
{
    return health == rhs.health;
}

bool Jedi::operator!=(const Jedi& rhs)
{
    return  !(*this == rhs);
}

bool Jedi::operator<(const Jedi& rhs)
{
    return health < rhs.health;
}

bool Jedi::operator>(const Jedi& rhs)
{
    return health > rhs.health;
}

bool Sith::operator==(const Sith& rhs)
{
    return health == rhs.health;
}

bool Sith::operator!=(const Sith& rhs)
{
    return !(*this == rhs);
}

bool Sith::operator<(const Sith& rhs)
{
    return health < rhs.health;
}

bool Sith::operator>(const Sith& rhs)
{
    return health > rhs.health;
}



int main(int argc, char* argv[])
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

    Jedi j1("Yoda");
    Jedi j2("Mace Windu");
    if (j1 != j2)
    {
        cout << j1.getName() << "is not equal to " << j2.getName();
    }
    else
    cout << "print(""""All test cases passed!"""")"" Wait, what the hell? Wrong language!" << endl;


    Guardian g1("Obi-Wan");
    Guardian g2("Anakin");
    if (g1.getHealth() == g2.getHealth())
    {
    cout << "These two Jedi have the same amount of health.""\n";
    }
    else
    cout << "These two Jedi do not have equal health.""\n";

    Darth d1("Vader");
    Darth d2("Maul");

    Consular c1("Harry Potter");
    Acolyte a1("Gandalf");
    if (c1 > g1)
    {
        cout << c1.getName() << " doesn't belong in this universe!" << "\n";
    }
    else 
    cout << "Nothing suspicious to see here. Move along" "\n" << endl;

    if (a1 < d1)
    {
        cout << a1.getName() << ", you don't belong in this universe! Go home! You are drunk!" << "\n";
    }
    else
    cout << "That override works, too." << endl;
    

    if (d1 > d2)
    cout << d1.getName() << " has more health than " << d2.getName() << "\n";
    else
    cout << d2.getName() << " has more health than " << d1.getName() << "\n";

    Character* select = nullptr;
    if (temp == 1) select = new Guardian(name);
    else select = new Consular(name);

    Character* bad_guy = nullptr;
    int a = dist(gen);
        if ( a == 0) bad_guy = new Acolyte("Acolyte");
        else bad_guy = new Darth("Darth");

    cout << "Your fighter is: \n";
    cout << *select << endl;
    cout << "The enemy is: \n";
    cout << *bad_guy << endl;
    

    cout << "\n""Fight!""\nThe fate of the galaxy rests in your hands!""\n";


    while ( select -> getHealth() > 0 && bad_guy -> getHealth() > 0 )
    {
        int dmg = select -> attack();
        int roll = critHit(gen);
        if (roll <= 25)
        {
            Character crit = *select * 2;
            cout << "CRITICAL HIT! It's super effective!\n";
        }

        if (roll <= 35)//Random heal.
        {
            Character helf = *select + 15;
            cout << "You find inner strength and regenerate 15 health! \n";
        }
        *bad_guy = *bad_guy - dmg;

        cout << select->getName() << " attacks for " << dmg << " damage!\n";
        cout << bad_guy->getName() << "'s health is: " << bad_guy->getHealth() << "\n";
        if (bad_guy->getHealth() <= 0)
            break;

        int dmgBG = bad_guy->attack();
        int roll2 = critHit(gen);
        if (roll2 <= 15)//Bad guys don't get as much good luck.
        {
            Character crit = *bad_guy * 2;
            cout << "CRITICAL HIT! It's super effective!\n";
        }

        if (roll2 <= 25)
        {
            Character helf = *bad_guy + 25;
            cout << "The Sith has found inner strength. He regenerates 25 health! \n";
        }
        *select = *select - dmgBG;

        cout << bad_guy->getName() << " attacks and does " << dmgBG << " damage!" << "\n";
        cout << select->getName() << "'s health is: " << select->getHealth() << "\n";

    }

    if (select->getHealth()>0 && bad_guy->getHealth() <=0 ) cout << "\nYou won! The galaxy is safe once more.";
    else cout << "\nYou've lost. The Sith have triumphed on this day!";
    
    select->saveToFile("StarWars_save.txt");

    delete select;
    delete bad_guy;

    return 0;

}

