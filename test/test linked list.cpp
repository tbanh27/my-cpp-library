#include <iostream>
#include "../data structure/linked list.h"

using namespace std;

int chooseAction()
{
    cout << "\nWhat do you want?\n";
    cout << "(1) Search by index\t\t(2) Search by data\n";
    cout << "(3) Add head\t(4) Add tail\t(5) Add at index\t(6) Add keep order\n";
    cout << "(7) Delete head\t(8) Delete tail\t(9) Delete at index\t(10) Delete by data\n";
    cout << "Your choice: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > 10)
    {
        cout << "Invalid choice!\n";
        return chooseAction();
    }
    return choice;
}

int main()
{
    Linked_List<int> list;

    cout << "Nhap list:";
    int data;
    while (true)
    {
        cout << "\ndata: ";
        cin >> data;
        list.addTail(data);
        cout << "current list: ";
        list.showLinkedList();
        cout << "Continue? (y/n): ";
        char x;
        cin >> x;
        if (tolower(x) != 'y')
            break;
    }

    while (true)
    {
        int choice = chooseAction();
        switch (choice)
        {
        case 1:
        {
            int index;
            cout << "\nindex: ";
            cin >> index;
            ListNode<int> *z = list.findByIndex(index);
            if (z)
            {
                cout << "node[" << index << "] = " << z->data << endl;
            }
            else
                cout << "Invalid index!\n";
        }
        break;
        case 2:
        {
            int data, index;
            cout << "\ndata to search: ";
            cin >> data;
            ListNode<int> *z = list.findByData(data, index);
            if (z)
            {
                cout << "node[" << index << "] = " << data << endl;
            }
            else
                cout << "Not Found!\n";
        }
        break;
        case 3:
        {
            int data;
            cout << "\ndata: ";
            cin >> data;
            list.addHead(data);
            cout << "list after add head: ";
            list.showLinkedList();
        }
        break;
        case 4:
        {
            int data;
            cout << "\ndata: ";
            cin >> data;
            list.addTail(data);
            cout << "list after add tail: ";
            list.showLinkedList();
        }
        break;
        case 5:
        {
            int data, index;
            cout << "\ndata: ";
            cin >> data;
            cout << "index: ";
            cin >> index;
            list.addAtIndex(data, index);
            cout << "list after add: ";
            list.showLinkedList();
        }
        break;
        case 6:
        {
            cout << "Sure that list is ordered!\n";
            int data;
            cout << "\ndata: ";
            cin >> data;
            list.addKeepOrder(data);
            cout << "list after add keep order: ";
            list.showLinkedList();
        }
        break;
        case 7:
        {
            list.deleteListHeadNode();
            cout << "list after delete head: ";
            list.showLinkedList();
        }
        break;
        case 8:
        {
            list.deleteListTailNode();
            cout << "list after delete tail: ";
            list.showLinkedList();
        }
        break;
        case 9:
        {
            int index;
            cout << "\nindex: ";
            cin >> index;
            if (list.deleteListNodeAtIndex(index) == false)
                cout << "invalid index!\n";
            cout << "list after delete: ";
            list.showLinkedList();
        }
        break;
        case 10:
        {
            int data;
            cout << "\ndata: ";
            cin >> data;
            list.deleteListNodeByData(data);
            cout << "list after delete: ";
            list.showLinkedList();
        }
        break;
        default:
            break;
        }

        char x;
        cout << "Continue? (y/n): ";
        cin >> x;
        if (tolower(x) != 'y')
            break;
    }

    list.deleteLinkedList();
    return 0;
}