#include <iostream>
#include "linkedlistfunc.h"
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
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *dummy, *valstr, *op; // for using with strtok, strtol
    int val; // the value from the command

    LinkedList myList; // initializing the linked list
        

    while(getline(input,command)) // get next line of input, store as repeat
    {
        // << SKIP IF COMMAND IS EMPTY >>
	if (command.length() == 0) // command is empty
            continue;
        
	com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " \t"); //tokenize command on whitespace, first token is operation

	// << PRINT COMMAND >>
        // We first check if command is to print, since we do not need further parsing of command
        if(strcmp(op,"p") == 0) // print list
        {
            output << myList.print() << endl; // write printed list to file, and add new line
            cout << "Printing" << endl;
            cout << myList.print() << endl; // printing to console
            continue; // move on to next command
        }

	// << SPLIT STRING INTO "COMMAND / VALUE" >>
        valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if(valstr != NULL) // first check if there is actually anything to convert into int
            val = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details. 
    
	// ** INSERT **
        if(strcmp(op,"i") == 0) // insert into list
        {
            cout << "Insert "+to_string(val) << endl;
            myList.insert(val);
        }

	// ** DELETE **
        if(strcmp(op,"d") == 0) // delete from list
        {
            cout << "Delete "+to_string(val) << endl;
            myList.deleteNode(val);
        }
     }


// ====================== ADV OPERATIONS ===========================

    /*
     // << TEST deleteNode(Node*) >>
     cout << "<< TEST : Delete head->next with deleteNode(Node*) " << endl;
     myList.deleteNode(myList.head->next);
     cout << myList.print() << endl;
    */

    
    // << TEST deleteOccurence >>
    cout << "<< TEST : Delete LAST Occurence of 6 >>" << endl;
    myList.deleteOccurrence(6, -1);
    cout << myList.print() << endl; 
    

    
    // << TEST reverse list >>
    cout << "<< TEST : Reverse List >>" << endl;
    myList.reverse(myList.head);
    cout << myList.print() << endl;
    

    // << TEST deleteExtraOccurences >>
    cout << "<< TEST : deleteExtraOccurences -> val(6) >>" << endl;
    myList.deleteExtraOccurrences(6);
    cout << myList.print() << endl;


    input.close();
    output.close();
}






















