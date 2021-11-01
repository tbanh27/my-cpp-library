#pragma once


template <class T>
class Node
{
private:
    T data;
    Node<T> *pNext;

public:
    Node();
    Node(T srcData, Node *srcpNext);
    Node(const Node &src);
    ~Node();

    T getData();
    Node *getNextNode();
    bool setData(T src);
    bool setNextNode(Node *src);

    Node &operator=(const Node &src);
};

template <class T>
Node<T>::Node()
{
    this->data = 0;
    this->pNext = nullptr;
}

template <class T>
Node<T>::Node(T srcData, Node *srcpNext)
{
    this->data = srcData;
    this->pNext = srcpNext;
}

template <class T>
Node<T>::Node(const Node &src)
{
    this->data = src.data;
    this->pNext = src.pNext;
}

template <class T>
Node<T>::~Node()
{
    // Do nothing
}

template <class T>
T Node<T>::getData()
{
    return this->data;
}

template <class T>
Node<T>* Node<T>::getNextNode()
{
    return this->pNext;
}

template <class T>
bool Node<T>::setData(T src)
{
    this->data = src;
}

template <class T>
bool Node<T>::setNextNode(Node *src)
{
    this->pNext = src;
}

template <class T>
Node<T> &Node<T>::operator=(const Node &src)
{
    this->data = src.data;
    this->pNext = src.pNext;
    return *this;
}