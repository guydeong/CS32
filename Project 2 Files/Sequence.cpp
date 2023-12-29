// Sequence.cpp

#include "Sequence.h"


//Things to consider when implementing double-linked list:
//1) Implement circular doubly-linked list. Will only require 1 pointer: head. Tail of the list will be at head->m_prev
//Finished
Sequence::Sequence(){
    //When constructing, set the head and tail equal to nullptrs
    this->head = nullptr;
    this->m_size = 0;
}

//Destructor
//Finished
Sequence::~Sequence() {
    //Delete every item in the sequence
    if (m_size != 0) {
        Node* temp = head;
        for (int i = 0; i < m_size; i++) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        } 
    }
    //Prevent dangling pointer
    head = nullptr;
    m_size = 0;
    
}

//Copy Constructor
//Finished
Sequence::Sequence(const Sequence& other) {
    
    //If the other linked list is empty, set the new sequence as empty too
    if (other.head == nullptr) {
        this->head = nullptr;
        this->m_size = 0;
    }
    //Otherwise swap the values
    else {
        this->head = nullptr;
        this->m_size = 0;

        //Create Nodes for the current Sequence
        for (int i = 0; i < other.size(); i++) {
            ItemType x;
            other.get(i, x);
            this->insert(i, x);
        }
    }
    
    
}

//Assignment Operator
//Finished
Sequence& Sequence::operator=(const Sequence& other) {
    //If statement to prevent aliasing
    if (this == &other) {
        return *this;
    }

    //Copy the values into temp
    Sequence temp(other);

    //Swap the values with temp
    swap(temp);
    
    return *this;
}

//Finished
int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > size() || size() == DEFAULT_MAX_ITEMS)
        return -1;
    uncheckedInsert(pos, value);
    return pos;
}

//Finished
int Sequence::insert(const ItemType& value)
{
    int pos = 0;

    //Case 1: Linked list is empty
    if (head == nullptr && m_size == 0) {
        pos = 0;
        this->insert(pos, value);
        return pos;
    }

    //Case 2: Linked list is not empty
    Node* temp = head;
    //Traverse through linked list
    for (int i = 0; i < size(); i++) {
        if (temp->value == value) {
            break;
        }
        pos++;
        temp = temp->next;
    }
    this->insert(pos, value);
    return pos;
 
}

//Finished
bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= size() || m_size == 0 || head == nullptr)
        return false;

    if (pos == 0 && head == nullptr) {
        return false;
    }
    
    //Erasing the node at position 0 if the size is 1
    if (pos == 0 && m_size == 1) {
        Node* temp = head;
        head = nullptr;
        delete temp;
        m_size--;
        return true;
    }

    //Erasing the node at position 0 if the size is greater than 0
    else if (pos == 0 && m_size > 0) {
        Node* temp = head;
        head = head->next;
        Node* last_node = temp->previous;
        last_node->next = head;
        head->previous = last_node;
        delete temp;
        m_size--;
        return true;
    }
    
    //Erasing the node at the end of the linked list
    else if (pos == (size() - 1) && m_size != 0) {
        Node* tail = head->previous;
        Node* before_tail = tail->previous;
        before_tail->next = head;
        head->previous = before_tail;
        delete tail;
        m_size--;
        return true;
    }
    
    //Erasing the node in the middle of the test
    Node* temp = head;

    //finding the previous pointer's position
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    Node* before_temp = temp->previous;
    Node* after_temp = temp->next;
    after_temp->previous = before_temp;
    before_temp->next = after_temp;
    delete temp;
    m_size--;
    return true;
}

//Finished
int Sequence::remove(const ItemType& value)
{
    if (find(value) == -1)
        return 0;

    int counter = 0;
    
    //Loop until all of the values are erased
    while (find(value) != -1) {
        erase(find(value));
        counter++;
    }

    return counter;
}

//Finished
bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= size())
        return false;
    Node* temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    value = temp->value;
    return true;
}

//Finished
bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= size())
        return false;
    Node* temp = head;

    //Loop through the sequence until value found
    for (int i = 0; i < pos; i++) {
        //Let temp point to the next value
        temp = temp->next;
    }

    temp->value = value;
    return true;
}

//Finished
int Sequence::find(const ItemType& value) const
{
    //Check if head is not a nullptr
    if (head == nullptr) {
        return -1;
    }

    Node* temp = head;
    for (int p = 0; p < size(); p++) {
        if (temp->value == value) {
            return p;
        }
        temp = temp->next;
    }

    return -1;
}


