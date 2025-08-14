//
//  Tooter.h
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/8/24.
//

#ifndef Tooter_h
#define Tooter_h

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <stdio.h>
using namespace std;

class City;

class Tooter
{
  public:
        // Constructor
    Tooter(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};


#endif /* Tooter_h */
