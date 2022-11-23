// Filename: treewrapper.cpp
//
// This is the main wrapper for the BST class.
// 
// After running make, the usage is:
//     ./treewrapper <INPUT_FILE> <OUTPUT_FILE>
// 
// The input file contains a list of operations performed on a BST. The operations are insert, delete, find, printing in/pre/post order 
// Each line is of the form:
// 
//         i <INT>: insert <INT> into BST
//         f <INT>: find if <INT> is in BST
//         d <INT>: delete <INT> from BST
//         pin: print tree in order
//         ppre: print tree pre-order
//         ppost: print tree post-order
// 
// The find and print operations generate output, which is either "found/didn't find <INT>" or the tree printed in the desired order.
// 
// The output file contains the output of all commands that lead to output.
// 
// In addition, the console output shows the operations performed, and also prints the tree (for every print command).
// 
// C. Seshadhri, Jan 2020

#include <iostream>
#include "bst.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *op; // for using with strtok, strtol
    string word; // the value from the command
    string range_max;

    BST myBST; // initializing the linked list
        

    while(getline(input,command)) // get next line of input, store as repeat
    {
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " "); //tokenize command on whitespace, first token is operation

        word = strtok(NULL, " "); // next token is value, as string (check out documentation on strtok, to understand the parsing)

        // << INSERT >>
        if(strcmp(op,"i") == 0) // insert into list
        {
            //cout << "Insert "+ word << endl;
            myBST.insert(word);
        }

        // << FIND RANGE >>
        if(strcmp(op,"r") == 0) // insert into list
        {
            range_max = strtok(NULL, " "); // next token is value, as string (check out documentation on strtok, to understand the parsing)
            //cout << "  ++ range_max: " << range_max << endl;

            int range_count = myBST.rangeCount(word, range_max);

            //cout << "Range: " + to_string(range_count) << endl;
            output << to_string(range_count) << endl;
        }
    }

     myBST.deleteBST(); // delete the tree from memory
     input.close();
     output.close();


}
