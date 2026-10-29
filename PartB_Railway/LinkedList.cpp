#include <iostream>
#include <iomanip>
#include <utility>
#include "LinkedList.h"
using namespace std;

TrainNode* LinkedList::GetNodeAt(int index)
{
    TrainNode* current = head;
    for (int i = 0; i < index && current != nullptr; i++)
        current = current->next;
    return current;
}

void LinkedList::CopyTrainData(TrainNode* a, TrainNode* b)
{
    swap(a->trainID, b->trainID);
    swap(a->trainName, b->trainName);
    swap(a->destination, b->destination);
    swap(a->priority, b->priority);
}

LinkedList::LinkedList()
{
    head = nullptr;
    count = 0;
}

LinkedList::LinkedList(const LinkedList& other)
{
    head = nullptr;
    count = 0;
    TrainNode* current = other.head;
    while (current != nullptr)
    {
        InsertAt(CreateTrain(current->trainID, current->trainName,
                             current->destination, current->priority), count);
        current = current->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this == &other)
        return *this;
    while (!IsEmpty())
        delete Remove();
    TrainNode* current = other.head;
    while (current != nullptr)
    {
        InsertAt(CreateTrain(current->trainID, current->trainName,
                             current->destination, current->priority), count);
        current = current->next;
    }
    return *this;
}

LinkedList::~LinkedList()
{
    while (!IsEmpty())
        delete Remove();
}

void LinkedList::Insert(TrainNode* train)
{
    if (train == nullptr)
        return;
    train->next = head;
    head = train;
    count++;
}

TrainNode* LinkedList::Remove()
{
    if (IsEmpty())
        return nullptr;
    TrainNode* train = head;
    head = head->next;
    train->next = nullptr;
    count--;
    return train;
}

bool LinkedList::IsEmpty()
{
    return head == nullptr;
}

bool LinkedList::IsNotEmpty()
{
    return head != nullptr;
}

void LinkedList::InsertAt(TrainNode* train, int index)
{
    if (train == nullptr)
        return;
    if (index < 0)
        index = 0;
    if (index > count)
        index = count;
    if (index == 0)
    {
        Insert(train);
        return;
    }
    TrainNode* previous = GetNodeAt(index - 1);
    train->next = previous->next;
    previous->next = train;
    count++;
}

TrainNode* LinkedList::RemoveAt(int index)
{
    if (IsEmpty())
        return nullptr;
    if (index < 0)
        index = 0;
    if (index >= count)
        index = count - 1;
    if (index == 0)
        return Remove();
    TrainNode* previous = GetNodeAt(index - 1);
    TrainNode* train = previous->next;
    previous->next = train->next;
    train->next = nullptr;
    count--;
    return train;
}

void LinkedList::Swap(int index1, int index2)
{
    if (index1 < 0 || index1 >= count || index2 < 0 || index2 >= count)
        return;
    if (index1 == index2)
        return;
    CopyTrainData(GetNodeAt(index1), GetNodeAt(index2));
}

void LinkedList::Sort()
{
    for (TrainNode* i = head; i != nullptr; i = i->next)
    {
        for (TrainNode* j = i->next; j != nullptr; j = j->next)
        {
            if (i->trainID > j->trainID)
                CopyTrainData(i, j);
        }
    }
}

void LinkedList::Reverse()
{
    TrainNode* previous = nullptr;
    TrainNode* current = head;
    TrainNode* next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}

void LinkedList::Print()
{
    TrainNode* current = head;
    int index = 0;
    cout << "\n" << left << setw(7) << "Index" << setw(10) << "Train ID"
         << setw(20) << "Train Name" << setw(15) << "Destination"
         << "Priority\n";
    cout << "-------------------------------------------------------------\n";
    while (current != nullptr)
    {
        cout << left << setw(7) << index << setw(10) << current->trainID
             << setw(20) << current->trainName << setw(15) << current->destination
             << current->priority << endl;
        current = current->next;
        index++;
    }
    cout << "Total trains: " << count << endl;
}

int LinkedList::GetCount()
{
    return count;
}
