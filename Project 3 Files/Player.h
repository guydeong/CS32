#ifndef PLAYER_H
#define PLAYER_H
using namespace std;
#include <iostream>
#include "Board.h"
#include "Side.h"
#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}
	void start()
	{
		m_time = std::chrono::high_resolution_clock::now();
	}
	double elapsed() const
	{
		std::chrono::duration<double, std::milli> diff =
			std::chrono::high_resolution_clock::now() - m_time;
		return diff.count();
	}
private:
	std::chrono::high_resolution_clock::time_point m_time;
};

class JumpyTimer
{
public:
	JumpyTimer(int jumpInterval)
		: m_jumpInterval(jumpInterval), m_callsMade(0)
	{
		actualElapsed();
	}
	double elapsed()
	{
		m_callsMade++;
		if (m_callsMade == m_jumpInterval)
		{
			m_lastElapsed = m_timer.elapsed();
			m_callsMade = 0;
		}
		return m_lastElapsed;
	}
	double actualElapsed()
	{
		m_lastElapsed = m_timer.elapsed();
		return m_lastElapsed;
	}
private:
	Timer m_timer;
	int m_jumpInterval;
	int m_callsMade;
	int m_lastElapsed;
};
class Player {
public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();

private:
	string m_name;

};

class HumanPlayer :public Player {
public:
	HumanPlayer(string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer();
private:
	//Helper function
	bool valid_input(const Board& b, const Side s, const int input) const;
};

class BadPlayer:public Player {
public:
	BadPlayer(string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer();
private:
	//Helper function
	bool valid_input(const Board& b, const Side s, const int input) const;
};

class SmartPlayer : public Player {
public:
	SmartPlayer(string name);
	int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer();
private:
	int eval(const Board& b, Side s) const;
	bool valid_input(const Board& b, const Side s, const int input) const;
	void chooseMove_Helper(const Board& b, Side s_orig, Side opp_orig, Side s, int& depth, int& bestHole, int& value, double timeLimit, JumpyTimer& timer) const;
};



#endif