#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Side.h"
#include "Player.h"
using namespace std;

class Game {
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move(Side s);
	void play();
	int beans(Side s, int hole) const;
private:
	Board m_b;
	Player* m_south;
	Player* m_north;
};
#endif