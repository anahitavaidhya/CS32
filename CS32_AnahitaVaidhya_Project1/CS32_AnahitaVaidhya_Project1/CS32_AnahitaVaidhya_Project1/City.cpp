//
//  City.cpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//

#include "City.h"
#include "Player.h"
#include "Tooter.h"
#include "globals.h"
#include "History.h"

class Player;

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols) :  m_rows(nRows), m_cols(nCols), m_player(nullptr), m_nTooters(0), m_history(nRows, nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
}

//double check if this is correct
//where thread 1 test case comes from
//last test case maybe
City::~City()
{
    // DONE TODO:  Delete the player and all remaining dynamically allocated Tooters.
    for(int i = 0; i < m_nTooters; i++){
        delete m_tooters[i];
    }
    delete m_player;
}

int City::rows() const
{
    // DONE TODO: TRIVIAL:  Return the number of rows in the city.
    // Delete the following line and replace it with the correct code.
    return m_rows;  // This implementation compiles, but is incorrect.
}

int City::cols() const
{
    // DONE TODO: TRIVIAL:  Return the number of columns in the city.
    // Delete the following line and replace it with the correct code.
    return m_cols;  // This implementation compiles, but is incorrect.
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    // DONE TODO:  Return true if the player is at row r, column c, otherwise false.
    // Delete the following line and replace it with the correct code.
    if(m_player->row() == r && m_player->col() == c){
        return true;
    } else {
        return false;
    }// This implementation compiles, but is incorrect.
}

int City::tooterCount() const
{
    return m_nTooters;
}

int City::nTootersAt(int r, int c) const
{
    // I think DONE TODO:  Return the number of Tooters at row r, column c.
    // Delete the following line and replace it with the correct code.
    int count = 0;
    for(int i = 0; i < m_nTooters; i++){
        if(m_tooters[i]->row() == r && m_tooters[i]->col() == c){
            count++;
        }
    }
    return count;  // This implementation compiles, but is incorrect.
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
      // I think DONE TODO:  If a move from row r, column c, one step in direction dir
      //        would go off the edge of the city, leave r and c unchanged and
      //        return false.  Otherwise, set r or c so that row r, column c,
      //        is now the new position resulting from the proposed move, and
      //        return true.
    
    //use the isInBounds
    switch (dir)
    {
      case UP:
            // I think DONE TODO:  Implement the behavior if dir is UP.
            if(isInBounds((r-1), c)){
                r -= 1;
                break;
            } else {
                return false;
            }
      case DOWN:
            if(isInBounds((r+1), c)){
                r += 1;
                break;
            } else {
                return false;
            }
      case LEFT:
            if(isInBounds(r, (c-1))){
                c -= 1;
                break;
            } else {
                return false;
            }
      case RIGHT:
        // I think DONE TODO:  Implement the other directions.
            if(isInBounds(r, (c+1))){
                c += 1;
                break;
            } else {
                return false;
            }
      default:
        return false;
    }
    return true;
}

void City::display() const
{
      // Position (row,col) in the city coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each Tooter's position
    // I think DONE TODO:  If one Tooter is at some grid point, set the char to 'T'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    
    for(int i = 0; i < m_nTooters; i++){
        r = m_tooters[i]->row() - 1;
        c = m_tooters[i]->col() - 1;
        if(grid[r][c] == '.'){
            grid[r][c] = 'T';
        } else if(grid[r][c] == 'T'){
            grid[r][c] = '2';
        } else if(grid[r][c] <= '8'){
            grid[r][c] = grid[r][c] + 1;
        }
    }
    
        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a Tooter there
          // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, Tooter, and player info
    cout << "There are " << m_nTooters << " unconverted Tooters remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addTooter(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a Tooter on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
      // If there are MAXTOOTERS unconverted Tooters, return false. (don't need to add anymore)
    if(m_nTooters == 125){
        return false;
    }
      // Otherwise, dynamically allocate a new Tooter at coordinates (r,c).
      // Save the pointer to the newly allocated Tooter and return true.
    
    m_tooters[m_nTooters] = new Tooter(this, r, c);
    m_nTooters++;

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXTOOTERS
      // Tooters are added, then some are converted and removed from the city,
      // then more are added.
        // delete m_tooters[];

      // TODO:  Implement this.
    return true;  // This implementation compiles, but is incorrect.
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a Tooter
    if (nTootersAt(r, c) > 0)
        return false;

      // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToTootersAroundPlayer()
{
    for(int i = 0; i < m_nTooters; i++){
        if((m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()) || (m_tooters[i]->row() == m_player->row() && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row() && m_tooters[i]->col() == m_player->col()+1) || (m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row()-1 && m_tooters[i]->col() == m_player->col()+1) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()-1) || (m_tooters[i]->row() == m_player->row()+1 && m_tooters[i]->col() == m_player->col()+1)){
            
            if((randInt(0, 2) < 2)){
                delete m_tooters[i];
                for(int j = i; j < m_nTooters-1; j++){
                    m_tooters[j] = m_tooters[j+1];
                }
                m_nTooters--;
                i--;
            } else {
                m_history.record(m_tooters[i]->row(), m_tooters[i]->col());
            }
        }
    }
      // i think DONE TODO:  Implement this.
}

void City::moveTooters()
{
    for (int k = 0; k < m_nTooters; k++)
    {
        m_tooters[k]->move();
        if(isPlayerAt(m_tooters[k]->row()-1, m_tooters[k]->col()) || isPlayerAt(m_tooters[k]->row()+1, m_tooters[k]->col()) || isPlayerAt(m_tooters[k]->row(), m_tooters[k]->col()-1) || isPlayerAt(m_tooters[k]->row(), m_tooters[k]->col()+1)){
            
            m_player->getGassed();
        }
      // TODO:  Have the k-th Tooter in the city make one move.
      //        If that move results in that Tooter being orthogonally
     //        adjacent to the player, the player suffers a gas blast.
        
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

History& City::history(){
    return m_history;
}




