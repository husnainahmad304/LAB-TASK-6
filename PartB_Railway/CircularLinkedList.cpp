#include <iostream>
#include <iomanip>
#include <utility>
#include "CircularLinkedList.h"
using namespace std;

// ---------- private helpers ----------
TrainNode* CircularLinkedList::GetNodeAt(int index)
{
    if (head == nullptr)
        return nullptr;
    TrainNode* current = head->next;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

void CircularLinkedList::SwapData(TrainNode* a, TrainNode* b)
{
    swap(a->trainID, b->trainID);
    swap(a->trainName, b->trainName);
    swap(a->destination, b->destination);
    swap(a->priority, b->priority);
}

// Normalize a circular index to 0..count-1
int CircularLinkedList::NormalizeIndex(int index)
{
    return ((index % count) + count) % count;
}

// ---------- constructor / copy / assignment / destructor ----------
CircularLinkedList::CircularLinkedList()
{
    head = nullptr;
    display = nullptr;
    count = 0;
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList& other)
{
    head = nullptr;
    display = nullptr;
    count = 0;
    if (other.head == nullptr)
        return;
    TrainNode* current = other.head->next;
    for (int i = 0; i < other.count; i++)
    {
        InsertAt(CreateTrain(current->trainID, current->trainName,
                             current->destination, current->priority), count);
        current = current->next;
    }
}

CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& other)
{
    if (this == &other)
        return *this;
    while (IsNotEmpty())
        delete Remove();
    display = nullptr;
    if (other.head == nullptr)
        return *this;
    TrainNode* current = other.head->next;
    for (int i = 0; i < other.count; i++)
    {
        InsertAt(CreateTrain(current->trainID, current->trainName,
                             current->destination, current->priority), count);
        current = current->next;
    }
    return *this;
}

CircularLinkedList::~CircularLinkedList()
{
    while (IsNotEmpty())
        delete Remove();
}

// ---------- status ----------
bool CircularLinkedList::IsEmpty()
{
    return count == 0;
}

bool CircularLinkedList::IsNotEmpty()
{
    return count > 0;
}

// ---------- insert / remove at the front (node next to head) ----------
void CircularLinkedList::Insert(TrainNode* train)
{
    if (train == nullptr)
        return;
    if (head == nullptr)
    {
        head = train;
        train->next = train;
    }
    else
    {
        train->next = head->next;
        head->next = train;
    }
    count++;
}

TrainNode* CircularLinkedList::Remove()
{
    if (IsEmpty())
        return nullptr;
    TrainNode* first = head->next;
    if (first == display)
        display = nullptr;
    if (first == head)
        head = nullptr;
    else
        head->next = first->next;
    first->next = nullptr;
    count--;
    return first;
}

// ---------- insert / remove at an index ----------
void CircularLinkedList::InsertAt(TrainNode* train, int index)
{
    if (train == nullptr)
        return;
    if (count == 0)
    {
        head = train;
        train->next = train;
        count++;
        return;
    }
    // Negative indexes wrap around the circle
    if (index < 0)
        index = NormalizeIndex(index);
    // Index greater than count wraps around
    if (index > count)
        index %= count;
    // Insert at the beginning
    if (index == 0)
    {
        Insert(train);
        return;
    }
    // Insert at the end
    if (index == count)
    {
        train->next = head->next;
        head->next = train;
        head = train;
        count++;
        return;
    }
    // Insert in the middle
    TrainNode* previous = GetNodeAt(index - 1);
    train->next = previous->next;
    previous->next = train;
    count++;
}

TrainNode* CircularLinkedList::RemoveAt(int index)
{
    if (IsEmpty())
        return nullptr;
    index = NormalizeIndex(index);
    if (index == 0)
        return Remove();
    TrainNode* previous = GetNodeAt(index - 1);
    TrainNode* target = previous->next;
    previous->next = target->next;
    // Update head if removing the last node
    if (target == head)
        head = previous;
    if (target == display)
        display = nullptr;
    target->next = nullptr;
    count--;
    return target;
}

// ---------- swap / sort / reverse ----------
void CircularLinkedList::Swap(int index1, int index2)
{
    if (IsEmpty())
        return;
    index1 = NormalizeIndex(index1);
    index2 = NormalizeIndex(index2);
    if (index1 == index2)
        return;
    SwapData(GetNodeAt(index1), GetNodeAt(index2));
}

void CircularLinkedList::Sort()
{
    if (count < 2)
        return;
    TrainNode* current = head->next;
    for (int i = 0; i < count - 1; i++)
    {
        TrainNode* nextNode = current->next;
        for (int j = i + 1; j < count; j++)
        {
            if (current->trainID > nextNode->trainID)
                SwapData(current, nextNode);
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

void CircularLinkedList::Reverse()
{
    if (count < 2)
        return;
    TrainNode* oldTail = head;
    TrainNode* oldFirst = head->next;
    TrainNode* previous = oldTail;
    TrainNode* current = oldFirst;
    while (current != oldTail)
    {
        TrainNode* nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }
    oldTail->next = previous;
    head = oldFirst;     // old first becomes the new last node
}

// ---------- print (exactly count nodes) ----------
void CircularLinkedList::Print()
{
    if (IsEmpty())
    {
        cout << "No trains on the board.\n";
        return;
    }
    TrainNode* current = head->next;
    cout << "\n" << left << setw(7) << "Index" << setw(10) << "Train ID"
         << setw(20) << "Train Name" << setw(15) << "Destination"
         << "Priority\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < count; i++)
    {
        cout << left << setw(7) << i << setw(10) << current->trainID
             << setw(20) << current->trainName << setw(15) << current->destination
             << current->priority;
        if (current == display)
            cout << "   <-- on board";
        cout << endl;
        current = current->next;
    }
    cout << "Total trains: " << count << endl;
}

// ---------- circular traversal ----------
TrainNode* CircularLinkedList::MoveToNext(bool* wrapped)
{
    if (wrapped != nullptr)
        *wrapped = false;
    if (IsEmpty())
        return nullptr;

    if (display == nullptr)
        display = head->next;              // nothing shown yet: start at first train
    else
    {
        if (display == head && wrapped != nullptr)
            *wrapped = true;               // moving from last train back to first
        display = display->next;           // never reaches nullptr
    }
    return display;
}

bool CircularLinkedList::IsCircular()
{
    if (IsEmpty())
        return false;
    TrainNode* current = head->next;
    for (int i = 0; i < count - 1; i++)
    {
        if (current == nullptr)
            return false;
        current = current->next;
    }
    return current == head && head->next != nullptr;
}

void CircularLinkedList::PrintCircularInfo()
{
    if (IsEmpty())
    {
        cout << "Board is EMPTY.\n";
        return;
    }
    TrainNode* first = head->next;
    cout << "Board is NOT empty. Total trains: " << count << endl;
    cout << "First train : [" << first->trainID << "] " << first->trainName << endl;
    cout << "Last train  : [" << head->trainID << "] " << head->trainName << endl;
    cout << "Last train links back to first train: "
         << (IsCircular() ? "YES (circular)" : "NO") << endl;
}

int CircularLinkedList::GetCount()
{
    return count;
}
