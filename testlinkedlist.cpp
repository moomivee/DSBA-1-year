#include "linkedlist.h"
#include <list>
#include <iostream>

int main() {

    LinkedList<int> test;

    test.appendValue(3);
    test.appendValue(4);
    test.insertValue(5, test.getPreHead()->getNext());
    std::cout << test << '\n';
    LinkedList<int>::Node::Swap(test.getPreHead()->getNext(), test.getPreHead()->getPrev()->getPrev());
    std::cout << test;
    return 0;
}