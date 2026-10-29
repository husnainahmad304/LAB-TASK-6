#include <iostream>
#include <utility>
#include "LinkedList.h"
using namespace std;

BookNode* LinkedList::GetNodeAt(int index)
{
    BookNode* current = head;
    for (int i = 0; i < index && current != nullptr; i++)
        current = current->next;
    return current;
}

void LinkedList::CopyBookData(BookNode* a, BookNode* b)
{
    swap(a->bookID, b->bookID);
    swap(a->title, b->title);
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
    BookNode* current = other.head;
    while (current != nullptr)
    {
        BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
        InsertAt(copy, count);
        current = current->next;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this == &other)
        return *this;
    while (!IsEmpty())
        delete Remove();
    BookNode* current = other.head;
    while (current != nullptr)
    {
        BookNode* copy = new BookNode{ current->bookID, current->title, nullptr };
        InsertAt(copy, count);
        current = current->next;
    }
    return *this;
}

LinkedList::~LinkedList()
{
    while (!IsEmpty())
        delete Remove();
}

void LinkedList::Insert(BookNode* book)
{
    if (book == nullptr)
        return;
    book->next = head;
    head = book;
    count++;
}

BookNode* LinkedList::Remove()
{
    if (IsEmpty())
        return nullptr;
    BookNode* book = head;
    head = head->next;
    book->next = nullptr;
    count--;
    return book;
}

bool LinkedList::IsEmpty()
{
    return head == nullptr;
}

bool LinkedList::IsNotEmpty()
{
    return head != nullptr;
}

void LinkedList::InsertAt(BookNode* book, int index)
{
    if (book == nullptr)
        return;
    if (index < 0)
        index = 0;
    if (index > count)
        index = count;
    if (index == 0)
    {
        Insert(book);
        return;
    }
    BookNode* previous = GetNodeAt(index - 1);
    book->next = previous->next;
    previous->next = book;
    count++;
}

BookNode* LinkedList::RemoveAt(int index)
{
    if (IsEmpty())
        return nullptr;
    if (index < 0)
        index = 0;
    if (index >= count)
        index = count - 1;
    if (index == 0)
        return Remove();
    BookNode* previous = GetNodeAt(index - 1);
    BookNode* book = previous->next;
    previous->next = book->next;
    book->next = nullptr;
    count--;
    return book;
}

void LinkedList::Swap(int index1, int index2)
{
    if (index1 < 0 || index1 >= count || index2 < 0 || index2 >= count)
        return;
    if (index1 == index2)
        return;
    CopyBookData(GetNodeAt(index1), GetNodeAt(index2));
}

void LinkedList::Sort()
{
    for (BookNode* i = head; i != nullptr; i = i->next)
    {
        for (BookNode* j = i->next; j != nullptr; j = j->next)
        {
            if (i->bookID > j->bookID)
                CopyBookData(i, j);
        }
    }
}

void LinkedList::Reverse()
{
    BookNode* previous = nullptr;
    BookNode* current = head;
    BookNode* next = nullptr;
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
    BookNode* current = head;
    int index = 0;
    cout << "\nIndex\tBook ID\tTitle\n";
    cout << "-----------------------------------\n";
    while (current != nullptr)
    {
        cout << index << "\t" << current->bookID << "\t" << current->title << endl;
        current = current->next;
        index++;
    }
    cout << "Total books: " << count << endl;
}

int LinkedList::GetCount()
{
    return count;
}
