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
};

template <typename T>
void showLinkedList(Linked_List<T> list)
{
    ListNode<T> *p = list.pHead;
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
bool isEmptyList(Linked_List<T> list)
{
    return list.nNode == 0;
}

template <typename T>
ListNode<T> *addHead(T data, Linked_List<T> &list)
{
    ListNode<T> *new_node = newListNode<T>(data, list.pHead);
    if (new_node != nullptr)
    {
        if (isEmptyList<T>(list))
            list.pHead = list.pTail = new_node;
        else
            list.pHead = new_node;
        list.nNode++;
    }
    return new_node;
}

template <typename T>
ListNode<T> *addTail(T data, Linked_List<T> &list)
{
    if (isEmptyList<T>(list))
        return addHead<T>(data, list);
    ListNode<T> *new_node = newListNode<T>(data, nullptr);
    if (new_node != nullptr)
    {
        list.pTail->pNext = new_node;
        list.pTail = new_node;
        list.nNode++;
    }
    return new_node;
}

template <typename T>
ListNode<T> *findByIndex(int index, Linked_List<T> list)
{
    if (index < 0 || index >= list.nNode)
        return nullptr;
    ListNode<T> *p = list.pHead;
    while (index--)
        p = p->pNext;
    return p;
}

template <typename T>
ListNode<T> *findByData(T data, Linked_List<T> list, int &index)
{
    if (isEmptyList<T>(list))
        return nullptr;
    ListNode<T> *p = list.pHead;
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
ListNode<T> *addAtIndex(T data, Linked_List<T> &list, int index)
{
    if (index == 0)
        return addHead<T>(data, list);
    if (index == list.nNode)
        return addTail<T>(data, list);
    if (index < 0 || index > list.nNode)
        return nullptr;

    ListNode<T> *prev_Index = findByIndex<T>(index - 1, list); // sure 0 <= prevIndex <= nNode-2
    ListNode<T> *at_Index = findByIndex<T>(index, list);       // sure 1 <= index <= nNode-1
    ListNode<T> *new_node = newListNode<T>(data, at_Index);
    prev_Index->pNext = new_node;
    list.nNode++;
    return new_node;
}

template <typename T>
ListNode<T> *addKeepOrder(T data, Linked_List<T> &sortedList)
{
    if (isEmptyList<T>(sortedList))
        return addHead<T>(data, sortedList);

    bool isIncreasing = true;
    for (ListNode<T> *p = sortedList.pHead; p != nullptr; p = p->pNext)
    {
        if (p->pNext != nullptr && p->data > p->pNext->data)
        {
            isIncreasing = false;
            break;
        }
    }

    ListNode<T> *p = sortedList.pHead;
    int index = 0;

    if (isIncreasing)
    {
        while (p != nullptr && p->data < data)
        {
            p = p->pNext;
            index++;
        }
        return addAtIndex<T>(data, sortedList, index);
    }
    else
    {
        while (p != nullptr && p->data > data)
        {
            p = p->pNext;
            index++;
        }
        return addAtIndex<T>(data, sortedList, index + 1);
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
bool deleteListNodeAtIndex(int index, Linked_List<T> &list)
{
    ListNode<T> *p = findByIndex<T>(index, list);
    if (p != nullptr)
    {
        ListNode<T> *prev = findByIndex<T>(index - 1, list);
        ListNode<T> *next = p->pNext;
        if (prev != nullptr)
            prev->pNext = next;
        freeMemoryListNode<T>(p);
        if (index == 0)
            list.pHead = next;
        if (index == list.nNode - 1)
            list.pTail = prev;
        list.nNode--;
        return true;
    }
    return false;
}

template <typename T>
bool deleteListHeadNode(Linked_List<T> &list)
{
    return deleteListNodeAtIndex<T>(0, list);
}

template <typename T>
bool deleteListTailNode(Linked_List<T> &list)
{
    return deleteListNodeAtIndex<T>(list.nNode - 1, list);
}

template <typename T>
bool deleteListNodeByData(T data, Linked_List<T> &list)
{
    int index;
    ListNode<T> *p = findByData<T>(data, list, index);
    if (p != nullptr)
        return deleteListNodeAtIndex<T>(index, list);
    return false;
}

template <typename T>
bool deleteLinkedList(Linked_List<T> &list)
{
    if (isEmptyList<T>(list))
        return false;
    ListNode<T> *p = list.pHead, *q = nullptr;
    while (p != nullptr)
    {
        q = p->pNext;
        delete[] p;
        p = q;
    }
    list.pHead = list.pTail = nullptr;
    list.nNode = 0;
    return true;
}