#include "../include/queue.h"
#include <cstdlib>
#include <iostream>
Queue::Queue(int qs) : qsize(qs) {
    front = rear = nullptr;
    items        = 0;
}

Queue::~Queue() {
    Node *temp;
    while (front != NULL) {
        temp  = front;
        front = front->next;
        delete temp;
    }
}

bool Queue::isempty() const {
    return items == 0;
}

bool Queue::isfull() const {
    return items == qsize;
}

int Queue::queuecount() const {
    return items;
}

bool Queue::enqueue(const Item &item) {
    if (isfull())
        return false;
    Node *add = new Node;
    add->item = item;
    add->next = nullptr;
    items++;
    if (front == NULL)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}

bool Queue::dequeue(Item &item) {
    if (front == NULL)
        return false;
    item = front->item;
    items--;
    Node *temp = front;
    front      = front->next;
    delete temp;
    if (items == 0)
        rear = NULL;
    return true;
}

void Customer::set(long when) {
    m_processtime = std::rand() % 3 + 1;
    m_arrive      = when;
}

bool Customer::isRight(int a) const {
    int count = 0;
    while (a > 0) {
        count += a % 2;
        a = a >> 1;
    }

    if (count == 1) {
        return true;
    } else {
        return false;
    }
}