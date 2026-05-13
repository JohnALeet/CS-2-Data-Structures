#pragma once
#include "node.h"
#include "room.h"
#include <iostream>

using namespace std;

namespace dungeon
{

class Dungeon
{
private:
    Node<Room*>* _head;
    Node<Room*>* _tail;
    Node<Room*>* currentRoom;
    size_t dungeonSize;

public:
    Dungeon();
    ~Dungeon();

    bool empty();
    size_t size();

    void push_front(Room* room);
    Room* pop_front();
    Room* front();

    void push_back(Room* room);
    Room* pop_back();
    Room* back();

    Room* getCurrentRoom();
    void resetCurrentRoom();

    bool moveNext();
    bool movePrev();
    

    void displayCurrentRoom();

    bool atFinalRoom();

    void removeEnemyFromCurrentRoom();
    void removeItemFromCurrentRoom();

    void addRoom(Room* room);

    bool operator==(const Dungeon& rhs);

    friend ostream& operator<<(ostream& os, const Dungeon& dungeon);
};


Dungeon::Dungeon()
{
    _head = nullptr;
    _tail = nullptr;
    currentRoom = nullptr;
    dungeonSize = 0;
}

// iteratively delete the dungeon starting at _head
Dungeon::~Dungeon()
{
    while (!empty())
    {
        Room* roomToDelete = pop_front();

        if (roomToDelete != nullptr)
        {
            delete roomToDelete;
            roomToDelete = nullptr;
        }
    }
}

// return true if the dungeon is empty, false otherwise
bool Dungeon::empty()
{
    return _head == nullptr && _tail == nullptr;
}

// return number of rooms in dungeon
size_t Dungeon::size()
{
    return dungeonSize;
}

// add a room to the beginning of the dungeon
void Dungeon::push_front(Room* room)
{
    Node<Room*>* temp = new Node<Room*>();
    temp->setData(room);

    if (empty())
    {
        _head = temp;
        _tail = temp;
        currentRoom = temp;
    }
    else
    {
        temp->setNext(_head);
        _head->setPrev(temp);
        _head = temp;
        currentRoom = _head;
    }

    dungeonSize++;
}

// return the first room in the dungeon
Room* Dungeon::front()
{
    if (empty())
    {
        cout << "Dungeon is empty." << endl;
        return nullptr;
    }

    return _head->getData();
}

// remove the first room from the dungeon and return it
Room* Dungeon::pop_front()
{
    if (empty())
    {
        cout << "Empty dungeon." << endl;
        return nullptr;
    }

    Room* value = _head->getData();

    if (_head == _tail)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
        currentRoom = nullptr;
    }
    else
    {
        Node<Room*>* temp = _head;
        _head = _head->getNext();
        _head->setPrev(nullptr);

        if (currentRoom == temp)
        {
            currentRoom = _head;
        }

        delete temp;
    }

    dungeonSize--;
    return value;
}


// add a room to the end of the dungeon
void Dungeon::push_back(Room* room)
{
    Node<Room*>* temp = new Node<Room*>();
    temp->setData(room);

    if (empty())
    {
        _head = temp;
        _tail = temp;
        currentRoom = temp;
    }
    else
    {
        temp->setPrev(_tail);
        _tail->setNext(temp);
        _tail = temp;
    }

    dungeonSize++;
}

// return the last room in the dungeon
Room* Dungeon::back()
{
    if (empty())
    {
        cout << "Dungeon is empty." << endl;
        return nullptr;
    }

    return _tail->getData();
}

// remove the last room from the dungeon and return it
Room* Dungeon::pop_back()
{
    if (empty())
    {
        cout << "Empty dungeon." << endl;
        return nullptr;
    }

    Room* value = _tail->getData();

    if (_head == _tail)
    {
        delete _tail;
        _head = nullptr;
        _tail = nullptr;
        currentRoom = nullptr;
    }
    else
    {
        Node<Room*>* temp = _tail;
        _tail = _tail->getPrev();
        _tail->setNext(nullptr);

        if (currentRoom == temp)
        {
            currentRoom = _tail;
        }

        delete temp;
    }

    dungeonSize--;
    return value;
}

// return the current room the player is in
Room* Dungeon::getCurrentRoom()
{
    if (currentRoom == nullptr)
    {
        return nullptr;
    }

    return currentRoom->getData();
}

// reset the player to the first room
void Dungeon::resetCurrentRoom()
{
    currentRoom = _head;
}

// move to the next room
bool Dungeon::moveNext()
{
    if (currentRoom == nullptr)
    {
        cout << "There is no current room." << endl;
        return false;
    }

    if (currentRoom->getNext() == nullptr)
    {
        cout << "There are no more rooms ahead." << endl;
        return false;
    }

    currentRoom = currentRoom->getNext();
    return true;
}


bool Dungeon::movePrev()
{
    if (currentRoom == nullptr)
    {
        cout << "There is no current room." << endl;
        return false;
    }

    if (currentRoom->getPrev() == nullptr)
    {
        cout << "There are no rooms behind you." << endl;
        return false;
    }

    currentRoom = currentRoom->getPrev();
    return true;
}

void Dungeon::addRoom(Room* room)
{
    push_back(room);
}

void Dungeon::removeEnemyFromCurrentRoom()
{
    if (currentRoom == nullptr)
    {
        cout << "There is no current room." << endl;
        return;
    }

    Room* room = currentRoom->getData();

    if (room == nullptr)
    {
        cout << "Current room does not exist." << endl;
        return;
    }

    room->removeEnemy();
}

void Dungeon::removeItemFromCurrentRoom()
{
    if (currentRoom == nullptr)
    {
        cout << "There is no current room." << endl;
        return;
    }

    Room* room = currentRoom->getData();

    if (room == nullptr)
    {
        cout << "Current room does not exist." << endl;
        return;
    }

    room->removeItem();
}

// display the current room
void Dungeon::displayCurrentRoom()
{
    if (currentRoom == nullptr)
    {
        cout << "There is no current room." << endl;
        return;
    }

    cout << *(currentRoom->getData()) << endl;
}

// check if the current room is the final room
bool Dungeon::atFinalRoom()
{
    return currentRoom != nullptr && currentRoom == _tail;
}

// compare two dungeons by size
bool Dungeon::operator==(const Dungeon& rhs)
{
    if (dungeonSize != rhs.dungeonSize)
    {
        return false;
    }

    Node<Room*>* left = _head;
    Node<Room*>* right = rhs._head;

    while (left != nullptr && right != nullptr)
    {
        if (*(left->getData()) != *(right->getData()))
        {
            return false;
        }

        left = left->getNext();
        right = right->getNext();
    }

    return true;
}

// print every room in the dungeon
ostream& operator<<(ostream& os, const Dungeon& dungeon)
{
    Node<Room*>* currentNode = dungeon._head;
    int roomNumber = 1;

    while (currentNode != nullptr)
    {
        os << "Room " << roomNumber << ":" << endl;
        os << *(currentNode->getData()) << endl;

        if (currentNode->getNext() != nullptr)
        {
            os << endl;
        }

        currentNode = currentNode->getNext();
        roomNumber++;
    }

    return os;
}

}