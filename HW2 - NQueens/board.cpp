#include "board.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

// Default constructor for Board
Board :: Board(int size)
{
    board_size = size;
    queen_count = 0;
    invalid_type = size + 2;

    init_queens.resize(size); // set init queens to size
    board_vec.resize(size);

    // << CREATE ROWS >>
    for (int i = 0; i < size; i++)
    {
        board_vec[i].resize(size);

        // << CREATE COLUMNS >>
        for (int j = 0; j < size; j++)
        {
            board_vec[i][j] = 0;
        }
    }

    print();

}

string Board :: solve(){

  cout << "\n((((((((((( SOLVE )))))))))))))))))))))))))))" << endl;

  // add init queens to board / stack
  for (int i = 0; i < (int)init_queens.size(); i++)
  {
      if (init_queens[i].empty()) { break;}

      if (check_queen(init_queens[i][0], init_queens[i][1]) == 0)
      {
        cout << "ERROR: INIT QUEEN PLACEMENT IS INVALID \nNo solution" << endl;
        return "No solution";
      }

      add_queen(init_queens[i][0], init_queens[i][1]);
  }

  print_queens();

  cout << " <<<<<< START ITERATION >>>>>>>" << endl;

  int curr_row = 1;
  int rec_col_start = 1; // recursive column start, adjusts to last value of checked queen in row

        
  // board is solved if queen stack is board size
  while (curr_row <= board_size){
    cout << "\nNew Iteration: ";
    cout << "curr_row(" << to_string(curr_row) << ")";
    cout << "re_col_start(" << to_string(rec_col_start) << ")";
    cout << "queen_count(" << to_string(queen_count) << ")" << endl;

    // for each space in row, check if you can place queen
    int valid_queen_found = 0;

    // check for init queen in row
    for (vector<int> queen : init_queens){
        if (queen.empty())
        {
          // cout << "  ++ no init queens in this row" << endl;
          break;
        }
        else if (queen[0] == curr_row)
        {
          cout << "  ++ init queen is in this row" << endl;
          queen_stack.push(queen);
          valid_queen_found = 1;
          break;
        }
    }

    // check for valid queen space
    if (valid_queen_found == 0){

      // for remaining columns in row
      for (int col = rec_col_start; col <= board_size; col++){
        // check if queen can fit
        if (check_queen(curr_row, col) == 1){
          cout << " ++ FOUND VALID QUEEN" << endl << endl;
          queen_stack.push({curr_row, col});
          add_queen(curr_row, col);
          valid_queen_found = 1;
          break;
        }
      }
    }

    // if valid queen found, continue searching
        // else, backtrack to valid row
    if (valid_queen_found == 1){
      curr_row ++;
      rec_col_start = 1;
    }
    else{
      
      int backtrack_count = -1;
      int continue_search = 0; // backtracked enough to find a valid row

      while (queen_stack.size() > 0 && continue_search == 0)
      {
        cout << "    ** backtracking " << to_string(backtrack_count) << endl;

        vector<int> top = queen_stack.top();
        int top_is_init = 0; // check whether top of stack is init queen
        for (vector<int> queen : init_queens){
            if (queen.empty())
            {
              // cout << "  ++ no init queens in this row" << endl;
              break;
            }
            else if (queen == top)
            {
              cout << "  ++ init queen is in this row" << endl;
              top_is_init = 1;
              break;
            }
        }

        queen_stack.pop(); // pop from stack

        // if top of stack is not init, remove from board nd continue search
        if (top_is_init == 0){
          remove_queen(top[0], top[1]); // remove queen from board
          //change_cell_type(top[0], top[1], invalid_type); // set space to invalid type

          curr_row += backtrack_count; // continue_search
          rec_col_start = top[1] + 1; // get top cell, next column value

          continue_search = 1;
        }
        else{
          cout << "  ++ backtrack skip: " << to_string(top[0]) << " " << to_string(top[1]) << endl;
          backtrack_count -= 1;
        }
      }

      // << NO SOLUTION >>
      if (queen_stack.size() == 0 && continue_search == 0)
      {
        cout << " ++ total backtrack: " << to_string(backtrack_count) << endl;
        cout << " << No solution >>" << endl;

        string out = out_string();
        cout << "OUT: " << out << endl;
        return out;
      }
    }

    print();
  }

  string out = out_string();
  cout << "<< VALID SOLUTION >> : " << out << endl;
  return out;

}


