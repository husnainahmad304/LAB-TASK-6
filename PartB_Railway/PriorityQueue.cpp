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
    TrainNode* current = other.front;
    while (current != nullptr)
    {
        Add(CreateTrain(current->trainID, current->trainName,
                        current->destination, current->priority));
        current = current->next;
    }
}

void PriorityQueue::Clear()
{
    while (front != nullptr)
    {
        TrainNode* temp = front;
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

void PriorityQueue::Add(TrainNode* train)
{
    train->next = nullptr;

    if (front == nullptr)
    {
        front = train;
        rear = train;
    }
    else if (train->priority < front->priority)
    {
        train->next = front;
        front = train;
    }
    else
    {
        TrainNode* current = front;
        while (current->next != nullptr &&
               current->next->priority <= train->priority)
        {
            current = current->next;
        }
        train->next = current->next;
        current->next = train;

        if (train->next == nullptr)
            rear = train;
    }
    count++;
}

TrainNode* PriorityQueue::Remove()
{
    if (front == nullptr)
        return nullptr;
    TrainNode* train = front;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    train->next = nullptr;
    count--;
    return train;
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
    TrainNode* current = front;
    while (current != nullptr)
    {
        cout << "Train ID: " << current->trainID << endl;
        cout << "Train Name: " << current->trainName << endl;
        cout << "Destination: " << current->destination << endl;
        cout << "Priority: " << current->priority << endl;
        cout << "-----------------------------" << endl;
        current = current->next;
    }
}
