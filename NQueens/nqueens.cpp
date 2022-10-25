#include <iostream>
#include "board.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file


    string in_str; // to store the next command and operation
    char *com, *in_size; // for using with strtok, strtol

    while(getline(input, in_str)) // get next line of input, store as repeat
    {
        if (in_str.length() == 0) // command is empty
            continue;
        com = strdup(in_str.c_str()); // annoying, first copy string into a "C-style" string
        in_size = strtok(com, " \t"); //tokenize command on whitespace, first token is operation


        // "<< CREATE BOARD >>"
        cout << "in_size: " << in_size << endl;
        int board_size = stoi(in_size); // convert from str to int
        Board *board = new Board(board_size);


        // "<< GET INIT QUEENS >>"
        char *row, *col;
        int invalid_queen = 0;
        int init_queen_count = 0;
        while (invalid_queen == 0)
        {
          row = strtok(NULL, " \t");
          col = strtok(NULL, " \t");

          if (row == NULL || col == NULL) { invalid_queen = 1;}
          else { 
            cout << "input queen: " << row << " " << col << endl; 

              int in_row = stoi(row);
              int in_col = stoi(col);

              board->init_queens[init_queen_count] = {in_row, in_col};
              init_queen_count ++;
            }
        }
        cout << endl;

        // output
        output << board->solve() << endl;

    }

    input.close();
    output.close();
}