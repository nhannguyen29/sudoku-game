/*****************************************
 *      Programmer: Nhan Nguyen
 *      Program: Grid.cpp
 *      Purpose: The implementation file for the
 *              Grid class
 *      Date: 04/30/2015
 ****************************************/

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "Grid.h"
using namespace std;

    // Class Definition

    // Constructor
        
        Grid::Grid() {} // default constructor

        Grid::Grid(vector< vector<int> > grid) // alternate constructor
        {
            grid_ = grid;
        }
        
        Grid::Grid(const Grid & G) // copy constructor
        {
            grid_ = G.getGrid();
        }
        
    // Destructor

        Grid::~Grid() {}

    //Inspector

        vector< vector<int> > Grid::getGrid() const
        {
            return grid_;
        }
        
        vector<int> Grid::getRow(int row) const
        {
            return grid_[row];
        }
        
        int Grid::getValueInColumn(int row, int column) const
        {
            return grid_[row][column];
        }

    //Mutator

        void Grid::setGrid(vector< vector<int> > grid)
        {
            grid_ = grid;
        }

        void Grid::setRow(vector<int> new_row)
        {
            grid_.push_back(new_row);
        }

    //Facilitator

        void Grid::output(ostream & out)
        { 
            int count = 0;
            for (int i =0; i < grid_.size(); i++)
            {
            for (int j = 0; j < grid_[i].size(); j++)
                {
                   if (grid_[i][j] == 0)
                   {
                        out << "-" << " ";
                   }
                   else 
                   {
                        out << grid_[i][j] << " ";
                   }
                   count++;
                   if (count == 9)
                   {
                        out << endl;
                        count = 0;
                   }
                }
            }

        }
        void Grid::display(ostream & out)
        {
            string dash_board(7, '-');
            char row_character = 'A';
            string border = "+" + dash_board + "+" + dash_board + "+" + dash_board + "+"; 
            out << setw(4) << " " << 0 << " " << 1 << " " << 2 << setw(4) << 3 << " " << 4 << " " << 5
                << setw(4) << 6 << " " << 7 << " " << 8 << setw(2) << endl; 
            for (int i = 0; i < grid_.size(); i++)
            {
                if (i % 3 == 0)
                {
                    out << "  " << border << endl;
                }
                out << row_character << " ";
                for (int j = 0; j < grid_[i].size(); j++)
                {
                   if ((j) % 3 == 0)
                   {
                        out << "| ";
                   }
                   if (grid_[i][j] == 0)
                   {
                        out << "-" << " ";
                   }
                   else 
                   {
                        out << grid_[i][j] << " ";
                   }
                                   }
                out << "|" << endl;
                row_character++;
            }
            out << "  " << border << endl;
        }

        vector<int> & Grid::operator[] (int row)
        {
            return grid_[row];
        }
        
        bool Grid::testColumn()
        {
            bool test = true;
            // test by recording the appearance of a number in the columns
            for (int column = 0; column < 9; column++)
            {   
            vector<int> count(10,0);
	        for (int i =0; i < 9; i++)
            {          
	            count[grid_[i][column]]++;
            }
            // if one column fails the rule, return false
            for (int i = 1; i < 10; i++)
            {
                if (count[i] == 2)
                {
                    test = false;
                    break;
                }
            }
            }
            return test;
        }
        
        bool Grid::testRow()
        {
            bool test = true;
            // test by recording the appearance of a number in the rows
            for (int row = 0; row < 9; row++)
            {
            vector<int> count(10,0);
            for (int i = 0; i < 9; i++)
            {
                count[grid_[row][i]]++;
            }
            // if one row fails the rule, return false
            for (int i = 1; i < 10; i++)
            {
                if (count[i] == 2)
                {
                    test = false;
                    break;
                }
            }
            }
            return test;
        }
        
        bool Grid::test3x3Grid(int column_left, int column_right, int row_up, int row_down)
        {
            // test by recording the appearance of a number in the 3x3 grids
            bool test = true;
            vector<int> count(10,0);
            for (int i = column_left; i <= column_right; i++)
            {
                for (int j = row_up; j <= row_down; j++)
                {
                    count[grid_[i][j]]++;
                }
            }
            for (int i =1; i<10; i++)
            {
                if (count[i] == 2)
                {
                    test = false;
                    break;
                }
            }
            return test; 
        }

        bool Grid::test()
        {
            // if one grid fails the rule, return false for the 3x3Grid test
           bool testAll3x3Grid = (((test3x3Grid(0,2,0,2) && test3x3Grid(0,2,3,5))
                                   && test3x3Grid(0,2,6,8)) && ((test3x3Grid(3,5,0,2)
                                   && test3x3Grid(3,5,3,5)) && test3x3Grid(3,5,6,8)))
                                   && ((test3x3Grid(6,8,0,2) && test3x3Grid(6,8,3,5))
                                   && test3x3Grid(6,8,6,8));
            return (testColumn() && testRow()) && testAll3x3Grid;
        }
        
        bool Grid::isSolved()
        {
            bool testSolved = true;
            for(int row = 0; row < 9; row++)
            {
                for (int column = 0; column < 9; column++)
                {
                    if (grid_[row][column] == 0)
                    {
                        testSolved = false;
                        break;
                    }
                }
            }

            testSolved = testSolved && test();
            return testSolved;
        }
    // Operator Overloading
        
        ostream & operator<< (ostream & out, Grid & G)
        {
            if (&out == &cout)
            {
                G.display(out);
            }
            else
            {
                G.output(out);
            }
            return out;
        }
