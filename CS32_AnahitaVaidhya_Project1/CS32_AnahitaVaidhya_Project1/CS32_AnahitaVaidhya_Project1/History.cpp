//
//  History.cpp
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/9/24.
//

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <iostream>

#include "History.h"
#include "City.h"
//class City;
class Tooter;
using namespace std;

History::History(int nRows, int nCols) : m_Rows(nRows), m_Cols(nCols){
    for (int r = 0; r < m_Rows; r++)
        for (int c = 0; c < m_Cols; c++)
            m_Grid[r][c] = 0;
}

//The record function is to be called to notify the History object that a Tooter at row r, column c was preached to but not converted. The function returns false if row r, column c is not within the City; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the City (e.g., row 1, column 1 is the upper-left-most position).
bool History::record(int r, int c){
    if (r <= 0 || r > m_Rows || c <= 0 || c > m_Cols){
        return false;
    }
    m_Grid[r-1][c-1]++;
    return true;
}

//The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display (which should be done somewhere else in the program). (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
void History::display() const{
    clearScreen();
    for (int r = 0; r < m_Rows; r++){
        for (int c = 0; c < m_Cols; c++){
            char ch = '.';
            int n = m_Grid[r][c];
            if (n == 0){
                ch = '.';
            } else if (n > 26){
                ch = 'Z';
            } else if (n > 0){
                ch = ('A' + (n-1));
            }
            cout << ch;
        }
        cout << endl;
    }
    cout << endl;
}
