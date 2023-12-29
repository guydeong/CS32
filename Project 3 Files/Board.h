#ifndef BOARD_H
#define BOARD_H
#include "Side.h"
#include <vector>
#include <iostream>
using namespace std;

class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);
	//Construct a Board with the indicated number of holes per side (not counting the pot)
	//and initial number of beans per hole. If nHoles is not positive, act as if it were 1;
	//if initialBeansPerHole is negative, act as if it were 0.
	int holes() const;
	int beans(Side s, int hole) const;
	int beansInPlay(Side s) const;
	int totalBeans() const;
	bool sow(Side s, int hole, Side& endSide, int& endHole);
	bool moveToPot(Side s, int hole, Side potOwner);

	//Should not be used directly or indirectly
	bool setBeans(Side s, int hole, int beans);
	
	
	////HELPER FUNCTION: COMMENT OUT ONCE FINISHED
	//void display() const;
private:
	//Number of holes per side
	int mHoles;
	
	vector <int> m_SouthSide;
	vector <int> m_NorthSide;

	//Helper functions
	void increment(Side s, int hole);
	

};
#endif