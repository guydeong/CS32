#include <queue>
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

    queue <Coord> coord_queue;
    //Pseudocode:

    Coord End_Coord = Coord(er, ec);


    //Note to self: 'E' means that the algorithm has encountered the coordinate
    //Current Coordinates:
    int r = sr;
    int c = sc;
    Coord start(r, c);
    //Push the starting coordinate (sr,sc) onto the coordinate queue
    coord_queue.push(start);
    //And update maze[sr][sc] to indicate that the algorithm has encountered it (i.e., set maze[sr][sc] to have a value other than '.').
    maze[sr][sc] = 'E';

    //While the queue is not empty,
    while (!coord_queue.empty()) {
        //Pop the top coordinate off the queue. This gives you the current (r,c) location that your algoritm is exploring.
        Coord current = coord_queue.front();
        Coord s(current.r() + 1, current.c());
        Coord e(current.r(), current.c() + 1);
        Coord n(current.r() - 1, current.c());
        Coord w(current.r(), current.c() - 1);
        /*cout << current.r() << "," << current.c() << endl;*/
        coord_queue.pop();
        //If the current (r,c) coordinate is equal to the ending coordinate,
        if (current.r() == End_Coord.r() && current.c() == End_Coord.c()) {
            //then we've solved the maze so return true;
            return true;
        }
        //Check each place you can move from the current cell as follows:
        //If you can move SOUTH and haven't encountered that cell yet, 
        if (maze[s.r()][s.c()] == '.' && maze[s.r()][s.c()] != 'E') {

            //Then push the coordinate (r+1,c) onto the queue and
            coord_queue.push(s);
            //Update maze[r+1][c] to indicate the algorithm has encountered it
            maze[s.r()][s.c()] = 'E';
        }
        //If you can move EAST and haven't encountered that cell yet,
        if (maze[e.r()][e.c()] == '.' && maze[e.r()][e.c()] != 'E') {

            //then push the coordinate (r, c+1) onto the queue and 
            coord_queue.push(e);
            //Update maze[r][c+1] to indicate the algorithm has encountered it.
            maze[e.r()][e.c()] = 'E';
        }

        //If you can move NORTH and haven't encountered that cell yet,
        if (maze[n.r()][n.c()] == '.' && maze[n.r()][n.c()] != 'E') {

            //Then push the coordinate (r-1,c) onto the queue and
            coord_queue.push(n);
            //maze[r-1][c] to indicate the algorithm has encountered it
            maze[n.r()][n.c()] = 'E';
        }

        //If you can move WEST and haven't encountered that cell yet,
        if (maze[w.r()][w.c()] == '.' && maze[w.r()][w.c()] != 'E') {
            //Then push the coordinate (r+1,c) onto the queue and
            coord_queue.push(w);
            //maze[r][c-1] to indicate the algorithm has encountered it
            maze[w.r()][w.c()] = 'E';
        }

    }
    //There was no solution, so return false
    return false;
}

int main() {

    
}