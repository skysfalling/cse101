#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <stack>

using namespace std;

class Board
{
    public:
      Board(int); // create board of size

      int board_size;
      vector<vector<int>> board_vec;

      int invalid_type; // space has been checked and is invalid

      int queen_count;
      vector<vector<int>> init_queens; // initial queens
      stack<vector<int>> queen_stack; // queen stack

      void add_queen(int, int);
      int check_queen(int, int);
      void remove_queen(int, int);
      string solve();

      void change_cell_type(int, int, int);
      void print_queens();
      void print_stack(stack<vector<int>> s);
      void print();

      string out_string();
};

#endif