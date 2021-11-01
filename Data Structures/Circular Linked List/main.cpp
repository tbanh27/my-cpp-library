#include "Circular Linked List.h"

int main()
{
    int data[] = {-4, 2, 1, 5, 3};
    int size = sizeof(data) / sizeof(data[0]);

    CircularLinkedList<int> list(size, data);

    list.printList("List khoi tao: ");

    list.addHead(-5);
    list.printList("addHead(5) -> List: ");

    list.addTail(6);
    list.printList("addTail(6) -> List: ");

    list.removeHead();
    list.printList("removeHead -> List: ");

    list.removeTail();
    list.printList("removeTail -> List: ");

    list.addAfter(3, 7);
    list.printList("addAfter(index = 3, data = 7) -> List: ");

    list.removeAfter(3);
    list.printList("removeAfter(index = 3) -> List: ");

    return 0;
}