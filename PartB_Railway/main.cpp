// Railway System (Individual Project)
//   Lab 4: Priority Queue       -> dispatch the highest-priority train first
//   Lab 5: Linked List          -> Train Timetable (insert, remove, swap, sort, reverse)
//   Lab 6: Circular Linked List -> Station Departure Board that keeps rotating
#include <iostream>
#include <string>
#include "Input.h"
#include "PriorityQueue.h"
#include "LinkedList.h"
#include "CircularLinkedList.h"
using namespace std;

// Reads one train from the user. Returns nullptr if input was invalid.
TrainNode* ReadTrain()
{
    int id, priority;

    if (!ReadInt("Enter Train ID: ", id))
    {
        cout << "Invalid Train ID. Train not added." << endl;
        return nullptr;
    }

    string name, destination;
    cout << "Enter Train Name: ";
    getline(cin, name);
    cout << "Enter Destination: ";
    getline(cin, destination);

    if (!ReadInt("Enter Priority (1=Express/Mail, 2=Passenger, 3=Freight): ", priority) ||
        priority < 1 || priority > 3)
    {
        cout << "Invalid priority. Train not added." << endl;
        return nullptr;
    }
    return CreateTrain(id, name, destination, priority);
}

// ============================================================
// Lab 4 menu: Priority Queue
// ============================================================
void QueueMenu(PriorityQueue& trains)
{
    int choice = 0;

    do
    {
        cout << endl;
        cout << "Railway Train Scheduling System (Lab 4)" << endl;
        cout << "1. Add Train to Queue" << endl;
        cout << "2. Dispatch Highest Priority Train" << endl;
        cout << "3. Display All Waiting Trains" << endl;
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
            TrainNode* train = ReadTrain();
            if (train != nullptr)
            {
                trains.Add(train);
                cout << "Train added to queue successfully." << endl;
            }
            break;
        }

        case 2:
        {
            TrainNode* dispatched = trains.Remove();
            if (dispatched == nullptr)
                cout << "Queue is empty. No train to dispatch." << endl;
            else
            {
                cout << "===== Dispatching Train =====" << endl;
                cout << "Train ID: " << dispatched->trainID << endl;
                cout << "Train Name: " << dispatched->trainName << endl;
                cout << "Destination: " << dispatched->destination << endl;
                cout << "Priority: " << dispatched->priority << endl;
                delete dispatched;
            }
            break;
        }

        case 3:
            if (trains.IsEmpty())
                cout << "No trains waiting." << endl;
            else
            {
                cout << "===== Waiting Trains =====" << endl << endl;
                trains.PrintQueue();
            }
            break;

        case 4:
            if (trains.IsEmpty())
                cout << "Queue Status: Empty" << endl;
            else
                cout << "Queue Status: Not Empty (trains waiting)" << endl;
            break;

        case 5:
            break;

        default:
            cout << "Invalid choice. Please select 1-5." << endl;
        }

    } while (choice != 5);
}

// ============================================================
// Lab 5 menu: Train Timetable (Linked List)
// ============================================================
void LoadSampleTrains(LinkedList& timetable)
{
    timetable.InsertAt(CreateTrain(305, "Karakoram Express", "Karachi", 1), 0);
    timetable.InsertAt(CreateTrain(301, "Green Line", "Lahore", 1), 1);
    timetable.InsertAt(CreateTrain(304, "Awam Express", "Peshawar", 2), 2);
    timetable.InsertAt(CreateTrain(302, "Freight Cargo", "Quetta", 3), 3);
    timetable.InsertAt(CreateTrain(303, "Shalimar Express", "Multan", 2), 4);
    cout << "Sample trains loaded." << endl;
}

void TimetableMenu(LinkedList& timetable)
{
    int choice = 0;

    do
    {
        cout << "\n========================================\n";
        cout << "     TRAIN TIMETABLE MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1.  Display All Trains\n";
        cout << "2.  Insert Train at Head\n";
        cout << "3.  Remove Train from Head\n";
        cout << "4.  Insert Train at Index\n";
        cout << "5.  Remove Train at Index\n";
        cout << "6.  Swap Trains\n";
        cout << "7.  Sort Trains by ID\n";
        cout << "8.  Reverse Timetable\n";
        cout << "9.  Check Timetable Status\n";
        cout << "10. Load Sample Trains\n";
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
            timetable.Print();
            break;

        case 2:
        {
            TrainNode* train = ReadTrain();
            if (train != nullptr)
            {
                timetable.Insert(train);
                cout << "Train inserted at head.\n";
            }
            break;
        }

        case 3:
        {
            TrainNode* removed = timetable.Remove();
            if (removed != nullptr)
            {
                cout << "Removed train: " << removed->trainName << endl;
                delete removed;
            }
            else
                cout << "Timetable is empty.\n";
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
            TrainNode* train = ReadTrain();
            if (train != nullptr)
            {
                timetable.InsertAt(train, index);
                cout << "Train inserted.\n";
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
            TrainNode* removed = timetable.RemoveAt(index);
            if (removed != nullptr)
            {
                cout << "Removed train: " << removed->trainName << endl;
                delete removed;
            }
            else
                cout << "Timetable is empty.\n";
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
            timetable.Swap(i1, i2);
            cout << "Swap done (invalid indexes are ignored).\n";
            break;
        }

        case 7:
            timetable.Sort();
            cout << "Trains sorted by ID.\n";
            break;

        case 8:
            timetable.Reverse();
            cout << "Timetable reversed.\n";
            break;

        case 9:
            if (timetable.IsEmpty())
                cout << "Timetable is EMPTY.\n";
            else
                cout << "Timetable is NOT empty. Total trains: " << timetable.GetCount() << endl;
            break;

        case 10:
            LoadSampleTrains(timetable);
            break;

        case 11:
            break;

        default:
            cout << "Invalid choice. Please select 1-11.\n";
        }

    } while (choice != 11);
}

