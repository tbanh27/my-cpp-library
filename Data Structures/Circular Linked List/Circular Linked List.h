#pragma once
#include <iostream>
using namespace std;

//#include "Node.h"
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
Node<T> *Node<T>::getNextNode()
{
    return this->pNext;
}

template <class T>
bool Node<T>::setData(T src)
{
    this->data = src;
    return true;
}

template <class T>
bool Node<T>::setNextNode(Node *src)
{
    this->pNext = src;
    return true;
}

template <class T>
Node<T> &Node<T>::operator=(const Node &src)
{
    this->data = src.data;
    this->pNext = src.pNext;
    return *this;
}

//=======================================================================================================================

template <class T>
class CircularLinkedList
{
private:
    Node<T> *pTail;

public:
    CircularLinkedList();
    CircularLinkedList(int size, T *data);
    ~CircularLinkedList();

    bool isEmpty();

    void setTailNode(Node<T> *src);
    Node<T> *getNode(int index);
    Node<T> *getHeadNode();
    int getSize();

    bool addHead(T srcData);
    bool addTail(T srcData);
    bool removeHead();
    bool removeTail();
    bool addAfter(int index, T srcData);
    bool removeAfter(int index);

    void printList(const string defaultStartMessage = "", const string defaultEnding = "\n");
};

// Default constructor, create new empty circular linked list
template <class T>
CircularLinkedList<T>::CircularLinkedList()
{
    this->pTail = nullptr;
}

template <class T>
CircularLinkedList<T>::CircularLinkedList(int size, T *data)
{
    for (int i = 0; i < size; ++i)
        this->addTail(data[i]);
}

// Destructor
template <class T>
CircularLinkedList<T>::~CircularLinkedList()
{
    Node<T> *p = this->getHeadNode();

    while (p != nullptr)
    {
        Node<T> *q = p->getNextNode();

        // If p is pTail, set q to nullptr to avoid error
        if (p == this->pTail)
            q = nullptr;

        delete p;
        p = q;
    }

    this->setTailNode(nullptr);
}

// This method return true if this circular linked list is empty
template <class T>
bool CircularLinkedList<T>::isEmpty()
{
    return this->pTail == nullptr;
}

// This method is used to set tail node for this circular linked list
template <class T>
void CircularLinkedList<T>::setTailNode(Node<T> *src)
{
    this->pTail = src;
}

// This method returns the pointer to the node with given index
// If that node doesn't exist, this method return false
template <class T>
Node<T> *CircularLinkedList<T>::getNode(int index)
{
    int size = this->getSize();

    if (index < 0 || index >= size)
        return nullptr;

    if (index == size - 1)
        return this->pTail;

    Node<T> *p = this->getHeadNode();
    int i = 0;

    while (i != index)
    {
        i++;
        p = p->getNextNode();
    }

    return p;
}

// This method return pointer to head node of this circular linked  list
// If this list is empty, it returns nullptr
template <class T>
Node<T> *CircularLinkedList<T>::getHeadNode()
{
    if (this->isEmpty())
        return nullptr;

    return this->pTail->getNextNode();
}

// This method return current size of this linked list
template <class T>
int CircularLinkedList<T>::getSize()
{
    int size = 0;
    Node<T> *head = this->getHeadNode();
    Node<T> *p = head;

    while (p != nullptr)
    {
        p = p->getNextNode();
        size++;

        if (p == head)
            break;
    }

    return size;
}

// This method add a new node to this linked list as head node
template <class T>
bool CircularLinkedList<T>::addHead(T srcData)
{
    if (this->isEmpty())
    {
        Node<T> *newHead = new Node<T>(srcData, nullptr);

        if (newHead == nullptr)
            return false;

        newHead->setNextNode(newHead);
        this->setTailNode(newHead);
        return true;
    }

    Node<T> *oldHead = this->getHeadNode();
    Node<T> *newHead = new Node<T>(srcData, oldHead);

    if (newHead == nullptr)
        return false;

    this->pTail->setNextNode(newHead);
    return true;
}

