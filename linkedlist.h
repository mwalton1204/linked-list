/*********************
Name: Michael Walton
COSC-2436-004
Purpose:
 - Design Linked List ADT
**********************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "data.h"

using std::cout;

class LinkedList {

public:

    LinkedList();
    ~LinkedList();

    bool addNode(int, string*);
    bool deleteNode(int);
    bool getNode(int, Data*);
    void printList(bool = false);
    int getCount();
    bool clearList();
    bool exists(int);

private:

    Node* createNode(int, string*);
    void newList(int, string*, bool&);
    void addHead(int, string*, bool&);
    void addMiddle(int, string*, Node*, bool&);
    void addTail(int, string*, Node*, bool&);
    Node* getTail();

    Node *head;
};

#endif //LINKED_LIST_H