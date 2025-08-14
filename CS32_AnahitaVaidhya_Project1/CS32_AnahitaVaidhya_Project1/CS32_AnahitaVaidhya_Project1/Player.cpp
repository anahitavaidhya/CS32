//
//  Player.cpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//
#include <stdio.h>
#include "Player.h"
#include "City.h"
#include "globals.h" //Do I need?

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 12;
      // DONE TODO: You might or might not put something here.
}

int Player::row() const
{
    // DONE TODO: TRIVIAL:  Return the row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const
{
    // DONE TODO: TRIVIAL:  Return the column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

int Player::age() const
{
    // DONE TODO: TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // This implementation compiles, but is incorrect.
}

int Player::health() const
{
    // DONE TODO: TRIVIAL:  Return the player's health status.
    // Delete the following line and replace it with the correct code.
    return m_health;  // This implementation compiles, but is incorrect.
}

  
//double check if this is correct
bool Player::isPassedOut() const
{
    // DONE TODO: TRIVIAL:  Return whether the player is passed out.
    // Delete the following line and replace it with the correct code.
    return (m_health <= 0);  // This implementation compiles, but is incorrect.
}

void Player::preach()
{
    m_age++;
    m_city->preachToTootersAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
    //Move one step up, down, left, or right to an empty position (i.e., one not occupied by a Tooter). If the player attempts to move into the wall of the city (e.g., down, when on the bottom row) or to a position occupied by a Tooter, the player does not move.
    
    int tempRow = m_row;
    int tempCol = m_col;
    
    if (m_city->determineNewPosition(m_row, m_col, dir) && m_city->nTootersAt(m_row, m_col) > 0){
        m_row = tempRow;
        m_col = tempCol;
    }
      // I think DONE TODO:  If there is a grid position in the indicated direction that is
      //        adjacent to the player and vacant, move the player there;
      //        otherwise, don't move.
}

//double check if this is correct
void Player::getGassed()
{
    // DONE TODO: TRIVIAL
    m_health--;
}

