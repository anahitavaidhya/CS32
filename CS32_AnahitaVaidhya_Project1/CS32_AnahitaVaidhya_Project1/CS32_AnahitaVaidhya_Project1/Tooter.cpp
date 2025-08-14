//
//  Tooter.cpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//

#include <stdio.h>
#include "Tooter.h"
#include "City.h"
#include "globals.h"

///////////////////////////////////////////////////////////////////////////
//  Tooter implementation
///////////////////////////////////////////////////////////////////////////

Tooter::Tooter(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Tooter must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Tooter created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Tooter::row() const
{
    return m_row;
}

int Tooter::col() const
{
    // DONE TODO: TRIVIAL:  Return the column the Tooter is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

void Tooter::move()
{
      // Attempt to move in a random direction; if it can't move, don't move.
      // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
                                    //up= 0, down = 1, left = 2, right = 3
    int tempRow = m_row;
    int tempCol = m_col;
    
    //figure out if this is ok or the other way I had it
    if (m_city->determineNewPosition(m_row, m_col, dir) && m_city->isPlayerAt(m_row, m_col)){
        m_row = tempRow;
        m_col = tempCol;
    }
    
    // I think DONE TODO:  Move in the appropriate direction if allowed
}

