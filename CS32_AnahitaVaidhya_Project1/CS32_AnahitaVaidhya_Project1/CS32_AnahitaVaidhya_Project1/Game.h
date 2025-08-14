//
//  Game.hpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//

#ifndef Game_h
#define Game_h

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <stdio.h>
using namespace std;

//Do I need this?
class City;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nTooters);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};

#endif /* Game_h */
