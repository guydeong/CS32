#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence arr(1000);   // a can hold at most 1000 items
    Sequence brr(5);      // b can hold at most 5 items
    Sequence crr;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType vrr = 14;

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(brr.insert(vrr) != -1);

    // Failure if we try to insert a sixth item into b
    assert(brr.insert(vrr) == -1);

    arr.swap(brr);
    assert(arr.insert(vrr) == -1 && brr.insert(vrr) != -1);

    cerr << "All tests passed" << endl;

    return 0;
}

