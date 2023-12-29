#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "globals.h"
using namespace std;

class Arena;

class History
{
public:
	//History Constructor
	History(int nRows, int nCols);
	//Member Functions
	bool record(int r, int c);
	void display() const;
private:
	int m_grid[MAXROWS][MAXCOLS];
	int m_rows;
	int m_cols;
};

#endif