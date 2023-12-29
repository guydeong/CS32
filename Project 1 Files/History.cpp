//History.cpp
#include "History.h"

//Constructor for History
History::History(int nRows, int nCols) {

    //Assign the rows and columns to the constructor's rows and columns
    m_rows = nRows;
    m_cols = nCols;

    //Create the arena
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            //0 will be referenced later as a condition to display '.'
            m_grid[r][c] = 0;
        }
    }

}

//Record function
bool History::record(int r, int c) {
    r = r - 1;
    c = c - 1;

    //Check if row r, column c is not within the bounds specified
    if (r <= m_rows && c <= m_cols && r >= 0 && c >= 0) {
        //If the value corresponding to the position of m_grid[r][c] is not 'Z', then increment m_grid by 1.
        if (m_grid[r][c] != 'Z') {
            m_grid[r][c]++;
        }
        return true;
    }

    return false;
}

void History::display() const {

    //Declare 3 variables: displayGrid, r, and c
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) or the corresponding character 
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++) {
            //If the value of the element is greater than 1, set the display grid to the corresponding ascii value.
            if (m_grid[r][c] >= 1) {
                displayGrid[r][c] = 'A' + m_grid[r][c] - 1;
            }
            //Otherwise, place a dot.
            else {
                displayGrid[r][c] = '.';
            }
        }

    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++) {
        for (c = 0; c < m_cols; c++) {
            cout << displayGrid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}