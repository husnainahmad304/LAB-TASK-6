#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "TrainNode.h"

// Lab 6: Circular Linked List = Station Departure Board that rotates
// through the trains again and again.
//   head        -> points to the LAST node (pivot)
//   head->next  -> points to the FIRST node
//   display     -> the train currently shown on the board
class CircularLinkedList
{
private:
    TrainNode* head;
    TrainNode* display;
    int count;

    TrainNode* GetNodeAt(int index);
    void SwapData(TrainNode* a, TrainNode* b);
    int NormalizeIndex(int index);

public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other);
    CircularLinkedList& operator=(const CircularLinkedList& other);
    ~CircularLinkedList();

    bool IsEmpty();
    bool IsNotEmpty();

    void Insert(TrainNode* train);      // insert at node next to head (front)
    TrainNode* Remove();                // remove node next to head (front)
    void InsertAt(TrainNode* train, int index);
    TrainNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();                        // by train ID, ascending
    void Reverse();
    void Print();

    // Move the board to the next train. After the last train it goes back
    // to the first one. *wrapped is set to true when it wrapped around.
    TrainNode* MoveToNext(bool* wrapped = nullptr);

    bool IsCircular();                  // does the last node link back to the first?
    void PrintCircularInfo();
    int GetCount();
};

#endif