// CHANGE TYPE OF CELL
// ** any int above 0 is a queen
// ** any int below 0 is a 'invalid' space
void Board :: change_cell_type(int row, int col, int type)
{
    board_vec[row - 1][col - 1] = type;
}


void Board :: add_queen(int row, int col)
{
    cout << ">> ADD QUEEN " << to_string(row) << " " << to_string(col) << endl;

    // CHECK IF QUEEN IS VALID
    int valid = check_queen(row, col);
    if (valid == 0)
    {
      cout << "  ERROR: Queen " << to_string(row) << " " << to_string(col) << " is not valid ****" << endl;
      return;
    }

    // SET RELATED INVALID CELLS
    queen_count += 1;
    change_cell_type(row, col, queen_count);

    // set to index values
    row -= 1;
    col -= 1;

    // ** set row to invalid**
    for (int c = 0; c < board_size; c++)
    {
        if (board_vec[row][c] <= 0)
        {
            board_vec[row][c] -= 1;
        }
    }

    // ** set column to invalid**
    for (int r = 0; r < board_size; r++)
    {
        if (board_vec[r][col] <= 0)
        {
            board_vec[r][col] -= 1;
        }
    }

    // ** set right diags to invalid **
    int curr_y_offset = 1;
    for (int c = col + 1; c < board_size; c++)
    {
      if (row - curr_y_offset > -1  && board_vec[row - curr_y_offset][c] <= 0){
          board_vec[row - curr_y_offset][c] -= 1;
      }
      if (row + curr_y_offset < board_size && board_vec[row + curr_y_offset][c] <= 0){
          board_vec[row + curr_y_offset][c] -= 1;
      }
      curr_y_offset += 1;
    }

    // ** set left diags to invalid **
    curr_y_offset = 1;
    for (int c = col - 1; c > -1; c--)
    {
      if (row - curr_y_offset > -1  && board_vec[row - curr_y_offset][c] <= 0){
          board_vec[row - curr_y_offset][c] -= 1;
      }
      if (row + curr_y_offset < board_size && board_vec[row + curr_y_offset][c] <= 0){
          board_vec[row + curr_y_offset][c] -= 1;
      }
      curr_y_offset += 1;
    }

}

void Board :: remove_queen(int row, int col)
{
    cout << ">> REMOVE QUEEN " << to_string(row) << " " << to_string(col) << endl;

    // SET RELATED INVALID CELLS
    queen_count -= 1;
    change_cell_type(row, col, 0);

    // set to index values
    row -= 1;
    col -= 1;

    // ** reset row**
    for (int c = 0; c < board_size; c++)
    {
        if (board_vec[row][c] < 0)
        {
            board_vec[row][c] += 1;
        }
    }

    // ** set column to invalid**
    for (int r = 0; r < board_size; r++)
    {
        if (board_vec[r][col] < 0)
        {
            board_vec[r][col] += 1;
        }
    }

    // ** reset right diags **
    int curr_y_offset = 1;
    for (int c = col + 1; c < board_size; c++)
    {
      if (row - curr_y_offset > -1  && board_vec[row - curr_y_offset][c] < 0){
          board_vec[row - curr_y_offset][c] += 1;
      }
      if (row + curr_y_offset < board_size && board_vec[row + curr_y_offset][c] < 0){
          board_vec[row + curr_y_offset][c] += 1;
      }
      curr_y_offset += 1;
    }

    // ** set left diags to invalid **
    curr_y_offset = 1;
    for (int c = col - 1; c > -1; c--)
    {
      if (row - curr_y_offset > -1  && board_vec[row - curr_y_offset][c] < 0){
          board_vec[row - curr_y_offset][c] += 1;
      }
      if (row + curr_y_offset < board_size && board_vec[row + curr_y_offset][c] < 0){
          board_vec[row + curr_y_offset][c] += 1;
      }
      curr_y_offset += 1;
    }
}

