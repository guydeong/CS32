//Notes:
//
//Parameters
//1) 2-dimensional 10x10 character array of Xs and dots that represent the maze. Each 'X' represents a wall, and each '.' represents a walkway
//2) The starting coordinates in the maze: sr, sc; the row number and column number range from 0 to 9.
//3) The ending coordinates in the maze: er, ec; the row number and
//4) The function must return true if in the maze as it was when the function was called, there is a path from maze[sr]
//[sc] to maze[er][ec] that includes only walkways, no walls; otherwise it must return false. The path may turn
//south, east, north, and west, but not diagonally. When the function returns, it is allowable for the maze to have been
//modified by the function.
//
//Simplfying assumptions:
//1) The maze has 10 rows
//2) The maze contains only Xs and dots when passed in to the function
//3) The top and bottom rows of the maze contain only Xs, as do the left and right columns
//4) sr, sc, er, and ec are between 0 and 9
//5) maze[sr][sc] and maze[er][ec] and '.' (i.e., not walls)

#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

class Coord
{
public:
    //Copy Constructor:
    //Values passed in:
    //1) Horizontal coordinate
    //2)Vertical Coordinate
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	// Return true if there is a path from (sr,sc) to (er,ec) through the maze;

    stack <Coord> coord_stack;
    //Pseudocode:
    
    Coord End_Coord = Coord(er, ec);


    //Note to self: 'E' means that the algorithm has encountered the coordinate
    //Current Coordinates:
    int r = sr;
    int c = sc;
    Coord start(r, c);
    //Push the starting coordinate (sr,sc) onto the coordinate stack
    coord_stack.push(start);
    //And update maze[sr][sc] to indicate that the algorithm has encountered it (i.e., set maze[sr][sc] to have a value other than '.').
    maze[sr][sc] = 'E';

    //While the stack is not empty,
    while (!coord_stack.empty()) {
        //Pop the top coordinate off the stack. This gives you the current (r,c) location that your algoritm is exploring.
        Coord current = coord_stack.top();
        Coord s(current.r() + 1, current.c());
        Coord e(current.r(), current.c() + 1);
        Coord n(current.r() - 1, current.c());
        Coord w(current.r(), current.c() - 1);
        coord_stack.pop();
        //If the current (r,c) coordinate is equal to the ending coordinate,
        if (current.r() == End_Coord.r() && current.c() == End_Coord.c()) {
            //then we've solved the maze so return true;
            return true;
        }
        //Check each place you can move from the current cell as follows:
        //If you can move SOUTH and haven't encountered that cell yet, 
        if (maze[s.r()][s.c()] == '.' && maze[s.r()][s.c()] != 'E') {
            
            //Then push the coordinate (r+1,c) onto the stack and
            coord_stack.push(s);
            //Update maze[r+1][c] to indicate the algorithm has encountered it
            maze[s.r()][s.c()] = 'E';
        }
        //If you can move EAST and haven't encountered that cell yet,
        if (maze[e.r()][e.c()] == '.' && maze[e.r()][e.c()] != 'E') {
            
            //then push the coordinate (r, c+1) onto the stack and 
            coord_stack.push(e);
            //Update maze[r][c+1] to indicate the algorithm has encountered it.
            maze[e.r()][e.c()] = 'E';
        }

        //If you can move NORTH and haven't encountered that cell yet,
        if (maze[n.r()][n.c()] == '.' && maze[n.r()][n.c()] != 'E') {
            
            //Then push the coordinate (r-1,c) onto the stack and
            coord_stack.push(n);
            //maze[r-1][c] to indicate the algorithm has encountered it
            maze[n.r()][n.c()] = 'E';
        }

        //If you can move WEST and haven't encountered that cell yet,
        if (maze[w.r()][w.c()] == '.' && maze[w.r()][w.c()] != 'E') {
            //Then push the coordinate (r+1,c) onto the stack and
            coord_stack.push(w);
            //maze[r][c-1] to indicate the algorithm has encountered it
            maze[w.r()][w.c()] = 'E';
        }
        
    }
    //There was no solution, so return false
    return false;
}

int main() {
    
}
