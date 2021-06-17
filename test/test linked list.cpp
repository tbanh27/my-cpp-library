#include <iostream>
#include "../linked list.h"

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
        addTail<int>(data, list);
        cout << "current list: ";
        showLinkedList<int>(list);
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
            ListNode<int> *z = findByIndex<int>(index, list);
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
            ListNode<int> *z = findByData<int>(data, list, index);
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
            addHead<int>(data, list);
            cout << "list after add head: ";
            showLinkedList<int>(list);
        }
        break;
        case 4:
        {
            int data;
            cout << "\ndata: ";
            cin >> data;
            addTail<int>(data, list);
            cout << "list after add tail: ";
            showLinkedList<int>(list);
        }
        break;
        case 5:
        {
            int data, index;
            cout << "\ndata: ";
            cin >> data;
            cout << "index: ";
            cin >> index;
            addAtIndex<int>(data, list, index);
            cout << "list after add: ";
            showLinkedList<int>(list);
        }
        break;
        case 6:
        {
            cout << "Sure that list is ordered!\n";
            int data;
            cout << "\ndata: ";
            cin >> data;
            addKeepOrder<int>(data, list);
            cout << "list after add keep order: ";
            showLinkedList<int>(list);
        }
        break;
        case 7:
        {
            deleteListHeadNode<int>(list);
            cout << "list after delete head: ";
            showLinkedList<int>(list);
        }
        break;
        case 8:
        {
            deleteListTailNode<int>(list);
            cout << "list after delete tail: ";
            showLinkedList<int>(list);
        }
        break;
        case 9:
        {
            int index;
            cout << "\nindex: ";
            cin >> index;
            if (deleteListNodeAtIndex<int>(index, list) == false)
                cout << "invalid index!\n";
            cout << "list after delete: ";
            showLinkedList<int>(list);
        }
        break;
        case 10:
        {
            int data;
            cout << "\ndata: ";
            cin >> data;
            deleteListNodeByData<int>(data, list);
            cout << "list after delete: ";
            showLinkedList<int>(list);
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

    deleteLinkedList<int>(list);
    return 0;
}