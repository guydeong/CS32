//Arena.cpp

#include "Arena.h"
#include "globals.h"
#include "Rabbit.h"
#include "Player.h"


class Player;
class History;
class Rabbit;
//Arena Constructor
Arena::Arena(int nRows, int nCols):m_history(nRows, nCols) {
    //If nRows and nCols is not within bounds, exit the program
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    //Otherwise, set the following attributes of an arena:
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    //For every cell in the grid, set the cell status as Empty
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

//Destructor for the arena
Arena::~Arena()
{
    //For every rabbit in the m_rabbits array, delete them.
    for (int k = 0; k < m_nRabbits; k++)
        delete m_rabbits[k];
    //Delete m_player
    delete m_player;
}

//Accessor for number rows
int Arena::rows() const
{
    return m_rows;
}

//Accessor for number of columns
int Arena::cols() const
{
    return m_cols;
}

//Accessor for player
Player* Arena::player() const
{
    return m_player;
}

//Accessor for the number of rabbits
int Arena::rabbitCount() const
{
    return m_nRabbits;
}

History& Arena::history() {
    return m_history;
}

//Get the cell status of a particular point on the grid
int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r - 1][c - 1];
}


int Arena::numberOfRabbitsAt(int r, int c) const
{
    //Set counter equal to 0
    int count = 0;

    //Loop from 0 to the number of rabbits
    for (int k = 0; k < m_nRabbits; k++)
    {
        //Initialize rp as a pointer to the current rabbit's position we are checking
        Rabbit* rp = m_rabbits[k];
        //If rp.row() == row and rp.col() == c, then increment the counter by 1.
        if (rp->row() == r && rp->col() == c)
            count++;
    }
    //Return count
    return count;
}

void Arena::display(string msg) const
{
    //Initialize 2 variables:
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    //Loop through every row and every column within the display grid
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            //If getCellStatus is empty, place a dot. Otherwise, place a star
            displayGrid[r - 1][c - 1] = (getCellStatus(r, c) == EMPTY ? '.' : '*');

    // Indicate each rabbit's position
    for (int k = 0; k < m_nRabbits; k++)
    {
        //rp is a pointer to const Rabbit, which is assigned a value of the rabbit we are looking at.
        const Rabbit* rp = m_rabbits[k];
        //Converting the grid into array format
        //gridChar is a pointer to char, which equals to a certain point on the grid
        char& gridChar = displayGrid[rp->row() - 1][rp->col() - 1];
        //Switch to check the number of rabbits within a point at a grid
        switch (gridChar)
        {
        case '.':  gridChar = 'R'; break;
        case 'R':  gridChar = '2'; break;
        case '9':  break;
        default:   gridChar++; break;  // '2' through '8'
        }
    }

    // Indicate the player position
    if (m_player != nullptr)
        displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? 'X' : '@');

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;

    // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

    // Don't add a rabbit on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

    if (m_nRabbits == MAXRABBITS)
        return false;
    m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
    m_nRabbits++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
    // Move all rabbits
    for (int k = m_nRabbits - 1; k >= 0; k--)
    {
        Rabbit* rp = m_rabbits[k];
        rp->move();

        if (m_player != nullptr &&
            rp->row() == m_player->row() && rp->col() == m_player->col())
            m_player->setDead();

        if (rp->isDead())
        {
            delete rp;

            // The order of Rabbit pointers in the m_rabbits array is
            // irrelevant, so it's easiest to move the last pointer to
            // replace the one pointing to the now-deleted rabbit.  Since
            // we are traversing the array from last to first, we know this
            // last pointer does not point to a dead rabbit.

            m_rabbits[k] = m_rabbits[m_nRabbits - 1];
            m_nRabbits--;
        }
    }

    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
            << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

