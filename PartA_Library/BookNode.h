#ifndef BOOKNODE_H
#define BOOKNODE_H

#include <string>
using namespace std;

// Lab 5 node: one book in the library collection
struct BookNode
{
    int bookID;
    string title;
    BookNode* next;
};

BookNode* CreateBook(int id, string title);

#endif
