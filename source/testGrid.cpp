/*******************************************
 *      Programmer: Nhan Nguyen
 *      Program: testGrid.cpp
 *      Purpose: display a sudoku from a file
 *              and allow the user to solve it
 *              by inputing the number
 *      Date: 04/30/2015
 ******************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "Grid.h"

using namespace std;

//Function prototype
void initializeGrid(vector < vector<int> > & grid, vector < vector<int> > & fixedSudoku, istream & fin, Grid & sudoku);
/* This function reads in a sudoku from a text file and updates it to the Grid
 * object 
 *
 * @param grid: the grid, vector of vectors to represent the sudoku
 * @param fin: the input file
 * @param sudoku: the sudoku
 * @param fixedSudoku: the initial number in the original sudoku
 *
 * This function does not return anything
 *
 * Side Effect: there is no side effect
 */
void updateGrid(vector < vector<int> > & grid, char row_choose, int column_choose, int input_choose, Grid & sudoku);
/* This function reads in the user input and update the sudoku
 *
 * @param grid: the grid, vector of vectors to represent the sudoku
 * @param row_choose: the row the user chose
 * @param column_choose: the column the user chose
 * @param input_choose: the value the user input
 * @param sudoku: the sudoku
 *
 * This function does not return anything
 *
 * Side Effect: There is no side effect.
 */
void promtForGrid(char & row_choose, int & column_choose, int & input_choose, const vector < vector<int> > & fixedSudoku);
/* This function promts user for choice of row, column and input number
 *
 * @param row_choose: user's input of row
 * @param column_choose: user's input of column
 * @param input_choose: user's input of number
 * @param fixedSudoku: the initial number in the original sudoku
 *
 * This function does not return anything
 *
 * Side Effect: There is no side effect
 */
int main()
{   //------------- program begin -----------------
    // Declare necessary variable
    Grid sudoku;
    vector< vector<int> > fixedSudoku; // for the original value in the sudoku
    vector< vector<int> > grid(9); // used for initializing the sudoku
    ifstream fin; // input file
    ofstream fout; // output_file
    fin.open("sudoku.txt");
    // initial the sudoku
    initializeGrid(grid, fixedSudoku, fin, sudoku);
    fin.close();

    char row_choose;
    int column_choose, input_choose, value_before_modified;
    int row_choose_in_number;

    // start the sudoku
    do
    {
    if (sudoku.isSolved())
    {
        cout << sudoku << endl;
        cout << endl << "You have solved the sudoku." << endl << endl;
        fout.open("solved_sudoku.txt");
        fout << sudoku << endl;
        fout.close();
        break;
    }
    else
    {
        // print out the sudoku
        cout << sudoku << endl;
        // ask user's input
        promtForGrid(row_choose, column_choose, input_choose, fixedSudoku);
        if ((row_choose != 'Q') && (input_choose != 10))
        {
            row_choose_in_number = row_choose - 65;
            // get the original value of the sudoku
            value_before_modified = sudoku.getValueInColumn(row_choose_in_number, column_choose);
            // then update the sudoku
            updateGrid(grid,row_choose, column_choose, input_choose, sudoku);
            // test the input according to the rules
            if (!sudoku.test())
            {
                cout << endl << "Invaid input. Please enter again." << endl << endl;
                // go back to the previous version
                updateGrid(grid, row_choose, column_choose, value_before_modified, sudoku);
            }
        }
    }
    }
    while ((row_choose != 'Q')  && (input_choose != 10));
    return 0;
    //------------ end program -------------
}

//Function Definition
void initializeGrid(vector < vector<int> > & grid, vector < vector<int> >  & fixedSudoku, istream & fin, Grid & sudoku)
{
   int number;
   int row_count = 0;
   int grid_count = 0;
   vector<int> row(9);
   vector<int> fixedSudokuInRow;
   while (fin >> number)
   {
       row[row_count] = number;
       // get the original value's position
       if (number > 0)
       {
            fixedSudokuInRow.push_back(row_count);
       }
       row_count++;
       if (row_count == 9)
       {
           row_count = 0;
           grid[grid_count] = row;
           fixedSudoku.push_back(fixedSudokuInRow);
           fixedSudokuInRow.clear();
           grid_count++;
       }
       if (grid_count >= 10)
       {
           cout << "Invalid. The sudoku in the text file has more than 9 rows." << endl;
       }
       else
       {
           sudoku.setGrid(grid);
       }
   } 
}
void updateGrid(vector < vector<int> > & grid, char row_choose, int column_choose, int input_choose, Grid & sudoku)
{
    int row_choose_in_number = row_choose - 65;
    grid[row_choose_in_number][column_choose] = input_choose;
    sudoku.setGrid(grid);
}

void promtForGrid(char & row_choose, int & column_choose, int & input_choose, const vector < vector<int> > & fixedSudoku)
{
    bool testModified;
    int row_choose_in_number;
    do
    {
        testModified = false;
    do
        { 
            cout << "Enter the coordinate of the place which\nyou want to put your number in i.e. G3 (Q1 to quit): ";
            cin >> row_choose >> column_choose;
            row_choose_in_number = row_choose - 65;
            if (row_choose == 'Q')
            {
                exit(1);
            }
            if (row_choose < 'A' || row_choose > 'I')
            {
                cout << "Out of range input of row choice. Please input again." << endl;   
            }
            if (column_choose < 0 || column_choose > 8)
            {
                cout << "Out of range input of column choice. Please input again." << endl;
            }
        }
    while (row_choose < 'A' || row_choose > 'I');
    do
        {
            cout << "Enter your number (10 to quit, 0 to delete): ";
            cin >> input_choose;
            if (input_choose > 10)
            {
                cout << "Out of range input of number choice. Please input again." << endl;
            }
        }
    while (input_choose > 10);

    for (int i = 0; i < fixedSudoku[row_choose_in_number].size(); i++)
            {
                if (fixedSudoku[row_choose_in_number][i] == column_choose)
                {
                    if (input_choose >= 0)
                    {
                        cout << "You cannot modify the default values in the sudoku. Please input again." << endl;
                        testModified = true;
                    }
                    else
                    {
                        cout << "You modified one of the default value in the sudoku." << endl;
                        input_choose = -input_choose;
                        testModified = false;
                    }
                }
            }
    }
    while (testModified);
}