int Board :: check_queen(int row, int col)
{
    cout << ">> checking queen " << to_string(row) << " " << to_string(col) << endl;

    // set to index values
    row -= 1;
    col -= 1;

    // check if spot is nullified
    if (board_vec[row][col] == invalid_type)
    {
       cout << "  ++ ERROR: cell is of invalid type" << endl;
    }

    // base case, check if queen in valid spot
    if (board_vec[row][col] != 0)
    {
        cout << "  ++ ERROR: init spot not valid" << endl;
        return 0;
    }
    //cout << "    + init spot valid" << endl;


    // ** check row for another queen **
    for (int c = 0; c < board_size; c++)
    {
        // if not curr queen column and type is queen (not invalid spot)
        if (c != col && (board_vec[row][c] > 0 && board_vec[row][c] != invalid_type))
        {
            cout << "  ++ ERROR: row not valid" << endl;
            return 0;
        }
    }
    //cout << "    + row valid" << endl;


    // ** check column for another queen **
    for (int r = 0; r < board_size; r++)
    {
        // if not curr queen column and type is queen
        if (r != row && (board_vec[r][col] > 0 && board_vec[r][col] != invalid_type))
        {
            cout << "  ++ ERROR: column not valid" << endl;
            return 0;
        }  
    }
    //cout << "    + column valid" << endl;


    // ** check for queen in right diags **
    int curr_y_offset = 1;
    for (int c = col + 1; c < board_size; c++)
    {
      if (row - curr_y_offset > -1  
      && (board_vec[row - curr_y_offset][c] > 0 && board_vec[row - curr_y_offset][c] != invalid_type)){
          cout << "  ++ right diags not valid" << endl;
          return 0;
      }
      if (row + curr_y_offset < board_size 
      && (board_vec[row + curr_y_offset][c] > 0 && board_vec[row + curr_y_offset][c] != invalid_type)){
          cout << "  ++ right diags not valid" << endl;
          return 0;
      }
      curr_y_offset += 1;
    }
    //cout << "    + right diags valid" << endl;

    // ** set left diags to invalid **
    curr_y_offset = 1;
    for (int c = col - 1; c > -1; c--)
    {
      if (row - curr_y_offset > -1  
      && (board_vec[row - curr_y_offset][c] > 0 && board_vec[row - curr_y_offset][c] != invalid_type)){
          cout << "  ++ left diags not valid" << endl;
          return 0;
      }
      if (row + curr_y_offset < board_size 
      && (board_vec[row + curr_y_offset][c] > 0 && board_vec[row + curr_y_offset][c] != invalid_type)){
          cout << "  ++ left diags not valid" << endl;
          return 0;
      }
      curr_y_offset += 1;
    }
    //cout << "    + left diags valid" << endl;

    //cout << "    + Queen is valid" << endl;
    return 1;
}

string Board :: out_string()
{
  string out;
  if (queen_stack.empty()){
    out = "No solution";
  }
  else{

    while (!queen_stack.empty())
    {
      vector<int> top = queen_stack.top();

      out.insert(0 , to_string(top[0]) + " " + to_string(top[1]) + " ");

      queen_stack.pop();
    }
  }

  return out;
}

void Board :: print(){

    // cout << endl << "PRINT: " << endl;

    // << PRINT COLUMN REFERENCE >>
    cout << "    ";
    for (int c = 1; c < (int)board_vec.size() + 1; c++)
    {
        cout << to_string(c) << "|";
    }
    cout << endl;

    // << PRINT CURRENT BOARD >>
    for (int i = 0; i < (int)board_vec.size(); i++)
    {
        cout << " " << to_string(i + 1) << "| ";
        for (int j = 0; j < (int)board_vec.size(); j++)
        {
            if (board_vec[i][j] < 0 ){
              cout << ". "; // print value
            }
            else if (board_vec[i][j] == invalid_type)
            {
              cout << "X ";
            }
            else
            {
              cout << board_vec[i][j] << " "; 
            }
        }

        cout << "||" << endl;
    }

    // << PRINT BOTTOM LINE >>
    cout << "    ";
    for (int c = 1; c < (int)board_vec.size() + 1; c++)
    {
        cout << "==";
    }

    print_queens();

    cout << endl << endl;
}


void Board :: print_queens()
{
   cout << "  QUEENSTACK: ";

   print_stack(queen_stack);

   cout << endl;
}


void Board :: print_stack(stack<vector<int>> s)
{
    // If stack is empty then return
    if (s.empty())
        return;
     
    vector<int> x = s.top();
 
    // Pop the top element of the stack
    s.pop();
 
    // Recursively call the function PrintStack
    print_stack(s);
 
    // Print the stack element starting
    // from the bottom
    cout << "Q" << to_string(board_vec[x[0]-1][x[1]-1]) << ":<" << x[0] << "," << x[1] << ">" << " ";
 
    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}
