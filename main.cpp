#include <iostream>
#include "DoubleLinkedList.h"

int main() {

    // Not full test

    LinkedLists::DoubleLinkedList<double> list{};
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(5.5);
    list.push_front(3.3);
    list.push_front(4.4);
    list.push_front(5.5);
    list.push_front(5.5);
    list.push_back(6.6);

    LinkedLists::DoubleLinkedList<double> newList = std::move(list);

    newList.push_back(100.);


    list = std::move(newList);

    std::cout << list;

    return 0;
}
