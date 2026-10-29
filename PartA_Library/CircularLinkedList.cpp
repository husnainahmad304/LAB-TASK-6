#include <iostream>
#include <utility>
#include "CircularLinkedList.h"
using namespace std;

// ---------- private helpers ----------
BookNode* CircularLinkedList::GetNodeAt(int index)
{
    if (head == nullptr)
        return nullptr;
    BookNode* current = head->next;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

void CircularLinkedList::SwapData(BookNode* a, BookNode* b)
{
    swap(a->bookID, b->bookID);
    swap(a->title, b->title);
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
    BookNode* current = other.head->next;
    for (int i = 0; i < other.count; i++)
    {
        BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
        InsertAt(copy, count);
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
    BookNode* current = other.head->next;
    for (int i = 0; i < other.count; i++)
    {
        BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
        InsertAt(copy, count);
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
void CircularLinkedList::Insert(BookNode* book)
{
    if (book == nullptr)
        return;
    if (head == nullptr)
    {
        head = book;
        book->next = book;
    }
    else
    {
        book->next = head->next;
        head->next = book;
    }
    count++;
}

BookNode* CircularLinkedList::Remove()
{
    if (IsEmpty())
        return nullptr;
    BookNode* first = head->next;
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
void CircularLinkedList::InsertAt(BookNode* book, int index)
{
    if (book == nullptr)
        return;
    if (count == 0)
    {
        head = book;
        book->next = book;
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
        Insert(book);
        return;
    }
    // Insert at the end
    if (index == count)
    {
        book->next = head->next;
        head->next = book;
        head = book;
        count++;
        return;
    }
    // Insert in the middle
    BookNode* previous = GetNodeAt(index - 1);
    book->next = previous->next;
    previous->next = book;
    count++;
}

BookNode* CircularLinkedList::RemoveAt(int index)
{
    if (IsEmpty())
        return nullptr;
    index = NormalizeIndex(index);
    if (index == 0)
        return Remove();
    BookNode* previous = GetNodeAt(index - 1);
    BookNode* target = previous->next;
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
    BookNode* current = head->next;
    for (int i = 0; i < count - 1; i++)
    {
        BookNode* nextNode = current->next;
        for (int j = i + 1; j < count; j++)
        {
            if (current->bookID > nextNode->bookID)
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
    BookNode* oldTail = head;
    BookNode* oldFirst = head->next;
    BookNode* previous = oldTail;
    BookNode* current = oldFirst;
    while (current != oldTail)
    {
        BookNode* nextNode = current->next;
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
        cout << "No books in the collection.\n";
        return;
    }
    BookNode* current = head->next;
    cout << "\nIndex\tBook ID\tTitle\n";
    cout << "-----------------------------------\n";
    for (int i = 0; i < count; i++)
    {
        cout << i << "\t" << current->bookID << "\t" << current->title;
        if (current == display)
            cout << "   <-- on screen";
        cout << endl;
        current = current->next;
    }
    cout << "Total books: " << count << endl;
}

// ---------- circular traversal ----------
BookNode* CircularLinkedList::MoveToNext(bool* wrapped)
{
    if (wrapped != nullptr)
        *wrapped = false;
    if (IsEmpty())
        return nullptr;

    if (display == nullptr)
        display = head->next;              // nothing shown yet: start at first book
    else
    {
        if (display == head && wrapped != nullptr)
            *wrapped = true;               // moving from last book back to first
        display = display->next;           // never reaches nullptr
    }
    return display;
}

bool CircularLinkedList::IsCircular()
{
    if (IsEmpty())
        return false;
    BookNode* current = head->next;
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
        cout << "Collection is EMPTY.\n";
        return;
    }
    BookNode* first = head->next;
    cout << "Collection is NOT empty. Total books: " << count << endl;
    cout << "First book : [" << first->bookID << "] " << first->title << endl;
    cout << "Last book  : [" << head->bookID << "] " << head->title << endl;
    cout << "Last book links back to first book: "
         << (IsCircular() ? "YES (circular)" : "NO") << endl;
}

int CircularLinkedList::GetCount()
{
    return count;
}
