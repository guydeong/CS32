//Game.h

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

class Arena;

class Game
{
    public:
        // Constructor/destructor
        Game(int rows, int cols, int nRabbits);
        ~Game();

        // Mutators
        void play();

    private:
        Arena* m_arena;

        // Helper functions
        string takePlayerTurn();
};

#endif