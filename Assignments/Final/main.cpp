#include <iostream>
#include <string>
#include "dungeon.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "room.h"

using namespace std;
using namespace dungeon;

void fightEnemy(Player& player, Enemy* enemy)
{
    int choice;

    if (enemy == nullptr)
    {
        return;
    }

    cout << endl;
    cout << "An enemy blocks your path!" << endl;
    enemy->enemyIntro();

    while (player.isAlive() && enemy->isAlive())
    {
        cout << endl;
        cout << "Your Health: " << player.getHealth() << endl;
        cout << enemy->getName() << " Health: " << enemy->getHealth() << endl;

        cout << endl;
        cout << "1. Attack" << endl;
        cout << "2. Show Inventory" << endl;
        cout << "3. Use Inventory Item" << endl;
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1)
        {
            player.attackTarget(*enemy);
        }
        else if (choice == 2)
        {
            player.showInventory();
            continue;
        }
        else if (choice == 3)
        {
            int itemNumber;

            player.showInventory();

            cout << "Enter item number: ";
            cin >> itemNumber;

            player.useInventoryItem(itemNumber - 1);
            continue;
        }
        else
        {
            cout << "Invalid choice. You lose your turn." << endl;
        }

        if (enemy->isAlive())
        {
            enemy->attackTarget(player);
        }
    }

    if (player.isAlive())
    {
        cout << endl;
        cout << "You defeated " << enemy->getName() << "!" << endl;
    }
    else
    {
        cout << endl;
        cout << "You were defeated by " << enemy->getName() << "." << endl;
    }
}

void handleRoomItem(Player& player, Dungeon& dungeon)
{
    Room* currentRoom = dungeon.getCurrentRoom();

    if (currentRoom == nullptr)
    {
        return;
    }

    if (!currentRoom->hasItem())
    {
        return;
    }

    int choice;

    cout << endl;
    cout << "You found an item: " << currentRoom->getItem()->getName() << endl;
    cout << "1. Pick up item" << endl;
    cout << "2. Use item now" << endl;
    cout << "3. Leave item" << endl;
    cout << "Choose: ";
    cin >> choice;

    if (choice == 1)
    {
        player.addToInventory(*(currentRoom->getItem()));
        dungeon.removeItemFromCurrentRoom();

        cout << "Item added to inventory." << endl;
    }
    else if (choice == 2)
    {
        Item* item = currentRoom->getItem();

        if (item->getEffect() == "heal")
        {
            player.heal(item->getValue());
            cout << player.getName() << " healed for " << item->getValue() << "." << endl;
        }
        else if (item->getEffect() == "attack")
        {
            player.boostAttack(item->getValue());
            cout << player.getName() << " gained " << item->getValue() << " attack power." << endl;
        }
        else
        {
            cout << "The item had no effect." << endl;
        }

        dungeon.removeItemFromCurrentRoom();
    }
    else
    {
        cout << "You leave the item behind." << endl;
    }
}

int main()
{
    string playerName;
    int choice;
    bool gameOver = false;

    cout << "===================================" << endl;
    cout << "          LORD OF THE RINGS          " << endl;
    cout << "===================================" << endl;

    cout << endl;
    cout << "Enter your character's name: ";
    getline(cin, playerName);

    Player player(playerName, "A weary traveler carrying the fate of Middle-earth", 100, 25);

    Dungeon dungeon;

    dungeon.addRoom(new Room
    (
        "You stand at the entrance of a cold stone dungeon.\n You hear the sound of orcs singing. Their voices bounce off the walls of the cave \nand form a cacophony of indistinguishable murmuring.",
        nullptr,
        nullptr,
        false
    ));

    dungeon.addRoom(new Room
    (
        "You enter a narrow stone opening. The Uruk-hai are unaware of your presence",
        new Goblin("Orc Snaga"),
        nullptr,
        false
    ));

    dungeon.addRoom(new Room
    (
        "You find an abandoned storage room.",
        nullptr,
        new Item("Health Potion", "heal", 25),
        false
    ));

    dungeon.addRoom(new Room
    (
        "You step onto an old stone bridge. \n It seems familiar, but you're not sure why.",
        new Troll("Morgoth Troll"),
        nullptr,
        false
    ));

    dungeon.addRoom(new Room
    (
        "You enter the treasure chamber. The spoils of war have been collected and stored here.\n Each glinting piece of wealth represents an innocent slain and village pillaged.",
        new FinalBoss("Uruk-hai Chieftan"),
        new Item("Final Treasure", "treasure", 0),
        true
    ));

    cout << endl;
    cout << "Welcome, " << player.getName() << "." << endl;
    cout << "Reach the treasure room to win." << endl;

    while (!gameOver && player.isAlive())
    {
        Room* currentRoom = dungeon.getCurrentRoom();

        if (currentRoom == nullptr)
        {
            cout << "There is no current room. Ending game." << endl;
            break;
        }

        cout << endl;
        cout << "-----------------------------------" << endl;
        dungeon.displayCurrentRoom();
        cout << "-----------------------------------" << endl;

        if (currentRoom->hasEnemy())
        {
            fightEnemy(player, currentRoom->getEnemy());

            if (!player.isAlive())
            {
                gameOver = true;
                break;
            }

            dungeon.removeEnemyFromCurrentRoom();
        }

        handleRoomItem(player, dungeon);

        if (currentRoom->isTreasureRoom())
        {
            cout << endl;
            cout << "You reached the treasure room." << endl;
            cout << "Victory!" << endl;
            gameOver = true;
            break;
        }

        cout << endl;
        cout << "What do you want to do?" << endl;
        cout << "1. Move forward" << endl;
        cout << "2. Move backward" << endl;
        cout << "3. Show inventory" << endl;
        cout << "4. Show stats" << endl;
        cout << "5. Quit" << endl;
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1)
        {
            dungeon.moveNext();
        }
        else if (choice == 2)
        {
            dungeon.movePrev();
        }
        else if (choice == 3)
        {
            player.showInventory();
        }
        else if (choice == 4)
        {
            cout << player << endl;
        }
        else if (choice == 5)
        {
            cout << "You leave the dungeon." << endl;
            gameOver = true;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    cout << endl;

    if (!player.isAlive())
    {
        cout << "Defeat. Your health reached 0." << endl;
    }

    cout << "Game over." << endl;

    return 0;
}