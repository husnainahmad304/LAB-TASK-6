#ifndef TRAINNODE_H
#define TRAINNODE_H

#include <string>
using namespace std;

// Self-referential node: used by BOTH the Priority Queue (Lab 4)
// and the Linked List (Lab 5). Each train points to the next train.
struct TrainNode
{
    int trainID;
    string trainName;
    string destination;
    int priority;          // 1 = Express/Mail, 2 = Passenger, 3 = Freight
    TrainNode* next;
};

TrainNode* CreateTrain(int id, string name, string destination, int priority);

#endif
