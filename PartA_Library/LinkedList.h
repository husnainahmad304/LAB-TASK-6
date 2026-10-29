#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "BookNode.h"

// Lab 5: general-purpose singly linked list for the book collection
class LinkedList
{
private:
    BookNode* head;
    int count;

    BookNode* GetNodeAt(int index);
    void CopyBookData(BookNode* a, BookNode* b);

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();

    void Insert(BookNode* book);
    BookNode* Remove();
    bool IsEmpty();
    bool IsNotEmpty();
    void InsertAt(BookNode* book, int index);
    BookNode* RemoveAt(int index);
    void Swap(int index1, int index2);
    void Sort();
    void Reverse();
    void Print();
    int GetCount();
};

#endif
