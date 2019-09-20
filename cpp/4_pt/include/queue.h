#ifndef QUEUE_H_
#define QUEUE_H_

class Customer {
private:
    long m_arrive;      //客户到达时间
    int  m_processtime; //客户交易时间
public:
    Customer() { m_arrive = m_processtime = 0; }
    void set(long when);
    long when() const { return m_arrive; }
    int  ptime() const { return m_processtime; }
    bool isRight(int a) const;
};

typedef Customer Item;

class Queue {
private:
    struct Node {
        Item         item;
        struct Node *next;
    };
    enum { Q_SIZE = 10 };
    Node *    front;
    Node *    rear;
    int       items;
    const int qsize;
    Queue(const Queue &q) : qsize(0) {}
    Queue &operator=(const Queue &q) { return *this; }

public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int  queuecount() const;
    bool enqueue(const Item &itme);
    bool dequeue(Item &itme);
};

#endif