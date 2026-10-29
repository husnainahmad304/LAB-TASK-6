#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "TrainNode.h"

// Lab 5: general-purpose singly linked list = Train Timetable
class LinkedList
{
private:
    TrainNode* head;
    int count;

    TrainNode* GetNodeAt(int index);
    void CopyTrainData(TrainNode* a, TrainNode* b);

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();

    void Insert(TrainNode* train);          // insert at head
    TrainNode* Remove();                    // remove from head
    bool IsEmpty();
    bool IsNotEmpty();
    void InsertAt(TrainNode* train, int index);
    TrainNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();                            // by train ID, ascending
    void Reverse();
    void Print();
    int GetCount();
};

#endif
