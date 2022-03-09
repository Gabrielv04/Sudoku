# Sudoku
1. Introduction
A difficulty based sudoku puzzle using backtracking. The puzzle itself if built using a backtracking algorithm and the cells removed are chosen at random.
Each execution of the program will build a different puzzle.
The number of cells removed is determined by the difficulty chosen by the player. 
                                                                



2.Project Description.

The project contains 3 files:
-Header file for Player Class.
-Header file for Board Class.
-The main() function.

The Player class contains the player's name,and a bool variable that indicates whether the puzzle is solved or not.

The Board class contains : 
  
                        -board[9][9]: the board on which the game is played.
                        -solution[9][9]: the solution of the puzzle. In case the user makes a certain number of mistakes, after another wrong move they will be asked whether they want to 
reset their mistake count, end the game and see the solution or simply continue playing as normal.
                        -vector<int> numbers: A vector used to store integers between 1-9. When we attempt to build the board, we shuffle this vector and use it when we build the board using
backtracking(the shuffle is done so as to get a different board on every time we run the program).
                        -unordered_set<string> coordinates : We use this unordered_set to remember the coordinates of the cells that are printed at game start. In the event that the user 
tries to ovewrite one of these cells, they are not allowed to and are prompted to enter a valid move.
                        -int mistakes. This variable keeps track of the number of wrong moves made by the user.
                         -HANDLE hCon. Handle for the console, used in order to modify it's attributes(color,text aligment, etc.). Initialized with NULL, used in methods and destroyed using
the destructor.

3.Algorithm description:


At first all values on the game matrix(board) are initialized with 0. After we shuffle the numbers array, we generate the board using backtracking.
We iterate through the numbers array and check whether the current number is safe to place.The check is performed using the isSafe function which in turn calls 3 other functions to check
the row, column and 3*3 square.
If the function returns true we place the number in the cell and we recursivly call the buildBoard function.
After the board is completed we save it in the solution matrix.

The deleteCells function is used to delete the values in certain cells so as to make the game playable.The function takes a string as argument which signals the difficulty selected
by the player.
Depending on the difficulty level(Easy,Medium,Hard), a certain number of cells are deleted. This number as well as the coordinates of the cells which are to be deleted are generated
at random by using the rand() function.

The playMove function is called every time the player wants to complete one of the empty cells.It checks if the number that is to be written is a digit, if the coordinates passed
by the playerp point to an empty cell and whether the move is valid or not in regards to the game's rules.If the move is incorrect the mistakes variable is incremented and the user is
asked to insert a valid move.

4.THE GAME LOGIC:

The user is asked to continously play moves until they either forfeit the game or they complete the board.This is implemented through the use of another while loop that checks for a 'win'
variable in the Player class. While it if false the sequence repeats itself, and when it turns true a victory message appears. 

  

