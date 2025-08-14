//
//  History.h
//  CS32_AnahitaVaidhya_Project1
//
//  Created by Anahita Vaidhya on 1/9/24.
//

#ifndef History_h
#define History_h

#include "globals.h"
#include <stdio.h>

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
        
    private:
        int m_Rows;
        int m_Cols;
        int m_Grid[MAXROWS][MAXCOLS];
};

#endif /* History_h */