// ============================================================
// Lab 6 menu: Departure Board (Circular Linked List)
// ============================================================
void LoadSampleBoard(CircularLinkedList& board)
{
    board.InsertAt(CreateTrain(305, "Karakoram Express", "Karachi", 1), board.GetCount());
    board.InsertAt(CreateTrain(301, "Green Line", "Lahore", 1), board.GetCount());
    board.InsertAt(CreateTrain(304, "Awam Express", "Peshawar", 2), board.GetCount());
    board.InsertAt(CreateTrain(302, "Freight Cargo", "Quetta", 3), board.GetCount());
    cout << "Sample trains loaded on the board." << endl;
}

void ShowTrain(TrainNode* train, bool wrapped)
{
    cout << "Now showing: [" << train->trainID << "] " << train->trainName
         << " -> " << train->destination << endl;
    if (wrapped)
        cout << "  (Reached the last train - went back to the first train.)" << endl;
}

void BoardMenu(CircularLinkedList& board)
{
    int choice = 0;

    do
    {
        cout << "\n========================================\n";
        cout << "  CIRCULAR STATION DEPARTURE BOARD SYSTEM\n";
        cout << "========================================\n";
        cout << "1.  Display All Trains\n";
        cout << "2.  Insert Train at Head\n";
        cout << "3.  Remove Train from Head\n";
        cout << "4.  Insert Train at Index\n";
        cout << "5.  Remove Train at Index\n";
        cout << "6.  Swap Trains\n";
        cout << "7.  Sort Trains by ID\n";
        cout << "8.  Reverse Train Order\n";
        cout << "9.  Move to Next Train\n";
        cout << "10. Rotate Board N Times (circular traversal demo)\n";
        cout << "11. Check Board Status (circular link check)\n";
        cout << "12. Load Sample Trains\n";
        cout << "13. Exit (Back to Main Menu)\n";

        if (!ReadInt("Enter your choice: ", choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            board.Print();
            break;

        case 2:
        {
            TrainNode* train = ReadTrain();
            if (train != nullptr)
            {
                board.Insert(train);
                cout << "Train inserted at head (front).\n";
            }
            break;
        }

        case 3:
        {
            TrainNode* removed = board.Remove();
            if (removed != nullptr)
            {
                cout << "Removed train: " << removed->trainName << endl;
                delete removed;
            }
            else
                cout << "Board is empty.\n";
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
            TrainNode* train = ReadTrain();
            if (train != nullptr)
            {
                board.InsertAt(train, index);
                cout << "Train inserted.\n";
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
            TrainNode* removed = board.RemoveAt(index);
            if (removed != nullptr)
            {
                cout << "Removed train: " << removed->trainName << endl;
                delete removed;
            }
            else
                cout << "Board is empty.\n";
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
            board.Swap(i1, i2);
            cout << "Swap done (indexes wrap around the circle).\n";
            break;
        }

        case 7:
            board.Sort();
            cout << "Trains sorted by ID.\n";
            break;

        case 8:
            board.Reverse();
            cout << "Train order reversed.\n";
            break;

        case 9:
        {
            bool wrapped;
            TrainNode* shown = board.MoveToNext(&wrapped);
            if (shown == nullptr)
                cout << "No trains to show. Board is empty.\n";
            else
                ShowTrain(shown, wrapped);
            break;
        }

        case 10:
        {
            int steps;
            if (!ReadInt("How many times to rotate? ", steps) || steps < 1)
            {
                cout << "Please enter a number greater than 0.\n";
                break;
            }
            if (board.IsEmpty())
            {
                cout << "No trains to show. Board is empty.\n";
                break;
            }
            for (int i = 1; i <= steps; i++)
            {
                bool wrapped;
                TrainNode* shown = board.MoveToNext(&wrapped);
                cout << "Step " << i << ": ";
                ShowTrain(shown, wrapped);
            }
            break;
        }

        case 11:
            board.PrintCircularInfo();
            break;

        case 12:
            LoadSampleBoard(board);
            break;

        case 13:
            break;

        default:
            cout << "Invalid choice. Please select 1-13.\n";
        }

    } while (choice != 13);
}

// ============================================================
// Main menu
// ============================================================
int main()
{
    PriorityQueue trains;         // Lab 4
    LinkedList timetable;         // Lab 5
    CircularLinkedList board;     // Lab 6
    int choice = 0;

    do
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "        RAILWAY MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << "1. Train Dispatch Queue  (Lab 4 - Priority Queue)" << endl;
        cout << "2. Train Timetable       (Lab 5 - Linked List)" << endl;
        cout << "3. Departure Board       (Lab 6 - Circular Linked List)" << endl;
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
            QueueMenu(trains);
            break;
        case 2:
            TimetableMenu(timetable);
            break;
        case 3:
            BoardMenu(board);
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
