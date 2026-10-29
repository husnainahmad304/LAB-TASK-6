#include "TrainNode.h"

TrainNode* CreateTrain(int id, string name, string destination, int priority)
{
    TrainNode* train = new TrainNode;
    train->trainID = id;
    train->trainName = name;
    train->destination = destination;
    train->priority = priority;
    train->next = nullptr;
    return train;
}
