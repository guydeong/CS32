#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole) {
	//if nHoles is not positive, act as if it were 1
	if (nHoles <= 0) {
		mHoles = 1;
	}
	//Otherwise, set nHoles = mHoles
	else {
		mHoles = nHoles;
	}
	int mBeansPerHole = 0;
	
	//If nInitialBeansPerHole is negative, act as if it were 0.
	if (nInitialBeansPerHole < 0) {
		mBeansPerHole = 0;
	}
	else {
		mBeansPerHole = nInitialBeansPerHole;
	}

	//Note to self:
	//1) South's Pot is hole #0 in m_SouthSide
	//2) North's Pot is hole #0 in m_NorthSide

	//Storing North's pot
	m_NorthSide.push_back(0);
	//Storing South's pot
	m_SouthSide.push_back(0);

	for (int i = 1; i <= holes(); i++) {
		m_SouthSide.push_back(mBeansPerHole);
		m_NorthSide.push_back(mBeansPerHole);
	}

}

int Board::holes() const {
	return mHoles;
}

int Board::beans(Side s, int hole) const {

	if (hole > holes() || hole < 0 ) {
		return -1;
	}

	//North Side
	if (s == NORTH) {
		return m_NorthSide[hole];
	}

	//South Side
	else{
		return m_SouthSide[hole];
	}
}

int Board::beansInPlay(Side s) const {
	int total = 0;

	//South Side
	if (s == SOUTH) {
		for (int i = 1; i < m_SouthSide.size(); i++) {
			total += m_SouthSide[i];
		}
		
	}

	//North Side
	else {
		for (int i = 1; i < m_NorthSide.size(); i++) {
			total += m_NorthSide[i];
		}
		
	}
	
	return total;
}

int Board::totalBeans() const {
	int total = 0;

	//South Side
	for (int i = 0; i < m_SouthSide.size(); i++) {
		total += m_SouthSide[i];
	}

	//North Side
	for (int i = 0; i < m_NorthSide.size(); i++) {
		total += m_NorthSide[i];
	}

	return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	//If the hole indicated by (s, hole) is empty or invalid or a pot, this function returns false without changing anything
	if (beans(s, hole) <= 0 || hole == 0) {
		return false;
	}
	const Side player_s = s;

	Side curr_s = s;
	int curr_hole = hole;
	int rotations = beans(curr_s, curr_hole);
	//Set chosen south pot to 0
	if (player_s == SOUTH) {
		m_SouthSide[hole] = 0;
	}

	//Set chosen north pot to 0
	if (player_s == NORTH) {
		m_NorthSide[hole] = 0;
	}
	while (rotations > 0){
		//Incrementing holes depending on the side
		if (curr_hole == 0 && curr_s == NORTH && player_s == NORTH) {
			curr_hole = 0;
			curr_s = SOUTH;
		}
		if (curr_hole == 0 && curr_s == SOUTH && player_s == SOUTH) {
			curr_hole = mHoles+1;
			curr_s = NORTH;
		}
		//South
		if (curr_s == SOUTH) {
			curr_hole++;
		}
		//North
		if (curr_s == NORTH) {
			curr_hole--;
		}
		//Switching sides
		//Switching from south to north
		if (curr_hole == mHoles+1 && curr_s == SOUTH) {
			if (player_s == SOUTH) {
				curr_s = SOUTH;
				curr_hole = 0;
			}
			//Skip South's if north player
			else {
				curr_s = NORTH;
				curr_hole = mHoles;
			}
		}
		//Switching from north to south
		if (curr_hole == 0 && curr_s == NORTH) {
			if (player_s == NORTH) {
				curr_s = NORTH;
				curr_hole = 0;
			}
			//Skip North's pot if south player
			else {
				curr_s = SOUTH;
				curr_hole = 1;
			}
		}
		//Incremenet Current hole's beans
		increment(curr_s, curr_hole);
		rotations--;
	}
	endSide = curr_s;
	endHole = curr_hole;
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner) {
	//If input is valid, return false
	if (beans(s, hole) < 0 || hole == 0) {
		return false;
	}
	int bean_in_hole = 0;
	//Move to bean_in_hole variable and set hole to 0
	if (s == SOUTH) {
		bean_in_hole = m_SouthSide[hole];
		m_SouthSide[hole] = 0;
	}
	else {
		bean_in_hole = m_NorthSide[hole];
		m_NorthSide[hole] = 0;
	}

	//Set number of beans to corresponding hole
	if (potOwner == SOUTH) {
		m_SouthSide[0] += bean_in_hole;
	}
	else {
		m_NorthSide[0] += bean_in_hole;
	}
	return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
	//If inputs are invalid, return false
	if (hole > mHoles || hole < 0 || beans < 0) {
		return false;
	}
	//If side is SOUTH, set the value of that hole to the number of beans passed into the function.
	if (s == SOUTH) {
		m_SouthSide[hole] = beans;
	}
	//Otherwise, if side is NORTH, set the value of that hole to the number of beans passed into the function.
	else {
		m_NorthSide[hole] = beans;
	}
	return true;
}

//Helper function to increment by 1
void Board::increment(Side s, int hole) {
	//South Side
	if (s == SOUTH) {
		m_SouthSide[hole] = m_SouthSide[hole]+1;
	}
	//North Side
	if (s == NORTH) {
		m_NorthSide[hole] = m_NorthSide[hole]+1;
	}
}

//HELPER FUNCTION: COMMENT OUT ONCE FINISHED
//void Board::display() const {
//	int n_spaces = beans(NORTH, 0);
//	int s_spaces = beans(NORTH, 0);
//	do {
//		cout << " ";
//		n_spaces = n_spaces / 10;
//	} while (n_spaces > 0);
//
//	cout << "  ";
//	for (int i = 1; i <= holes(); i++) {
//		cout << beans(NORTH, i) << "  ";
//	}
//	cout << endl;
//
//	cout << beans(NORTH, 0);
//	for (int i = 1; i <= holes(); i++) {
//		cout << " " << "  ";
//	}
//
//	cout << "  ";
//	cout << beans(SOUTH, 0);
//	cout << endl;
//	do {
//		cout << " ";
//		s_spaces = s_spaces / 10;
//	} while (s_spaces > 0);
//
//	cout << "  ";
//	for (int i = 1; i <= holes(); i++) {
//		cout << beans(SOUTH, i) << "  ";
//	}
//	cout << endl;
//
//
//}