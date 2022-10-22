
class Board:
    def __init__(self, size):
        self.board = []
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
        
        print("++++ checking queen ...")

        # adjust for index
        row -= 1
        col -= 1
        

        # base case, queen not in valid spot
        if self.board[row][col] != 0:
            print("  ++ ERROR: init spot not valid")
            return 0
        print("    + init spot valid")

        # check row for queen
        for c in range(self.size):
            if (c != col):
                if self.board[row][c] > 0:
                    print("  ++ ERROR: row not valid")
                    return 0
        print("    + row valid")

        # check column for queen
        for r in range(self.size):
            if (r != row):
                if self.board[r][col] > 0:
                    print("  ++ ERROR: column not valid")
                    return 0
        print("    + column valid")

        # check right diags
        curr_y_offset = 1 # offset from queen pos for finding diags 

        # iterate through columns on the right
        for c in range(col + 1, self.size):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] > 0:
                print("  ++ right diags not valid")
                return 0
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] > 0:
                print("  ++ right diags not valid")
                return 0
            curr_y_offset += 1
        print("    + right diags valid")

        # iterate through columns on the left
        curr_y_offset = 1
        for c in range(col - 1, -1, -1):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] > 0:
                print("  ++ left diags not valid")
                return 0
            if (row + curr_y_offset < self.size) and self.board[row + curr_y_offset][c] > 0:
                print("  ++ left diags not valid")
                return 0
            curr_y_offset += 1
        print("    + left diags valid")


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
        
        # set to index values
        col -= 1
        row -= 1

        # << SET ROWS // COLUMNS // DIAGS >>
        # check row
        for c in range(self.size):
            if (self.board[row][c] <= 0):
                self.board[row][c] -= 1

        # check column
        for r in range(self.size):
            if (self.board[r][col] <= 0):
                self.board[r][col] -= 1

        # check right diags
        curr_y_offset = 1 # offset from queen pos for finding diags 

        # iterate through columns on the right
        for c in range(col + 1, self.size):
            if (row - curr_y_offset > -1) and self.board[row - curr_y_offset][c] >= 0:
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

    # 

    # print chess board at curr state
    def print(self):
        # print column markers
        col_str = "    |"
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
                if self.board[row][c] <= -1:
                    row_str += " ."
                else:
                    row_str += " " + str(self.board[row][c])
            print(row_str)


board = Board(11)
board.create()
board.print()

# << ADD QUEENS >>
# queen 1 
board.add_queen(4,4)

board.add_queen(4,8)

# queen 2
#board.add_queen(1,8)

board.print()

## To find all queen spots,

## start from top of board (row 1)
## <<ITERATE>> through each row
    ## <<ITERATE>> through each column and 'place' queen
        # check if queen is valid
        #