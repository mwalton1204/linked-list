/*********************
Name: Michael Walton
COSC-2436-004
Purpose:
 - Design Linked List ADT
**********************/

#include "linkedlist.h"

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::~LinkedList() {
    clearList();
}

bool LinkedList::addNode(int newId, string* newData) {
    bool added = false;
    if (newId > 0 && !newData->empty()) {
        if(!head) {
            newList(newId, newData, added);
        } else if (newId < head->data.id && !head->prev) {
            addHead(newId, newData, added);
        } else {
            Node* current = head;
            while (newId > current->data.id && current->next) {
                current = current->next;
            }
            if (current->data.id > newId && (!current->prev || current->prev->data.id < newId)) {
                addMiddle(newId, newData, current, added);
            } else if (!current->next && newId != current->data.id) {
                addTail(newId, newData, current, added);
            }
        }
    }
    return added;
}

bool LinkedList::deleteNode(int id) {
    bool deleted = false;
    Node* current = head;
    while (current && id != current->data.id && current->next) {
        current = current->next;
    }
    if(current && id == current->data.id) {
        if (current->next && current->prev) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        } else if (!current->prev && current->next) {
            current->next->prev = NULL;
            head = current->next;
        } else if (!current->next && current->prev) {
            current->prev->next = NULL;
        } else if (!current->next && !current->prev) {
            head = NULL;
        }
        delete current;
        deleted = true;
    }
    return deleted;
}

bool LinkedList::getNode(int id, Data* data) {
    bool retrieved = false;
    Node* current = head;

    data->id = -1;
    data->data = "";

    while(current) {
        if (id == current->data.id) {
            data->id = current->data.id;
            data->data = current->data.data;
            retrieved = true;
        }
        current = current->next;
    }
    return retrieved;
}

void LinkedList::printList(bool backward) {
    Node* current = head;
    int counter = 1;
    if(!head){
        cout << "\tList is empty\n";
    } else {
        if (!backward) {
            while (current) {
                cout << "\t" << counter << ": " << current->data.id << " : " << current->data.data << "\n";
                current = current->next;
                counter++;
            }
        } else {
            current = getTail();
            while (current) {
                cout << "\t" << counter << ": " << current->data.id << " : " << current->data.data << "\n";
                current = current->prev;
                counter++;
            }
        }
    }
    return;
}

int LinkedList::getCount() {
    int count = 0;
    Node* current = head;
    while(current) {
        count++;
        current = current->next;
    }
    return count;
}

bool LinkedList::clearList() {
    Node* current = head;
    while(current) {
        Node* tempNode = current->next;
        delete current;
        current = tempNode;
    }
    head = NULL;
    return true;
}

bool LinkedList::exists(int id) {
    bool exists = false;
    Node* current = head;
    while (current && !exists) {
        if (id == current->data.id) {
            exists = true;
        }
        current = current->next;
    }
    return exists;
}

Node* LinkedList::createNode(int newId, string* newData) {
    Node *newNode = new Node{{newId, *newData}, NULL, NULL};
    return newNode;
}

void LinkedList::newList(int newId, string* newData, bool& added) {
    Node* newNode = createNode(newId, newData);
    head = newNode;
    added = true;
}

void LinkedList::addHead(int newId, string* newData, bool& added) {
    Node* newNode = createNode(newId, newData);
    head->prev = newNode;
    newNode->next = head;
    newNode->prev = NULL;
    head = newNode;
    added = true;
}

void LinkedList::addMiddle(int newId, string* newData, Node* current, bool& added) {
    Node* newNode = createNode(newId, newData);
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    added = true;
}

void LinkedList::addTail(int newId, string* newData, Node* current, bool& added) {
    Node* newNode = createNode(newId, newData);
    newNode->next = NULL;
    newNode->prev = current;
    current->next = newNode;
    added = true;
}

Node* LinkedList::getTail() {
    Node* current = head;
    bool tail = false;
    while (current && !tail) {
        if (current->next) {
            current = current->next;
        } else {
            tail = true;
        }
    }
    return current;
}