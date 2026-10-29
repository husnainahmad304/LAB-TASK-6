#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "BookRequestNode.h"

// Lab 4: Priority Queue for urgent book requests
class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

    void CopyFrom(const PriorityQueue& other);
    void Clear();

public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);
    ~PriorityQueue();

    void Add(BookRequestNode* request);
    BookRequestNode* Remove();
    bool IsEmpty();
    bool IsNotEmpty();
    void PrintQueue();
};

#endif
