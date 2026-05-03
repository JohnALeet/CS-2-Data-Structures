#pragma once
#include "node.h"
#include <iostream>


template <class T1>
class queue
{
private:
    Node<T1>* _beg, _end;
    unsigned int _size

public:
    queue(){_beg = nullptr; _end = nullptr; _size = 0;}
    

};

bool empty()
{

    return (_beg == nullptr);
}

void enqueue(T1 data)
{
    Node<T1>* newNode = new Node;
    newNode -> setData(data);
    if(empty())
    {
        _beg = newNode;
        _end = newNode;
        return;

    }


};

T1 dequeue()
{
    if(empty())
    {
        std::cerr << "Queue empty" << endl;
        return T1();
    }

    Node<T1>* toBeDeleted = _beg;
    _beg = _beg->getNext();
    T1 toReturn = toBeDeleted->toReturn;
}
