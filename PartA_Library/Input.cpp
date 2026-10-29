#include <iostream>
#include <limits>
#include "Input.h"
using namespace std;

bool ReadInt(const string& message, int& value)
{
    cout << message;
    cin >> value;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}
