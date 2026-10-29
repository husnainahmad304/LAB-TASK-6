#ifndef INPUT_H
#define INPUT_H

#include <string>
using namespace std;

// Reads an integer safely. Returns false if the user typed something invalid.
bool ReadInt(const string& message, int& value);

#endif
