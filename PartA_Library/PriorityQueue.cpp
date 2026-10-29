#include <iostream>
#include "PriorityQueue.h"
using namespace std;

PriorityQueue::PriorityQueue()
{
    front = nullptr;
    rear = nullptr;
    count = 0;
}

void PriorityQueue::CopyFrom(const PriorityQueue& other)
{
    BookRequestNode* current = other.front;
    while (current != nullptr)
    {
        BookRequestNode* newNode = new BookRequestNode;
        newNode->studentID = current->studentID;
        newNode->studentName = current->studentName;
        newNode->bookID = current->bookID;
        newNode->bookTitle = current->bookTitle;
        newNode->priority = current->priority;
        newNode->next = nullptr;
        Add(newNode);
        current = current->next;
    }
}

void PriorityQueue::Clear()
{
    while (front != nullptr)
    {
        BookRequestNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    count = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue& other)
{
    front = nullptr;
    rear = nullptr;
    count = 0;
    CopyFrom(other);
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other)
{
    if (this == &other)
        return *this;
    Clear();
    CopyFrom(other);
    return *this;
}

PriorityQueue::~PriorityQueue()
{
    Clear();
}

void PriorityQueue::Add(BookRequestNode* request)
{
    request->next = nullptr;

    if (front == nullptr)
    {
        front = request;
        rear = request;
    }
    else if (request->priority < front->priority)
    {
        request->next = front;
        front = request;
    }
    else
    {
        BookRequestNode* current = front;
        while (current->next != nullptr &&
               current->next->priority <= request->priority)
        {
            current = current->next;
        }
        request->next = current->next;
        current->next = request;
        if (request->next == nullptr)
            rear = request;
    }
    count++;
}

BookRequestNode* PriorityQueue::Remove()
{
    if (front == nullptr)
        return nullptr;
    BookRequestNode* request = front;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    request->next = nullptr;
    count--;
    return request;
}

bool PriorityQueue::IsEmpty()
{
    return front == nullptr;
}

bool PriorityQueue::IsNotEmpty()
{
    return front != nullptr;
}

void PriorityQueue::PrintQueue()
{
    BookRequestNode* current = front;
    while (current != nullptr)
    {
        cout << "Student ID: " << current->studentID << endl;
        cout << "Student Name: " << current->studentName << endl;
        cout << "Book ID: " << current->bookID << endl;
        cout << "Book Title: " << current->bookTitle << endl;
        cout << "Priority: " << current->priority << endl;
        cout << "-----------------------------" << endl;
        current = current->next;
    }
}
