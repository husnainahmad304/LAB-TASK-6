// Library System
//   Lab 4: Priority Queue        -> Book Request Queue
//   Lab 5: Linked List           -> Book Collection Management
//   Lab 6: Circular Linked List  -> Featured Book Display Screen
#include <iostream>
#include <string>
#include "Input.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include "CircularLinkedList.h"
using namespace std;

// ============================================================
// Lab 4 menu: Book Request Queue (Priority Queue)
// ============================================================
void RequestMenu(PriorityQueue& requests)
{
    int choice = 0;

    do
    {
        cout << endl;
        cout << "Library Book Request System (Lab 4)" << endl;
        cout << "1. Add Book Request" << endl;
        cout << "2. Process Highest Priority Request" << endl;
        cout << "3. Display All Requests" << endl;
        cout << "4. Check Queue Status" << endl;
        cout << "5. Back to Main Menu" << endl;

        if (!ReadInt("Enter your choice: ", choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            BookRequestNode* request = new BookRequestNode;

            if (!ReadInt("Enter Student ID: ", request->studentID))
            {
                cout << "Invalid Student ID. Request not added." << endl;
                delete request;
                break;
            }

            cout << "Enter Student Name: ";
            getline(cin, request->studentName);

            if (!ReadInt("Enter Book ID: ", request->bookID))
            {
                cout << "Invalid Book ID. Request not added." << endl;
                delete request;
                break;
            }

            cout << "Enter Book Title: ";
            getline(cin, request->bookTitle);

            if (!ReadInt("Enter Priority (1=Exam/Urgent, 2=Assignment/Project, 3=Normal Reading): ",
                         request->priority) ||
                request->priority < 1 || request->priority > 3)
            {
                cout << "Invalid priority. Request not added." << endl;
                delete request;
                break;
            }

            requests.Add(request);
            cout << "Book request added successfully." << endl;
            break;
        }

        case 2:
        {
            BookRequestNode* processed = requests.Remove();
            if (processed == nullptr)
            {
                cout << "Queue is empty. No request to process." << endl;
            }
            else
            {
                cout << "===== Processing Request =====" << endl;
                cout << "Student ID: " << processed->studentID << endl;
                cout << "Student: " << processed->studentName << endl;
                cout << "Book ID: " << processed->bookID << endl;
                cout << "Book: " << processed->bookTitle << endl;
                cout << "Priority: " << processed->priority << endl;
                delete processed;
            }
            break;
        }

        case 3:
            if (requests.IsEmpty())
                cout << "No pending requests." << endl;
            else
            {
                cout << "===== All Pending Requests =====" << endl << endl;
                requests.PrintQueue();
            }
            break;

        case 4:
            if (requests.IsEmpty())
                cout << "Queue Status: Empty" << endl;
            else
                cout << "Queue Status: Not Empty (has pending requests)" << endl;
            break;

        case 5:
            break;

        default:
            cout << "Invalid choice. Please select 1-5." << endl;
        }

    } while (choice != 5);
}

// ============================================================
// Lab 5 menu: Book Collection (Linked List)
// ============================================================
BookNode* ReadBook()
{
    int id;
    if (!ReadInt("Enter Book ID: ", id))
    {
        cout << "Invalid Book ID. Book not added." << endl;
        return nullptr;
    }
    string title;
    cout << "Enter Book Title: ";
    getline(cin, title);
    return CreateBook(id, title);
}

