#include "Player.h"

Player::Player(std::string name):m_name(name){}

string Player::name() const {
	return m_name;
}

//Virtual function: may be overridden
bool Player::isInteractive() const {
	return false;
}

Player::~Player() {}


//HumanPlayer Member Functions
HumanPlayer::HumanPlayer(string name) :Player(name) {}

HumanPlayer::~HumanPlayer() {}

bool HumanPlayer::valid_input(const Board& b, const Side s, const int input) const {
	//check for valid input
	if (input <= b.holes() && input > 0 && b.beans(s, input) > 0) {
		return true;
	}
	return false;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const {
	int input = -1;
	while (!valid_input(b, s, input)) {
		cout << "Select a hole, " << this->name() << ": ";
		cin >> input;
		if (input > b.holes() || input <= 0) {
			cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
		}
		else if (b.beans(s, input) <= 0) {
			cout << "There are no beans in that hole." << endl;
		}
	}

	return input;
}

bool HumanPlayer::isInteractive() const {
	return true;
}

//BadPlayer Member Functions
BadPlayer::BadPlayer(string name) :Player(name) {}

BadPlayer::~BadPlayer() {}

bool BadPlayer::valid_input(const Board& b, const Side s, const int input) const {
	//check for valid input
	if (input > b.holes() || input <= 0 || b.beans(s, input) <= 0) {
		return false;
	}
	return true;
}

int BadPlayer::chooseMove(const Board& b, Side s) const {
	if (b.beansInPlay(s) <= 0)
		return -1;
	int i = 1;
	while (!valid_input(b, s, i) && i <= b.holes()) {
		i++;
	}
	cout << this->name() << " chooses hole " << i << endl;
	return i;
}

bool SmartPlayer::valid_input(const Board& b, const Side s, const int input) const {
	//check for valid input
	if (input > b.holes() || input <= 0 || b.beans(s, input) <= 0) {
		return false;
	}
	return true;
}

SmartPlayer::SmartPlayer(string name) : Player(name) {}

SmartPlayer::~SmartPlayer() {}




int SmartPlayer::chooseMove(const Board& b, Side s) const{
	if (b.beansInPlay(s) <= 0)
		return -1;
	int val = 0;
	int besthole = -3;
	int depth = 0;
	double timeLimit = 4990;
	JumpyTimer timer(1000);
	//const Board& b, Side s_orig, Side opp_orig, Side s, int& depth, int& bestHole, int& value, double timeLimit, Timer& timer
	chooseMove_Helper(b, s, opponent(s), s, depth, besthole, val, timeLimit, timer);
	cout << this->name() << " chooses hole " << besthole << endl;
	return besthole;
}

//const Board& b, Side s_orig, Side s, int& depth, int& bestHole, int& value
//Reminder to self: Use pass by reference if you want to change the parameters during recursion
void SmartPlayer::chooseMove_Helper(const Board& b, Side s_orig, Side opp_orig, Side s, int& depth, int& bestHole, int& value, double timeLimit, JumpyTimer& timer) const {
	//CURRENT VALUE FOR CURRENT BOARD
	int curr_value = eval(b, s_orig);

	//1) if no move for player exists (i.e., game is over),
	if (b.beansInPlay(s) <= 0) {
		Board t_board = Board(b);
		bestHole = -1;
		//Move the beans to determine winner
		if (s == SOUTH) {
			for (int i = 1; i <= t_board.holes(); i++) {
				t_board.moveToPot(NORTH, i, NORTH);
			}
		}
		else {
			for (int i = 1; i <= t_board.holes(); i++) {
				t_board.moveToPot(SOUTH, i, SOUTH);
			}
		}
		value = curr_value;
		return;
	}
	//2) if the criterion says we should not search below this node
	else if (depth > 4 || timeLimit <= 0) {
		bestHole = -1;
		value = eval(b,s_orig);
		return;
	}

	//Stores valid-holes to check
	int k = 1;
	vector<int> valid_holes;
	while (k <= b.holes()) {
		if (valid_input(b, s, k)) {
			valid_holes.push_back(k);
		}
		k++;
	}
	//3) for every hole h the player can choose, "make" the move h
	for (int i = 0; i < valid_holes.size(); i++) {
		//"Make" the move h
		//Initialize to prevent garbages
		double thisBranchTimeLimit = timeLimit / (valid_holes.size()-i);
		double startTime = timer.elapsed();
		Board t_board = Board(b);
		Side end_s;
		int end_hole = -1;
		int t_value = 0;
		int t_bestHole = -3;

		//Sow the board
		t_board.sow(s, valid_holes[i], end_s, end_hole);

		//Performing the capture
		if (s == end_s && end_hole > 0) {
			if (s == SOUTH && t_board.beans(NORTH, end_hole) != 0 && t_board.beans(SOUTH, end_hole) == 1 && end_hole != 0) {
				//Perform the capture
				t_board.moveToPot(SOUTH, end_hole, s);
				t_board.moveToPot(NORTH, end_hole, s);
			}
			else if (s == NORTH && t_board.beans(SOUTH, end_hole) != 0 && t_board.beans(NORTH, end_hole) == 1 && end_hole != 0) {
				//Perform the capture
				t_board.moveToPot(NORTH, end_hole, s);
				t_board.moveToPot(SOUTH, end_hole, s);
			}
		}
		//Landed in Own Pot -> Go again
		if (s == end_s && end_hole == 0) {
			int t_depth = depth; //Same depth
			//Recursive Call 1: Go Again
			chooseMove_Helper(t_board, s_orig, opp_orig, s, t_depth, t_bestHole, t_value, thisBranchTimeLimit, timer);
		}
		//Otherwise, switch sides
		else {
			Side t_opponent;
			if (s == SOUTH) {
				t_opponent = NORTH;
			}
			else {
				t_opponent = SOUTH;
			}
			//Switch Sides: Increment depth by 1
			int t_depth = depth + 1;
			chooseMove_Helper(t_board, s_orig, opp_orig, t_opponent, t_depth, t_bestHole, t_value, thisBranchTimeLimit, timer);
		}

		if (bestHole == -3) { //Initializaiton case
			bestHole = valid_holes[i];
			value = t_value;
		}
		//Maximizer: Original Player
		if (s_orig == s && t_value > value) {
			bestHole = valid_holes[i];
			value = t_value;
		}
		//Minimizer: Opponent Player
		else if (s_orig != s && t_value < value) {
			bestHole = valid_holes[i];
			value = t_value;
		}
		timeLimit -= (timer.elapsed() - startTime);
		if (timeLimit <= 0)
			timeLimit = 0;
	}
	return;
}

//void printVector(vector<int> v) {
//	for (int i = 0; i < v.size(); i++) {
//		cout << v[i] << ", ";
//	}
//	cout << endl << endl;
//}

int SmartPlayer::eval(const Board& b, Side s) const{
	//Note:
	//Maximizer: Current Player
	//Minimizer: Opponent

	//Game is over
	if (b.beansInPlay(s) <= 0 || b.beansInPlay(opponent(s)) <= 0) {
		if (b.beans(s, 0) + b.beansInPlay(s) > b.beans(opponent(s), 0) + b.beansInPlay(opponent(s))) {
			//Current Side Wins
			return 10000;
		}
		else if (b.beans(s, 0) + b.beansInPlay(s) < b.beans(opponent(s), 0) + b.beansInPlay(opponent(s))) {
			//Opposing Side Wins
			return -10000;
		}
		else {
			//Tie
			return 0;
		}
	}
	//If Game is not over, return the difference between beans from the current and opposing pot
	int difference = b.beans(s, 0) - b.beans(opponent(s), 0);
	return difference;
}