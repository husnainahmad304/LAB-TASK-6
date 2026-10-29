#ifndef BOOKREQUESTNODE_H
#define BOOKREQUESTNODE_H

#include <string>
using namespace std;

// Lab 4 node: one book request in the priority queue
struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

#endif