void CollectionMenu(LinkedList& library)
{
    int choice = 0;

    do
    {
        cout << "\n========================================\n";
        cout << "     LIBRARY BOOK COLLECTION SYSTEM\n";
        cout << "========================================\n";
        cout << "1.  Display All Books\n";
        cout << "2.  Insert Book at Head\n";
        cout << "3.  Remove Book from Head\n";
        cout << "4.  Insert Book at Index\n";
        cout << "5.  Remove Book at Index\n";
        cout << "6.  Swap Books\n";
        cout << "7.  Sort Books by ID\n";
        cout << "8.  Reverse Book Collection\n";
        cout << "9.  Check Collection Status\n";
        cout << "10. Exit (Back to Main Menu)\n";

        if (!ReadInt("Enter your choice: ", choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            library.Print();
            break;

        case 2:
        {
            BookNode* book = ReadBook();
            if (book != nullptr)
            {
                library.Insert(book);
                cout << "Book inserted at head.\n";
            }
            break;
        }

        case 3:
        {
            BookNode* removed = library.Remove();
            if (removed != nullptr)
            {
                cout << "Removed book: " << removed->title << endl;
                delete removed;
            }
            else
                cout << "Collection is empty.\n";
            break;
        }

        case 4:
        {
            int index;
            if (!ReadInt("Enter index: ", index))
            {
                cout << "Invalid index.\n";
                break;
            }
            BookNode* book = ReadBook();
            if (book != nullptr)
            {
                library.InsertAt(book, index);
                cout << "Book inserted.\n";
            }
            break;
        }

        case 5:
        {
            int index;
            if (!ReadInt("Enter index: ", index))
            {
                cout << "Invalid index.\n";
                break;
            }
            BookNode* removed = library.RemoveAt(index);
            if (removed != nullptr)
            {
                cout << "Removed book: " << removed->title << endl;
                delete removed;
            }
            else
                cout << "Collection is empty.\n";
            break;
        }

        case 6:
        {
            int i1, i2;
            if (!ReadInt("Enter first index: ", i1) || !ReadInt("Enter second index: ", i2))
            {
                cout << "Invalid index.\n";
                break;
            }
            library.Swap(i1, i2);
            cout << "Swap done (invalid indexes are ignored).\n";
            break;
        }

        case 7:
            library.Sort();
            cout << "Books sorted by ID.\n";
            break;

        case 8:
            library.Reverse();
            cout << "Collection reversed.\n";
            break;

        case 9:
            if (library.IsEmpty())
                cout << "Collection is EMPTY.\n";
            else
                cout << "Collection is NOT empty. Total books: " << library.GetCount() << endl;
            break;

        case 10:
            break;

        default:
            cout << "Invalid choice. Please select 1-10.\n";
        }

    } while (choice != 10);
}

// ============================================================
// Lab 6 menu: Featured Book Display (Circular Linked List)
// ============================================================
void DisplayMenu(CircularLinkedList& display)
{
    int choice = 0;

    do
    {
        cout << "\n========================================\n";
        cout << "  CIRCULAR LIBRARY BOOK DISPLAY SYSTEM\n";
        cout << "========================================\n";
        cout << "1.  Display All Books\n";
        cout << "2.  Insert Book at Head\n";
        cout << "3.  Remove Book from Head\n";
        cout << "4.  Insert Book at Index\n";
        cout << "5.  Remove Book at Index\n";
        cout << "6.  Swap Books\n";
        cout << "7.  Sort Books by ID\n";
        cout << "8.  Reverse Book Collection\n";
        cout << "9.  Move to Next Book\n";
        cout << "10. Check Collection Status\n";
        cout << "11. Exit (Back to Main Menu)\n";

        if (!ReadInt("Enter your choice: ", choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            display.Print();
            break;

        case 2:
        {
            BookNode* book = ReadBook();
            if (book != nullptr)
            {
                display.Insert(book);
                cout << "Book inserted at head (front).\n";
            }
            break;
        }

        case 3:
        {
            BookNode* removed = display.Remove();
            if (removed != nullptr)
            {
                cout << "Removed book: " << removed->title << endl;
                delete removed;
            }
            else
                cout << "Collection is empty.\n";
            break;
        }

        case 4:
        {
            int index;
            if (!ReadInt("Enter index: ", index))
            {
                cout << "Invalid index.\n";
                break;
            }
            BookNode* book = ReadBook();
            if (book != nullptr)
            {
                display.InsertAt(book, index);
                cout << "Book inserted.\n";
            }
            break;
        }

        case 5:
        {
            int index;
            if (!ReadInt("Enter index: ", index))
            {
                cout << "Invalid index.\n";
                break;
            }
            BookNode* removed = display.RemoveAt(index);
            if (removed != nullptr)
            {
                cout << "Removed book: " << removed->title << endl;
                delete removed;
            }
            else
                cout << "Collection is empty.\n";
            break;
        }

        case 6:
        {
            int i1, i2;
            if (!ReadInt("Enter first index: ", i1) || !ReadInt("Enter second index: ", i2))
            {
                cout << "Invalid index.\n";
                break;
            }
            display.Swap(i1, i2);
            cout << "Swap done (indexes wrap around the circle).\n";
            break;
        }

        case 7:
            display.Sort();
            cout << "Books sorted by ID.\n";
            break;

        case 8:
            display.Reverse();
            cout << "Collection reversed.\n";
            break;

        case 9:
        {
            bool wrapped;
            BookNode* shown = display.MoveToNext(&wrapped);
            if (shown == nullptr)
                cout << "No books to display. Collection is empty.\n";
            else
            {
                cout << "Now displaying: [" << shown->bookID << "] " << shown->title << endl;
                if (wrapped)
                    cout << "(Reached the end - went back to the first book.)\n";
            }
            break;
        }

        case 10:
            display.PrintCircularInfo();
            break;

        case 11:
            break;

        default:
            cout << "Invalid choice. Please select 1-11.\n";
        }

    } while (choice != 11);
}

// ============================================================
// Main menu
// ============================================================
int main()
{
    PriorityQueue requests;          // Lab 4
    LinkedList library;              // Lab 5
    CircularLinkedList featured;     // Lab 6
    int choice = 0;

    do
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "          LIBRARY MANAGEMENT" << endl;
        cout << "========================================" << endl;
        cout << "1. Book Request Queue   (Lab 4 - Priority Queue)" << endl;
        cout << "2. Book Collection      (Lab 5 - Linked List)" << endl;
        cout << "3. Featured Book Screen (Lab 6 - Circular Linked List)" << endl;
        cout << "4. Exit" << endl;

        if (!ReadInt("Enter your choice: ", choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            RequestMenu(requests);
            break;
        case 2:
            CollectionMenu(library);
            break;
        case 3:
            DisplayMenu(featured);
            break;
        case 4:
            cout << "Exiting program. All memory released." << endl;
            break;
        default:
            cout << "Invalid choice. Please select 1-4." << endl;
        }
    } while (choice != 4);

    return 0;
}
