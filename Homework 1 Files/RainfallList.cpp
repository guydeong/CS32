#include "RainfallList.h"

RainfallList::RainfallList():m_arr() {
	// Create an empty rainfall list.
}

bool RainfallList::add(unsigned long rainfall) {
	// If the rainfall is valid (a value from 0 to 400) and the rainfall list has room for it, add it to the rainfall list and return true.
	//Double check this if statement
	if (rainfall >= 0 && rainfall <= 400 && m_arr.insert(m_arr.size(), rainfall) != 1) {
		return true;
	}

	return false;
}


bool RainfallList::remove(unsigned long rainfall) {
	//Remove one instance of the specified rainfall from the rainfall list.
	int x = m_arr.find(rainfall);
	if (x != -1) {
		//Return true if a rainfall was removed;
		m_arr.erase(x);
		return true;
	}
		

	//Otherwise, false
	return false;
}

int RainfallList::size() const {
	return m_arr.size();
}


unsigned long RainfallList::minimum() const {
	//If the list is empty, return NO_RAINFALLS.
	if (m_arr.size() == 0) {
		return NO_RAINFALLS;
	}
	ItemType min;
	m_arr.get(0, min);
	ItemType temp;

	// Return the lowest-valued rainfall in the rainfall list.
	for (int i = 0; i < m_arr.size(); i++) {
		m_arr.get(i, temp);

		if (temp < min) {
			min = temp;
		}
	}
	return min;
}

unsigned long RainfallList::maximum() const {
	//If the list is empty, return NO_RAINFALLS.
	if (m_arr.empty()) {
		return NO_RAINFALLS;
	}
	ItemType max;
	m_arr.get(0, max);
	ItemType temp;

	// Return the lowest-valued rainfall in the rainfall list.
	for (int i = 0; i < m_arr.size(); i++) {
		m_arr.get(i, temp);

		if (temp > max) {
			max = temp;
		}
	}
	return max;
}