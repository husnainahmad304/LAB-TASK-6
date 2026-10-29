#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "TrainNode.h"

// Lab 4: Priority Queue for dispatching trains
class PriorityQueue
{
private:
    TrainNode* front;
    TrainNode* rear;
    int count;

    void CopyFrom(const PriorityQueue& other);
    void Clear();

public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(const PriorityQueue& other);
    ~PriorityQueue();

    void Add(TrainNode* train);
    TrainNode* Remove();   // removes highest-priority train
    bool IsEmpty();
    bool IsNotEmpty();
    void PrintQueue();
};

#endif
