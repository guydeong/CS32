// rabbit.cpp
#include "globals.h"
#include "Rabbit.h"
#include "Arena.h"

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = INITIAL_RABBIT_HEALTH;
    m_idleTurnsRemaining = 0;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
    return m_col;
}

bool Rabbit::isDead() const
{
    return m_health == 0;
}

void Rabbit::move()
{
    if (m_idleTurnsRemaining > 0)
    {
        m_idleTurnsRemaining--;
        return;
    }

    m_direction = randInt(0, NUMDIRS - 1);

    // Attempt to move in a random direction; if can't move, we don't move
    if (attemptMove(*m_arena, m_direction, m_row, m_col))
    {
        if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        {
            m_arena->setCellStatus(m_row, m_col, EMPTY);
            m_health--;
        }
    }

    //Check here
    if (m_health < INITIAL_RABBIT_HEALTH) {
        //Call the record function when the rabbit's health is less than the initial health
        m_arena->history().record(m_row, m_col);
        m_idleTurnsRemaining = POISONED_IDLE_TIME;
    }
       
}

