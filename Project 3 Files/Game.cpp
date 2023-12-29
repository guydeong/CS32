#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north) :m_b(b), m_south(south), m_north(north) {}

void Game::display() const {
	int n_spaces = beans(NORTH, 0);
	int s_spaces = beans(NORTH, 0);
	cout << "      " << m_north->name() << endl;
	//Count the number of spaces needed between pot and hole
	do {
		cout << " ";
		n_spaces = n_spaces / 10;
	} while (n_spaces > 0);
	cout << "  ";
	for (int i = 1; i <= m_b.holes(); i++) {
		cout << beans(NORTH, i) << "  ";
	}
	cout << endl;

	cout << beans(NORTH, 0);
	for (int i = 1; i <= m_b.holes(); i++) {
		cout << " " << "  ";
	}

	cout << "  ";
	cout << beans(SOUTH, 0);
	cout << endl;
	do {
		cout << " ";
		s_spaces = s_spaces / 10;
	} while (s_spaces > 0);
	
	cout << "  ";
	for (int i = 1; i <= m_b.holes(); i++) {
		cout << beans(SOUTH, i) << "  ";
	}
	cout << endl;
	cout << "      " << m_south->name();
	cout << endl;
	

	
}


bool Game::move(Side s) {
	
	//If beansInPlay is greater than 0
	if (m_b.beansInPlay(s) > 0) {
		const Side Player_s = s;
		Side curr_s = s;
		int move;
		Side endS;
		int endH;
		//While the endHole isn't the player's pot
		do {
			//Store move
			if (s == SOUTH) {
				move = m_south->chooseMove(m_b, s);
			}
			else {
				move = m_north->chooseMove(m_b, s);
			}
			m_b.sow(curr_s, move, endS, endH);
			//Performing the capture
			if (s == endS && endH > 0) {
				if (s == SOUTH && m_b.beans(NORTH, endH) != 0 && m_b.beans(SOUTH, endH) == 1 && endH != 0) {
					//Perform the capture
					m_b.moveToPot(SOUTH, endH, s);
					m_b.moveToPot(NORTH, endH, s);
				}
				else if (s == NORTH && m_b.beans(SOUTH, endH) != 0 && m_b.beans(NORTH, endH) == 1 && endH != 0) {
					//Perform the capture
					m_b.moveToPot(NORTH, endH, s);
					m_b.moveToPot(SOUTH, endH, s);
				}
			}
			
			//If endH is greater than 0, break.
			if (endH > 0 || m_b.beansInPlay(s) == 0) {
				break;
			}
			//Otherwise, Get another turn if endH is 0
			else {
				if (s == SOUTH) {
					cout << m_south->name() << " may get an additional turn" << endl;
					this->display();
				}
				else {
					cout << m_north->name() << " may get an additional turn" << endl;
					this->display();
				}
				
			}
		} while (1);
		
		//If game is over
		if (m_b.beansInPlay(s) == 0) {
			if (s == SOUTH) {
				//Move the remaining beans to North's pot
				for (int i = 1; i <= m_b.holes(); i++) {
					m_b.moveToPot(NORTH, i, NORTH);
				}
				cout << m_south->name() << " has no beans left to sow." << endl;
				cout << "Sweeping remaining beans into " << m_north->name() << "'s pot" << endl;
			}
			else {
				//Move the remaining beans to South's pot
				for (int i = 1; i <= m_b.holes(); i++) {
					m_b.moveToPot(SOUTH, i, SOUTH);
				}
				cout << m_north->name() << " has no beans left to sow." << endl;
				cout << "Sweeping remaining beans into " << m_south->name() << "'s pot" << endl;
			}
			return false;
		}
		return true;
	}
	else {
		
		if (s == SOUTH) {
			for (int i = 1; i <= m_b.holes(); i++) {
				m_b.moveToPot(NORTH, i, NORTH);
			}

		}
		else {
			for (int i = 1; i <= m_b.holes(); i++) {
				m_b.moveToPot(SOUTH, i, SOUTH);
			}
		}
		return false;
	}
	
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	//Game is over
	if (m_b.beansInPlay(SOUTH) <= 0 || m_b.beansInPlay(NORTH) <= 0) {
		if (beans(SOUTH, 0) + m_b.beansInPlay(SOUTH) == beans(NORTH, 0) + m_b.beansInPlay(NORTH)) {
			hasWinner = false;
		}
		else if (beans(SOUTH, 0) + m_b.beansInPlay(SOUTH) > beans(NORTH, 0) + m_b.beansInPlay(NORTH)) {
			hasWinner = true;
			winner = SOUTH;
		}
		else {
			hasWinner = true;
			winner = NORTH;
		}
		over = true;
	}
	//Otherwise, Game is not over
	else {
		over = false;
	}
}

int Game::beans(Side s, int hole) const {
	if (hole > m_b.holes() || hole < 0) {
		return -1;
	}
	return m_b.beans(s, hole);
}

void Game::play() {
	bool n_over = false;
	bool n_hasWinner;
	Side n_winner;

	Side turn = SOUTH;
	//If both player's are not interactive, execute the following
	if (m_south->isInteractive() == false && m_north->isInteractive() == false) {
		//While the game is not ever
		display();
		while (!n_over) {
			cout << "Press ENTER to continue: ";
			if (cin.get() == '\n') {
				
				status(n_over, n_hasWinner, n_winner);
				move(turn);
				display();
				
				//Rotating turns
				if (turn == SOUTH) {
					turn = NORTH;
				}
				else {
					turn = SOUTH;
				}

			}
			else {
				cout << endl;
				cout << "Game canceled" << endl;
				break;
			}
		}
		
	}
	else {
		while (!n_over) {
			display();
			status(n_over, n_hasWinner, n_winner);
			move(turn);
			
			//Rotating turns
			if (turn == SOUTH) {
				turn = NORTH;
			}
			else {
				turn = SOUTH;
			}
		}
		
	}
	//Game is over and has a winner
	if (n_over == true && n_hasWinner == true) {
		if (n_winner == 1) {
			cout << "The winner of the game is " << m_south->name() << " (South)" << "!" << endl;
		}
		else {
			cout << "The winner of the game is " << m_north->name() << " (North)" << "!" << endl;
		}
		
	}
	//Game is over and is a tie
	else if (n_over == true && n_hasWinner == false) {
		cout << "The game is a tie!" << endl;
	}
		
	display();
}