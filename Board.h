#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<random>
#include<unordered_set>
#include<sstream>
#include<string>
#include<windows.h>

using namespace std;


//Header file for the sudoku solver.
#define N 9 
#define EMPTY 0

class Board
{
    int board[N][N];
    int solution[N][N];
    vector<int> numbers;
    unordered_set<string> coordinates;
    int mistakes;
    HANDLE hCon;


public :

	Board()
	{
		memset(board, 0,sizeof(board));
        for (int i = 0; i < N; i++)
            numbers.push_back(i+1);
        unsigned seed = time(NULL);
        mistakes = 0;
        hCon = NULL;

    shuffle(numbers.begin(),numbers.end(), default_random_engine(seed));


	}

    ~Board()
    {
        CloseHandle(hCon);

    }
    void show()
    {
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hCon, &csbi);
        WORD wAttributes;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (board[i][j] == 0)
                {
                    cout << "[";
                    cout << 0;
                    cout << "]";
                }
                else
                {
                    stringstream temp;
                    string aux;
                    temp <<i<< ',' << j;
                    temp >> aux;
                    temp.clear();
                    cout << "[";
                    if (coordinates.find(aux) != coordinates.end())
                    {
                        wAttributes = FOREGROUND_GREEN;
                        SetConsoleTextAttribute(hCon, wAttributes);
                        cout << board[i][j];
                        SetConsoleTextAttribute(hCon, csbi.wAttributes);
                        cout << "]";
                    }
                    else if(coordinates.find(aux)==coordinates.end())
                    {
                        wAttributes = FOREGROUND_BLUE;
                        SetConsoleTextAttribute(hCon, wAttributes);
                        cout << board[i][j];
                        SetConsoleTextAttribute(hCon, csbi.wAttributes);
                        cout << "]";
                    }
                }

                if ((j + 1) % 3 == 0) cout << "  ";    // Separates the Columns into Groups of Three
                if (j == 8) cout << endl;            // Once j (horizontal iterator) is 9, newline
                if (j == 8 && (i + 1) % 3 == 0) cout << endl; // Separates the Rows into Groups of Three
            }
        }
    }

    //Function used for finding empty spaces on the game board.
    bool FindUnassignedLocation(int &row, int &col)
    {
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                if (board[row][col] == EMPTY)
                    return true;
            }
        }

        return false;
    }
    //Checks row
    bool UsedInRow(int row, int num)
    {
        for (int col = 0; col < N; col++)
        {
            if (board[row][col] == num)
                return true;
        }

        return false;
    }
    //Checks column
    bool UsedInColumn( int col, int num)
    {

        for (int row = 0; row < N; row++)
        {
            if (board[row][col] == num)
                return true;
        }
        return false;
    }
    //Checks 3*3 square
    bool UsedInBox( int boxStartRow, int boxStartCol, int num)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board[row + boxStartRow][col + boxStartCol] == num)
                    return true;
            }
        }

        return false;
    }

    bool isSafe( int row, int col, int num)
    {
        return !UsedInRow(row, num) && !UsedInColumn( col, num) && !UsedInBox( row - row % 3, col - col % 3, num);
    }
    //Function that build the game board based on difficulty level selected.
    bool buildBoard()
    {    
        int row;
        int col;
        int number;
       
        if (!FindUnassignedLocation(row,col))
            return true;
        for (int i = 0; i < N; i++)
        {
            if (isSafe(row, col, numbers[i]))
            {
                this->board[row][col] = numbers[i];
                if (buildBoard())
                {
                    solution[row][col] = board[row][col];
                    return true;
                }
                this->board[row][col] = EMPTY;
                this->solution[row][col] = EMPTY;
            }
        }
        return false;
    }

    //Function that deletes cells based on diff selected
    void deleteCells(string diff)
    {
        if (diff == "Easy")//In this case we have between 36 and 46 clues.
        {
            srand(time(NULL));
            int cnt = rand() % 10 + 36;
            cout << cnt << endl;
            while (cnt > 0)//The cells we remove are chosen at random 
            {

                int row = rand() % 9;
                int col = rand() % 9;
                if (board[row][col] == EMPTY)
                    continue;

                board[row][col] = EMPTY;

                cnt--;
            }
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                {
                    if (board[i][j] != EMPTY)
                    {
                        stringstream buffer;
                        string temp;
                        buffer << i << ',' << j;
                        buffer >> temp;
                        coordinates.insert(temp);
                        buffer.clear();



                    }

                }
        }
            if (diff == "Medium")
            {
                srand(time(NULL));
                int cnt = rand() % 5+46;
                while (cnt > 0)//The cells we remove are chosen at random 
                {

                    int row = rand() % 8;
                    int col = rand() % 8;
                    if (board[row][col] == EMPTY)
                        continue;

                    board[row][col] = EMPTY;

                    cnt--;
                }

                for(int i=0;i<N;i++)
                    for (int j = 0; j < N; j++)
                    {
                        if (board[i][j] != EMPTY)
                        {
                            stringstream buffer;
                            string temp;
                            buffer << i << ',' << j;
                            buffer >> temp;
                            coordinates.insert(temp);
                            buffer.clear();



                        }

                    }


            }

       if(diff=="Hard")
       {
           srand(time(NULL));
           int cnt = rand() % 3+50;
           while (cnt > 0)//The cells we remove are chosen at random 
           {

               int row = rand() % 8;
               int col = rand() % 8;
               if (board[row][col] == EMPTY)
                   continue;

               board[row][col] = EMPTY;

               cnt--;
           }
           for (int i = 0; i < N; i++)
               for (int j = 0; j < N; j++)
               {
                   if (board[i][j] != EMPTY)
                   {
                       stringstream buffer;
                       string temp;
                       buffer << i << ',' << j;
                       buffer >> temp;
                       coordinates.insert(temp);
                       buffer.clear();



                   }

               }

        }

    
    }
    //Used to complete cells in the puzzle
    void playMove(int row, int col, int number)
    {
        if (number > 9 || number < 1)
        {
            mistakes++;
            cout << "Please insert a valid value (Between 1 and 9). " << endl;
            return;
        }
        if (!isSafe(row, col, number))
        {
            mistakes++;
            cout << "Value is not  allowed." << endl;
            return;
        }
        stringstream buffer;
        string temp;
        buffer << row << ',' << col;
        buffer >> temp;
        if (coordinates.find(temp) != coordinates.end())
        {
            mistakes++;
            cout << "Move is not allowed, cell was already written ." << endl;
        }
       this->board[row][col] = number;
    }
//Checks for the win condition
    bool checkWin()
    {
        for(int i=0;i<N;i++)
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] == EMPTY)                
                    return false;

            }
        return true;


    }
    //Prints the puzzle solution
    void showSolution()
    {
        for(int i=0;i<N;i++)
            for (int j = 0; j < N; j++)
            {
                cout << "[";
                cout << solution[i][j];
                cout << "]";

                if ((j + 1) % 3 == 0) cout << "  ";   
                if (j == 8) cout << endl;            
                if (j == 8 && (i + 1) % 3 == 0) cout << endl;

            }


    }
    //Checks the number of mistakes of the user.
    int checkMistakes() {

        return mistakes;
    }
    //Sets mistakes count to 0
    void setMistakes()
    {

        mistakes = 0;
    }

};