void Sequence::swap(Sequence& other)
{
    //Temporarily store the pointers of head to 
    Node* temp_head_this = head;

    //Swap the actual heads
    head = other.head;
    other.head = temp_head_this;

    //Swap the sizes;
    int temp_size = other.size();
    other.m_size = this->size();
    m_size = temp_size;
}

//Finished
void Sequence::uncheckedInsert(int pos, const ItemType& value)
{
    //Create a new node
    Node* newNode = new Node;


    //If the head pointer is pointing to a null pointer and is of size 0, execute (1). This means that the linked list is empty.
    //(1)
    if (m_size == 0 && head == nullptr) {
        //Assign First Node
        newNode->value = value;
        head = newNode;
        newNode->next = newNode;
        newNode->previous = newNode;
    }

    //If the position we are trying to insert in is equal to m_size, execute (2). This means that we are inserting at the end of the list.
    //(2)
    if (m_size == pos) {
        newNode->value = value;

        //Find the end of the list
        Node* tail = head->previous;

        //Change the pointers
        newNode->previous = tail;
        newNode->next = head;
        head->previous = newNode;
        tail->next = newNode;
        
    }
    //If the position we are trying to insert is in the middle of the linked list, execute (3)
    //(3)
    if (pos > 0 && pos < m_size) {
        newNode->value = value;

        Node* temp = head;

        //finding the previous pointer's position
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        
        //Swapping the pointers
        Node* previous_node = temp->previous;
        previous_node->next = newNode;
        newNode->previous = previous_node;
        temp->previous = newNode;
        newNode->next = temp;

    }
    //If we are trying to inert at the beginning of a linked list that is not empty, execute (4)
    //(4)
    if (pos == 0 && head != nullptr) {
        newNode->value = value;

        Node* temp = head;

        head = newNode;
        Node* last_node = temp->previous;
        last_node->next = newNode;
        temp->previous = newNode;
        newNode->next = temp;
        newNode->previous = last_node;
        
    }


    m_size++;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    
    //Returns the earliest place in seq1 where the subsequence starts

    if (seq1.size() >= seq2.size() || seq1.size() > 0 || seq2.size() > 0) {
        
        
        ItemType item1;
        ItemType item2;
        for (int i = 0; i < seq1.size(); i++) {
            
            //Ensure that the size of sequence 2 is bigger than size of sequence 1 to prevent undefined behavior
            if ((seq1.size() - seq2.size() - i) < 0) {
                break;
            }
            seq1.get(i, item1);
            seq2.get(0, item2);
            //Condition that must be true to run check: Item1 and Item2 are equal.
            //If item1 and item2 are equivalent, we run a check to see if the sequence is the same
            if (item1 == item2) {
                for (int k = 0; k < seq2.size(); k++) {
                    seq1.get(i + k, item1);
                    seq2.get(k, item2);
                    //If the test fails, then we break from the loop
                    if (item1 != item2) {
                        break;
                    }
                    //Otherwise, check the next item

                    //If the iteration gets to the end, we know that they are equal, therefore, we can return the value.
                    if (k == seq2.size() - 1) {
                        return i;
                    }
                }
            }
        }
    }
    

    //If no such k exists or if seq2 is empty, the function returns -1
     return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {

    //If seq1 and seq2 are empty, then when this function returns, result must be empty
    if (seq1.size() == 0 && seq2.size() == 0) {
        return;
    }

    //If seq1 is empty, then when this function returns, result must consist of the sequence seq2_n, ..., seq2_0, and no other items
    Sequence temp;
    ItemType item;
    if (seq1.size() == 0 && seq2.size() > 0) {
        for (int i = seq2.size()-1; i >= 0; i--) {
            seq2.get(i, item);
            temp.insert(seq2.size()-1-i, item);
        }
        
    }

    //If seq2 is empty, then when this function returns, result must consist of seq1_n, ..., seq1_0, and no other items
    else if (seq2.size() == 0 && seq1.size() > 0) {

        for (int i = seq1.size() - 1; i >= 0; i--) {
            seq1.get(i, item);
            temp.insert(seq1.size()- 1 - i, item);
        }
    }

    //Otherwise, concatenate Reverse the sequence
    else {
        for (int i = seq1.size() - 1; i >= 0; i--) {
            seq1.get(i, item);
            temp.insert(seq1.size() - 1 - i, item);
        }

        for (int i = seq2.size() - 1; i >= 0; i--) {
            seq2.get(i, item);
            temp.insert(seq1.size() + seq2.size() - 1 - i, item);
        }
    }
    
    result = temp; 
    
    
}