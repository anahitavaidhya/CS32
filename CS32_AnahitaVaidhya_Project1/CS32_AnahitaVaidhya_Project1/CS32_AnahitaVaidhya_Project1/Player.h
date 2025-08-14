//
//  Player.hpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//

#ifndef Player_h
#define Player_h

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <stdio.h>
using namespace std;

class City;
class Tooter;

//might have to do #include "Tooter.h"

class Player
{
  public:
        // Constructor
    Player(City *cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

        // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();

  private:
    City* m_city;
    Tooter* m_tooter;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health;
      // DONE TODO: You'll probably find that a player object needs an additional
      //       data member to support your implementation of the behavior
      //       affected by the player's being blasted with gas.
};

#endif /* Player_h */
