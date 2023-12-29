#ifndef RAINFALLLIST_H
#define RAINFALLLIST_H

#include "Sequence.h"
#include <limits>
//NOTES: 
//1) The words for and while must not appear in RainfallList.h or RainfallList.cpp, except for implementation of minimum and maximum
//2) The characters [ (open square bracket) and * must not appear in RainfallList.h or RainfallList.cpp except in comments if you wish
//3) You do not have to change unsigned long to ItemType in RainfallList.h and RainfallList.cpp if you don't want to (since unlike Sequence, which is designed for a wide variety of item types, RainfallList is specifically designed to work with unsigned longs)
const unsigned long NO_RAINFALLS = std::numeric_limits<unsigned long>::max();

class RainfallList
{
public:
    RainfallList();       // Create an empty rainfall list.

    bool add(unsigned long rainfall);
    // If the rainfall is valid (a value from 0 to 400) and the rainfall list
    // has room for it, add it to the rainfall list and return true.
    // Otherwise, leave the rainfall list unchanged and return false.

    bool remove(unsigned long rainfall);
    // Remove one instance of the specified rainfall from the rainfall list.
    // Return true if a rainfall was removed; otherwise false.

    int size() const;  // Return the number of rainfalls in the list.

    unsigned long minimum() const;
    // Return the lowest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.

    unsigned long maximum() const;
    // Return the highest-valued rainfall in the rainfall list.  If the list is
    // empty, return NO_RAINFALLS.

private:
    // Some of your code goes here.
    Sequence m_arr;
};

#endif