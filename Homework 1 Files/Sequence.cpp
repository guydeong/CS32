#include "Sequence.h"

Sequence::Sequence(){
	//Create an empty sequence (i.e., one whose size() is 0)
	m_size = 0;
}


bool Sequence::empty() const {
	//If the sequence is empty, return true
	if (m_size == 0) {
		return true;
	}
	//Otherwise, return false
	return false;
}

//Accessor for m_size
int Sequence::size() const{
	//Return the number of items in the sequence
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
	//Insert value into the sequence so that it becomes the item at position pos

	//0 1 2 3 4 5 6 7 ...
	//M a r c
	
	//Sequence s
	//s.insert(2, "r")
	//0 1 2 3 4 5 6 7 ...
	//M a r r c
	//The original item at position pos and those that follow it end up at positions one greater than they were at before.
	//Return pos if 0 <= pos <= size() and the value could inserted
	if (0 <= pos && pos <= this->size()) {
		
		for (int i = this->size(); i > pos; i--) {
			//CAUTION: may produce undefined behavior. Check for edge cases
			m_arr[i] = m_arr[i - 1];
				
		}

		//If pos is equal to size(), the value is inserted at the end
		m_arr[pos] = value;
		m_size++;


		return pos;
	}
	//Otherwise, leave the sequence unchanged and return -1.
	return -1;
	
}

int Sequence::insert(const ItemType& value) {
	//Return -1 if the value was not inserted (perhaps because the sequence has a fixed capacity and is full).
	if (this->size() >= DEFAULT_MAX_ITEMS) {
		return -1;
	}
	//Let p be the smallest integer such that value <= the item at position p in the sequence
	int p = 0;
	for (int i = 0; i < this->size(); i++) {
		if(value <= m_arr[i]) {
			break;
		}
		p++;
	}

	//Insert value into the sequence so that it becomes the item in position p.
	for (int i = this->size(); i > p; i--) {
		//CAUTION: may produce undefined behavior. Check for edge cases
		m_arr[i] = m_arr[i - 1];

	}

	//If no such item exists (i.e., value > all items in the sequence), let p be size().
	m_arr[p] = value;
	m_size++;

	

	return p;
}

bool Sequence::erase(int pos) {
	//If 0<= pos < size(), remove the item pos from the sequence (so that all items that followed
	//that item end up at positions one lower than they were at before), and return true
	if (0 <= pos && pos < this->size()) {
		for (int i = pos; i < this->size()-1; i++) {
			m_arr[i] = m_arr[i + 1];
		}
		m_size--;
		return true;
	}

	//Otherwise, leave the sequence unchanged and return false
	return false;
}

int Sequence::remove(const ItemType& value) {
	//Test for edge cases: end of the sequence. What happens if the sequence hits the maximum number of indexes
	int index_position = this->size()-1;
	int counter = 0;
	//Erase all items from the sequence that == value.
	while (index_position != -1) {
		if (m_arr[index_position] == value) {
			this->erase(index_position);
			counter++;
		}
		index_position--;
	}
	//(which will be 0 if no item == value).
	if (counter == 0) {
		return 0;
	}
	//Return the number of items removed
	return counter;
	
}

//Accessor for values in the ItemType m_arr function
bool Sequence::get(int pos, ItemType& value) const{
	//If 0 <= pos < size(), copy into value the item in position pos of the sequence and return true
	//Changed equalities
	if (0 <= pos && pos < this->size()) {
		//Copy into value the item in position pos of the sequence
		value = m_arr[pos];
		return true;
	}

	//Otherwise, leave value unchanged and return false
	return false;
}

bool Sequence::set(int pos, const ItemType& value) {
	//If 0 <= pos < size(), replace the item at position pos in the sequence with value and return true
	if (0 <= pos && pos < this->size()) {
		//Replace the item at position pos in the sequence with value
		m_arr[pos] = value;
		return true;
	}
	
	//Otherwise, leave the sequence unchanged and return false
	return false;
}

int Sequence::find(const ItemType& value) const{
	int p = -1;

	//Let p be the smallest integer such that value == the item at position p in the sequence
	for (int i = 0; i < this->size(); i++) {
		if (value == m_arr[i]) {
			p = i;
			break;
		}
	}

	//If no such item exists, let p be -1
	//Return p.
	return p;
}

void Sequence::swap(Sequence& other) {
	//Exchange the context of this sequence with the other one
	//3 variables: this, other, swap (storage variable).
	//Array 1
	//0 1 2 3 4 5
	//M a r c

	//0 1 2 3 4 5 6 7 8 9 10
	//L u z u z u r i a g a

	int size_of_larger_array;

	if (this->size() > other.size()) {
		size_of_larger_array = this->size();
	}
	else {
		size_of_larger_array = other.size();
	}

	//Swap
	for (int i = 0; i < size_of_larger_array; i++) {
		ItemType temp = m_arr[i];
		m_arr[i] = other.m_arr[i];
		other.m_arr[i] = temp;
	}

	int temp_size = this->size();
	this->m_size = other.size();
	other.m_size = temp_size;
	


}