// This method add a new node to this linked list as a tail node
template <class T>
bool CircularLinkedList<T>::addTail(T srcData)
{
    if (this->isEmpty())
    {
        Node<T> *newTail = new Node<T>(srcData, nullptr);

        if (newTail == nullptr)
            return false;

        newTail->setNextNode(newTail);
        this->setTailNode(newTail);
        return true;
    }

    Node<T> *oldTail = this->pTail;
    Node<T> *head = this->getHeadNode();
    Node<T> *newTail = new Node<T>(srcData, head);

    if (newTail == nullptr)
        return false;

    oldTail->setNextNode(newTail);
    this->setTailNode(newTail);
    return true;
}

// This method remove head node of this linked list
// If this linked list is empty, this method returns false
template <class T>
bool CircularLinkedList<T>::removeHead()
{
    if (this->isEmpty())
        return false;

    Node<T> *oldHead = this->getHeadNode();
    Node<T> *newHead = oldHead->getNextNode();

    // If oldHead == newHead, means this linked list has only 1 element, just delete that element
    if (oldHead == newHead)
    {
        delete oldHead;
        this->setTailNode(nullptr);
        return true;
    }

    delete oldHead;
    this->pTail->setNextNode(newHead);
    return true;
}

// This method remove the tail node of this linked list
// If this linked list is empty, this method returns false
template <class T>
bool CircularLinkedList<T>::removeTail()
{
    if (this->isEmpty())
        return false;

    Node<T> *oldTail = this->pTail;
    Node<T> *head = this->getHeadNode();

    // If oldTail == head, means this linked list has only 1 element, just delete hat element
    if (oldTail == head)
    {
        delete oldTail;
        this->setTailNode(nullptr);
        return true;
    }

    Node<T> *newTail = this->pTail;
    Node<T> *p = head;
    while (p != oldTail)
    {
        newTail = p;
        p = p->getNextNode();
    }

    delete oldTail;
    newTail->setNextNode(head);
    this->setTailNode(newTail);
    return true;
}

// This method add a new node to linked list after the node at given index
// If the node at given index doesn't exist, this method returns false
template <class T>
bool CircularLinkedList<T>::addAfter(int index, T srcData)
{
    Node<T> *nodeIndex = this->getNode(index);

    // If node at index is not exist, return false
    if (nodeIndex == nullptr)
        return false;
    
    // If node at index is tail node, add tail
    if (nodeIndex == this->pTail)
        return this->addTail(srcData);

    // If node at index is not tail node, add new node after it
    Node<T> *nodeAfter = nodeIndex->getNextNode();
    Node<T> *newNode = new Node<T>(srcData, nodeAfter);

    if (newNode == nullptr)
        return false;

    nodeIndex->setNextNode(newNode);
    return true;
}

// This methods remove the node at index + 1, with given index.
template <class T>
bool CircularLinkedList<T>::removeAfter(int index)
{
    Node<T> *nodeIndex = this->getNode(index);

    // If node at index does not exist or it is tail node, return false because there isn't any node after it
    if (nodeIndex == nullptr || nodeIndex == this->pTail)
        return false;

    // If node at index exists and it's not tail node, remove the node after it
    Node<T> *nodeToRemove = nodeIndex->getNextNode();

    // If node to remove is tail node, remove tail
    if (nodeToRemove == this->pTail)
        return this->removeTail();

    // If node to remove is not tail node
    Node<T> *nodeAfter = nodeToRemove->getNextNode();
    delete nodeToRemove;
    nodeIndex->setNextNode(nodeAfter);
    return true;
}

// This method print this linked list to std::cout
// Parameters:
// --- defaultStartMessage: a string, representing a message before print the list, for default is an empty string.
// --- defaultEnding: a string, representing a message after print the list, for default is a newline character.
template <class T>
void CircularLinkedList<T>::printList(const string defaultStartMessage, const string defaultEnding)
{
    cout << defaultStartMessage;

    Node<T> *head = this->getHeadNode();
    for (Node<T> *p = head; p != nullptr; p = p->getNextNode())
    {
        cout << p->getData() << "  ";
        if (p->getNextNode() == head)
            break;
    }

    cout << defaultEnding;
}