// Sequence.h

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include <iostream>
using namespace std;
  // Later in the course, we'll see that templates provide a much nicer
  // way of enabling us to have Sequences of different types.  For now,
  // we'll use a type alias.

    //Notes: 
    //1) Implement the sequence using a doubly-linked list
    // 
    //2) You must NOT use list class template from the C++ Library
    // 
    //3) You must implement the following as well:
    //- Destructor: When a Sequence is destroyed, the nodes in the linked list must be deallocated
    //- Copy Constructor: When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes
    //must be allocated to hold a duplicate of the original list.
    //- Assignment Operator: Wehn an existing Sequence (the left-side) is assigned the value of another Sequence (the right-hand side),
    //the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e.
    //no list node form the old value of the left-hand side should be still allocated yet inaccessible).
    //
    
    //WATCH OUT:
    //1) You must use include guards in the header files
    //2) DO NOT DELETE FUNCTION FROM OR CHANGE THE PUBLIC INTERFACE OF THE SEQUENCE CLASS
    //3)DO NOT DECLARE ANY ADDITIONAL STRUCT INSIDE SEQUENCE CLASS
using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 160;

class Sequence
{
public:
    Sequence();          // Create an empty sequence (i.e., one whose size() is 0).
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.

    //Need to Add: Destructor
    ~Sequence();

    //Need to Add: Copy Constructor
    Sequence(const Sequence& other);

    //Need to Add: Assignment operator
    Sequence& operator=(const Sequence& other);

    int insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one greater than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.

    int insert(const ItemType& value);
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item in position
    // p.  The original item in position p and those that follow it end
    // up at positions one greater than before.  Return p if the value
    // was actually inserted.  Return -1 if the value was not inserted
    // (perhaps because the sequence has a fixed capacity and is full).

    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.

    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).

    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item in position pos
    // of the sequence and return true.  Otherwise, leave value unchanged
    // and return false.

    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos of the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.

    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.

    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.

private:
    int      m_size;                     // number of items in the sequence
    ItemType m_data[DEFAULT_MAX_ITEMS];  // the items in the sequence
    // At any time, the elements of m_data indexed from 0 to m_size-1
    // are in use.

    void uncheckedInsert(int pos, const ItemType& value);
    // Insert value at position pos, shifting items to the right to make
    // room for it.  Assume pos is valid and there's room.

    struct Node {
        ItemType value;
        Node* next; //pointer to a node
        Node* previous; //pionter to previous node
    };

    struct Node* head; //pointer to head node

};

// Inline implementations

inline
int Sequence::size() const
{
    return m_size;
}

inline
bool Sequence::empty() const
{
    return size() == 0;
}

//IMPLEMENT: Sequence Algorithm 1
int subsequence(const Sequence& seq1, const Sequence& seq2);
//IMPLEMENT: Sequence Algorithm 2
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // SEQUENCE_INCLUDED