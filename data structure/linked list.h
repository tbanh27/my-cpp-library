#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct ListNode
{
    T data;
    ListNode<T> *pNext = nullptr;
};

template <typename T>
struct Linked_List
{
    ListNode<T> *pHead = nullptr, *pTail = nullptr;
    int nNode = 0;

    void showLinkedList();
    bool isEmptyList();

    ListNode<T> *findByIndex(int index);
    ListNode<T> *findByData(T data, int &index);

    ListNode<T> *addHead(T data);
    ListNode<T> *addTail(T data);
    ListNode<T> *addAtIndex(T data, int index);
    ListNode<T> *addKeepOrder(T data);

    bool deleteListNodeAtIndex(int index);
    bool deleteListHeadNode();
    bool deleteListTailNode();
    bool deleteListNodeByData(T data);
    bool deleteLinkedList();
};

template <typename T>
void Linked_List<T>::showLinkedList()
{
    ListNode<T> *p = pHead;
    while (p != nullptr)
    {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << "\n";
}

template <typename T>
ListNode<T> *newListNode(T data, ListNode<T> *pNext)
{
    ListNode<T> *p = new ListNode<T>;
    if (p != nullptr)
    {
        p->data = data;
        p->pNext = pNext;
    }
    return p;
}

template <typename T>
bool Linked_List<T>::isEmptyList()
{
    return nNode == 0;
}

template <typename T>
ListNode<T> *Linked_List<T>::addHead(T data)
{
    ListNode<T> *new_node = newListNode<T>(data, pHead);
    if (new_node != nullptr)
    {
        if (isEmptyList())
            pHead = pTail = new_node;
        else
            pHead = new_node;
        nNode++;
    }
    return new_node;
}

template <typename T>
ListNode<T> *Linked_List<T>::addTail(T data)
{
    if (isEmptyList())
        return addHead(data);
    ListNode<T> *new_node = newListNode<T>(data, nullptr);
    if (new_node != nullptr)
    {
        pTail->pNext = new_node;
        pTail = new_node;
        nNode++;
    }
    return new_node;
}

template <typename T>
ListNode<T> *Linked_List<T>::findByIndex(int index)
{
    if (index < 0 || index >= nNode)
        return nullptr;
    ListNode<T> *p = pHead;
    while (index--)
        p = p->pNext;
    return p;
}

template <typename T>
ListNode<T> *Linked_List<T>::findByData(T data, int &index)
{
    if (isEmptyList())
        return nullptr;
    ListNode<T> *p = pHead;
    index = 0;
    while (p != nullptr)
    {
        if (p->data == data)
            break;
        p = p->pNext;
        index++;
    }
    return p;
}

template <typename T>
ListNode<T> *Linked_List<T>::addAtIndex(T data, int index)
{
    if (index == 0)
        return addHead(data);
    if (index == nNode)
        return addTail(data);
    if (index < 0 || index > nNode)
        return nullptr;

    ListNode<T> *prev_Index = findByIndex(index - 1); // sure 0 <= prevIndex <= nNode-2
    ListNode<T> *at_Index = findByIndex(index);       // sure 1 <= index <= nNode-1
    ListNode<T> *new_node = newListNode<T>(data, at_Index);
    prev_Index->pNext = new_node;
    nNode++;
    return new_node;
}

template <typename T>
ListNode<T> *Linked_List<T>::addKeepOrder(T data)
{
    if (isEmptyList())
        return addHead(data);

    bool isIncreasing = true;
    for (ListNode<T> *p = pHead; p != nullptr; p = p->pNext)
    {
        if (p->pNext != nullptr && p->data > p->pNext->data)
        {
            isIncreasing = false;
            break;
        }
    }

    ListNode<T> *p = pHead;
    int index = 0;

    if (isIncreasing)
    {
        while (p != nullptr && p->data < data)
        {
            p = p->pNext;
            index++;
        }
        return addAtIndex(data, index);
    }
    else
    {
        while (p != nullptr && p->data > data)
        {
            p = p->pNext;
            index++;
        }
        return addAtIndex(data, index + 1);
    }

    return nullptr;
}

template <typename T>
bool freeMemoryListNode(ListNode<T> *p)
{
    if (p != nullptr)
    {
        delete p;
        p = nullptr;
        return true;
    }
    return false;
}

template <typename T>
bool Linked_List<T>::deleteListNodeAtIndex(int index)
{
    ListNode<T> *p = findByIndex(index);
    if (p != nullptr)
    {
        ListNode<T> *prev = findByIndex(index - 1);
        ListNode<T> *next = p->pNext;
        if (prev != nullptr)
            prev->pNext = next;
        freeMemoryListNode<T>(p);
        if (index == 0)
            pHead = next;
        if (index == nNode - 1)
            pTail = prev;
        nNode--;
        return true;
    }
    return false;
}

template <typename T>
bool Linked_List<T>::deleteListHeadNode()
{
    return deleteListNodeAtIndex(0);
}

template <typename T>
bool Linked_List<T>::deleteListTailNode()
{
    return deleteListNodeAtIndex(nNode - 1);
}

template <typename T>
bool Linked_List<T>::deleteListNodeByData(T data)
{
    int index;
    ListNode<T> *p = findByData(data, index);
    if (p != nullptr)
        return deleteListNodeAtIndex(index);
    return false;
}

template <typename T>
bool Linked_List<T>::deleteLinkedList()
{
    if (isEmptyList())
        return false;
    ListNode<T> *p = pHead, *q = nullptr;
    while (p != nullptr)
    {
        q = p->pNext;
        delete[] p;
        p = q;
    }
    pHead = pTail = nullptr;
    nNode = 0;
    return true;
}