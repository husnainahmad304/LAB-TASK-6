#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "BookNode.h"

// Lab 6: Circular Linked List for the featured-book display screen.
//   head        -> points to the LAST node (pivot)
//   head->next  -> points to the FIRST node
//   display     -> the book currently shown on the screen
class CircularLinkedList
{
private:
    BookNode* head;
    BookNode* display;
    int count;

    BookNode* GetNodeAt(int index);
    void SwapData(BookNode* a, BookNode* b);
    int NormalizeIndex(int index);

public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList& other);
    CircularLinkedList& operator=(const CircularLinkedList& other);
    ~CircularLinkedList();

    bool IsEmpty();
    bool IsNotEmpty();

    void Insert(BookNode* book);       // insert at node next to head (front)
    BookNode* Remove();                // remove node next to head (front)
    void InsertAt(BookNode* book, int index);
    BookNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print();

    // Move the display to the next book. After the last book it goes
    // back to the first one. *wrapped is set to true when it wrapped around.
    BookNode* MoveToNext(bool* wrapped = nullptr);

    bool IsCircular();                 // does the last node link back to the first?
    void PrintCircularInfo();
    int GetCount();
};

#endif
