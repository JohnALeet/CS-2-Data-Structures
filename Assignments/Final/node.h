#pragma once

template <class T1>
class Node
{
private:
    T1 data;
    Node<T1>* next;
    Node<T1>* prev;

public:
    Node()
    {
        next = nullptr;
        prev = nullptr;
    }

    T1 getData()
    {
        return data;
    }

    Node<T1>* getNext()
    {
        return next;
    }

    Node<T1>* getPrev()
    {
        return prev;
    }

    void setData(T1 d)
    {
        data = d;
    }

    void setNext(Node<T1>* n)
    {
        next = n;
    }

    void setPrev(Node<T1>* p)
    {
        prev = p;
    }
};