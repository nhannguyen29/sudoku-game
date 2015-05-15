/**************************************
 *      Programmer: Nhan Nguyen
 *      Program: Grid.h
 *      Purpose: The header file for the
 *                  Grid class
 *      Date: 04/30/2015
 *************************************/

#ifndef _GRID_H_
#define _GRID_H_

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Grid
{
    public:
    //Constructor
    Grid(); // default constructor
    Grid(vector< vector<int> > grid); // alternate constructor
    Grid(const Grid & G); // copy constructor

    //Destructor
    ~Grid();

    //Inspector
    vector< vector<int> > getGrid() const;
    vector<int> getRow(int row) const;
    int getValueInColumn(int row, int column) const;

    //Mutator
    void setGrid(vector< vector<int> > grid);
    void setRow(vector<int> new_row);
    //Facilitator
    void output(ostream & out = cout);
    void display(ostream & out = cout);
    vector<int> & operator[] (int row);
    bool testColumn();
    bool testRow();
    bool test3x3Grid(int column_left, int column_right, int row_up, int row_down);
    bool test();
    bool isSolved();

    private:
    vector< vector<int> > grid_;

};

// Operator Overloading
    ostream & operator<< (ostream & out, Grid & G);
#endif
