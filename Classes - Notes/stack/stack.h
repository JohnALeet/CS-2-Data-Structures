#pragma once
#include "node.h"
#include <iostream>
template <class T1>//Linked lists let you access the data easier.
class Stack
{

private:
    Node <T1> * _top;
    unsigned int _size;

    public:
    Stack<T1>() { empty(); _size =0;}

    void push(T1 data)
    {
        Node<T1>* newNode = new Node<T1>;
        newNode->setData(data);
        // if(_top == nullptr)
        // {
        //     _top = newNode;
        // }
        // else
        // {
        //     _top->setNext(newNode);
        //     _top = newNode;
        // }
        if (_top != nullptr)
        {
            newNode->setPrev(_top);
        }
        _top = newNode;
        _size++;
    }
    T1 pop()
    {
        if(empty())
        {
            std::cerr << "List is empty!"
            return T1();
        }
        Node<T1>* tmpNode = _top;
        T1 toBeReturned = tmpNode->getData();
        _top = top _top->getPreb();
        _size--;
        delete tmpNode;
        return toBeReturned;

    }

    bool empty()
    {
        return _top==nullptr;
    }

};