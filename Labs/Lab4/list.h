#pragma once
#include "node.h"
#include <iostream>

using namespace std;

template <class T1>
class List
{
    private:
        Node<T1> *_head;
        Node<T1> *_tail;
        size_t listSize;

    public:
        List();
        ~List();

        bool empty();
        size_t size();

        void push_front(T1);
        T1 pop_front();
        T1 front();
        void push_back(T1);
        T1 pop_back();
        T1 back();

        bool operator==(const List<T1>&);
        // Have to declare a template for friend functions using a different template variable
        template <class T2>
        friend ostream &operator<<(ostream &, const List<T2> &);
};

// set to nullptr and initialize listSize
template <class T1>
List<T1>::List()
{
    _head = nullptr;
    _tail = nullptr;
    listSize = 0;
}

// iteratively delete the list starting at _head
template <class T1>
List<T1>::~List()
{
    while (!empty())
    {
        pop_front();
    }
}

// return true if the list is empty, false otherwise.
// Do not just check listSize, should actually check _head and _tail
template <class T1>
bool List<T1>::empty()
{
    return _head == nullptr && _tail == nullptr;
}

// return number of elements in list
template <class T1>
size_t List<T1>::size()
{
    return listSize;
}

// add an element to the beginning of the list, updating _head
template <class T1>
void List<T1>::push_front(T1 data)
{
    Node<T1>* temp = new Node<T1>();
    temp->setData(data);
    if (empty())
    {
        _head = temp;
        _tail = temp;
    }
    else 
    {
        temp->setNext(_head);
        _head->setPrev(temp);
        _head = temp;
    }
    listSize++;
    
}

// return the first element in the list.
// if the list is empty, print that out and return 0
template <class T1>
T1 List<T1>::front()
{
    if (empty())
    {
        cout << "List is empty. " << endl;
        return T1();
    }
    return _head->getData();
}

// remove the first element from the list and return its data
// if the list is empty, print that out and return 0;
template <class T1>
T1 List<T1>::pop_front()
{
    if (empty())
    {
        cout << "Empty list." << endl;
        return T1();
    }
    T1 value = _head->getData();

    if (_head == _tail)
    {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else
    {
        Node<T1>* temp = _head;
        _head = _head->getNext();
        _head->setPrev(nullptr);
        delete temp;
    }
    listSize--;
    return value;
}

// add an element to the end of hte list, updating _tail
template <class T1>
void List<T1>::push_back(T1 data)
{
    Node<T1>* temp = new Node<T1>();
    temp->setData(data);
    if (empty())
    {
        _head = temp;
        _tail = temp;
    }
    else
    {
        temp->setPrev(_tail);
        _tail->setNext(temp);
        _tail = temp;
    }
    listSize++;
}


// return the last element in the list.
// if the list is empty, print that out and return 0
template <class T1>
T1 List<T1>::back()
{
    if (empty())
    {
        cout<< "List is empty\n";
        return T1();
    }
    return _tail->getData(); 
}

// remove the last element from the list and return its data
// if the list is empty, print that out and return 0;
template <class T1>
T1 List<T1>::pop_back()
{
    if (empty())
    {
        cout << "Empty list.\n" << endl;
        return T1();
    }
    T1 value = _tail->getData();
    if (_head == _tail)
    {
        delete _tail;
        _head = nullptr;
        _tail = nullptr;
    }
    else
    {
        Node<T1>* temp = _tail;
        _tail = _tail->getPrev();
        _tail->setNext(nullptr);
        delete temp;
    }
    listSize--;
    return value;
}

// overloading <<, should return a space separated stream of all of the elements
template <class T1>
ostream &operator<<(ostream &os, const List<T1> &list)
{
    Node<T1>* currentNode = list._head;
    while (currentNode != nullptr)
    {
        os << currentNode->getData();
        if (currentNode->getNext() != nullptr)
        {
            os << " ";
        }
        currentNode = currentNode->getNext();
    }
    return os;
}

// should iterate through each list to check that they are exactly the same
template <class T1>
bool List<T1>::operator==(const List<T1>& rhs)
{
    if (listSize != rhs.listSize)
    {
        return false;
    }

    Node<T1>* left = _head;
    Node<T1>* right = rhs._head;

    while ( left != nullptr && right != nullptr)
    {   //Why am I getting this error???? I can't even figure it with Google.
        if (left->getData() != right->getData())
        {
            return false;
        }
    left = left->getNext();
    right = right->getNext();
    }

    return true;
}