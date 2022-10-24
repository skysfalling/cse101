
class Board:
    def __init__(self, size):
        self.board = []
        self.queen_stack = []
        self.size = size
        self.queen_count = 0

    # create double array for board
    def create(self):
        for row in range(self.size):
            self.board.append([])
            for c in range(self.size):
                self.board[row].append(0)

    # check row, columns and diags
    def check_queen(self, row, col):
        
        print("++++ checking queen", row, col)

        # adjust for index
        row -= 1
        col -= 1
        
        # base case, queen not in valid spot
        if self.board[row][col] != 0:
            print("  ++ ERROR: init spot not valid")
            return 0
        #print("    + init spot valid")

        # check row for queen
        for c in range(self.size):
            if (c != col and self.board[row][c] != None):
                if self.board[row][c] > 0:
                    print("  ++ ERROR: row not valid")
                    return 0
        #print("    + row valid")

        # check column for queen
        for r in range(self.size):
            if (r != row and self.board[row][c] != None):
                if self.board[r][col] > 0:
                    print("  ++ ERROR: column not valid")
                    return 0
        #print("    + column valid")

        # check right diags
        curr_y_offset = 1 # offset from queen pos for finding diags 

        # iterate through columns on the right
        for c in range(col + 1, self.size):

            if self.board[row - curr_y_offset][c] != None or self.board[row - curr_y_offset][c] != None:

                if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] != None and self.board[row - curr_y_offset][c] > 0:
                    print("  ++ right diags not valid")
                    return 0
                if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] != None and  self.board[row + curr_y_offset][c] > 0:
                    print("  ++ right diags not valid")
                    return 0
            curr_y_offset += 1
        #print("    + right diags valid")

        # iterate through columns on the left
        curr_y_offset = 1
        for c in range(col - 1, -1, -1):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] != None and self.board[row - curr_y_offset][c] > 0:
                print("  ++ left diags not valid")
                return 0
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] != None and self.board[row + curr_y_offset][c] > 0:
                print("  ++ left diags not valid")
                return 0
            curr_y_offset += 1
        #print("    + left diags valid")

        print("    + QUEEN IS VALID\n")
        return 1

    # add queen
    def add_queen(self, row, col):
        print("\n>> ADD QUEEN", row, col)

        # << CHECK QUEEN >>
        valid = self.check_queen(row, col)
        if valid == 0:
            print("  ERROR: Queen", row, col, "is not valid ****")
            return
        
        # push queen to stack
        self.queen_stack.append([row,col])

        # set to index values
        col -= 1
        row -= 1

        # << SET ROWS // COLUMNS // DIAGS >>
        # set row
        for c in range(self.size):
            if (self.board[row][c] != None and self.board[row][c] <= 0):
                self.board[row][c] -= 1

        # set column
        for r in range(self.size):
            if (self.board[row][c] != None and self.board[r][col] <= 0):
                self.board[r][col] -= 1

        # set right diags
        curr_y_offset = 1 # offset from queen pos for finding diags 

        # iterate through columns on the right
        for c in range(col + 1, self.size):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] <= 0:
                self.board[row - curr_y_offset][c] -= 1
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] <= 0:
                self.board[row + curr_y_offset][c] -= 1
            curr_y_offset += 1

        # iterate through columns on the left
        curr_y_offset = 1
        for c in range(col - 1, -1, -1):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] <= 0:
                self.board[row - curr_y_offset][c] -= 1
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] <= 0:
                self.board[row + curr_y_offset][c] -= 1
            curr_y_offset += 1

        # add queen
        self.queen_count += 1
        self.board[row][col] = self.queen_count

    # delete queen
    def remove_queen(self, row, col):
        print("\n>> REMOVE QUEEN", row, col)

        self.queen_count -= 1

        # set to index values
        col -= 1
        row -= 1

        if self.board[row][col] <= 0:
            print("++ ERROR: Queen", row+1, col+1, "does not exist at this cell")
            return

        self.board[row][col] = 0 # reset queen

        # << SET ROWS // COLUMNS // DIAGS >>
        # set row
        for c in range(self.size):
            if (self.board[row][c] < 0):
                self.board[row][c] += 1

        # set column
        for r in range(self.size):
            if (self.board[r][col] < 0):
                self.board[r][col] += 1

        # set right diags
        curr_y_offset = 1 # offset from queen pos for finding diags 

        # iterate through columns on the right
        for c in range(col + 1, self.size):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] < 0:
                self.board[row - curr_y_offset][c] += 1
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] < 0:
                self.board[row + curr_y_offset][c] += 1
            curr_y_offset += 1

        # iterate through columns on the left
        curr_y_offset = 1
        for c in range(col - 1, -1, -1):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] < 0:
                self.board[row - curr_y_offset][c] += 1
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] < 0:
                self.board[row + curr_y_offset][c] += 1
            curr_y_offset += 1

    # solve nqueens problem
    def solve(self, init_queens):
        print("\n============= SOLVE ==================")

        # << ADD QUEENS >>
        for queen in init_queens:
            board.add_queen(queen[0], queen[1])

        # print init queen stack
        print("  ++ init queen stack:", self.queen_stack)

        self.print()

        print("==== start iteration ====\n")
        curr_row = 1
        rec_col_start = 1 # recursive column start, adjusts to last value of checked queen in row
        # board is solved if queen stack is board size
        while (curr_row < self.size + 1):
            print("\n======= new iteration ========")
            print("\ncurr row:", curr_row)
            print("rec_col_start:", rec_col_start)

            # for each space in row, check if you can place queen
            valid_queen_found = 0
            
            # check for init queen in row
            for queen in init_queens:
                if queen[0] == curr_row:
                    print(" ++ init queen is in this row")
                    valid_queen_found = 1
                    break
                
            # check for valid queen space
            if valid_queen_found == 0:
                for col in range(rec_col_start, self.size + 1):
                    if self.board[curr_row-1][col-1] != None and self.check_queen(curr_row, col) == 1:
                        print(" ++ found valid queen", curr_row, col)
                        self.add_queen(curr_row, col)
                        valid_queen_found = 1
                        break

            # if found queen space, continue searching
            if valid_queen_found == 1:
                curr_row += 1
                rec_col_start = 1
            else:
                backtrack_count = -1
                continue_search = 0 # backtracked enough to find a valid row
                while (self.queen_stack[backtrack_count] != None and continue_search == 0):
                    
                    print("    ** backtracking:", backtrack_count)

                    # if backtrack value not in initial queens
                    if self.queen_stack[backtrack_count] not in init_queens:

                        remove_queen_val = [self.queen_stack[backtrack_count][0], self.queen_stack[backtrack_count][1]]
                        
                        print("  ++ backtrack remove ", remove_queen_val[0], remove_queen_val[1])
                        self.remove_queen(remove_queen_val[0], remove_queen_val[1]) # remove queen from board
                        self.queen_stack.pop() # remove top queen from stack
                        
                        self.board[remove_queen_val[0] - 1][remove_queen_val[1] - 1] = None # remove from truw indexes from possible solutions

                        curr_row += backtrack_count
                        #rec_col_start = self.queen_stack[backtrack_count][1] + 1 # get top cell, next column value
                        
                        continue_search = 1
                    # loop until finding a valid backtrack value
                    else:
                        print("  ++ backtrack skip ", self.queen_stack[backtrack_count][0], self.queen_stack[backtrack_count][1])
                        backtrack_count -= 1
                
                # if backtracking all the way to invalid cell, no solution
                if self.queen_stack[backtrack_count] == None:
                    print(" ++ total backtrack amount: ", backtrack_count)
                    print("\n << No Solution >>\n")
                    break


            print(" ++ queen stack:", self.queen_stack )
            self.print()
            print("\n\n")
            
    # print chess board at curr state
    def print(self):
        # print column markers
        col_str = "\n    |"
        for column in range(self.size):
            col_str += str(column + 1) + "|"
        print(col_str)

        # print rows
        for row in range(self.size):
            if (row > 8):
                row_str = "|" + str(row + 1) + "|"
            else:
                row_str = "| " + str(row + 1) + "|"

            for c in range(self.size):
                if self.board[row][c] == None:
                    row_str += " X"
                elif self.board[row][c] <= -1:
                    row_str += " ."
                else:
                    row_str += " " + str(self.board[row][c])
            print(row_str)

# =========================================
board = Board(5)
board.create()
board.print()

print(" << BOARD SIZE :", board.size, " >>")

init_queens = [[1,2], [2,5]]
board.solve(init_queens)


## To find all queen spots,

## start from top of board (row 1)
## <<ITERATE>> through each row
    ## <<ITERATE>> through each column and 'place' queen
        # check if queen is valid
        
