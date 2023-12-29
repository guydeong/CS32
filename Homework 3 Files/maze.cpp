bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	//If the start location is equal to the ending location, then we've solved the maze, so return true.
	if (sr == er && sc == ec) {
		return true;
	}
	//Visited = 'V'
	//Mark the start location as visited.
	maze[sr][sc] = 'V';
	//For each of the four directions,
	//South
	if (maze[sr + 1][sc] != 'V' && maze[sr + 1][sc] != 'X') {
		if (pathExists(maze, sr + 1, sc, er, ec)) {
			return true;
		};
	}
	//East
	if (maze[sr][sc + 1] != 'V' && maze[sr][sc + 1] != 'X') {
		if (pathExists(maze, sr, sc + 1, er, ec)) {
			return true;
		};
	}
	//North
	if (maze[sr-1][sc] != 'V' && maze[sr-1][sc] != 'X') {
		if (pathExists(maze, sr - 1, sc, er, ec)) {
			return true;
		};
	}
	//West
	if (maze[sr][sc-1] != 'V' && maze[sr][sc-1] != 'X') {
		if (pathExists(maze, sr, sc - 1, er, ec)) {
			return true;
		};
	}
	return false;
		//If the location one step in that direction (from the start location) has no wall and is unvisited, then call pathExisats starting from that location
		//ending at the same ending location as in the current call).
			//If that returned true,
				//then return true
	//Return false
}


