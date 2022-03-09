#pragma once
#include<Windows.h>
#include"Board.h"
#include"Player.h"
#include<iostream>
#include<string>
#include<sstream>




using namespace std;

int main()
{
	Board b;
	Player P;
	string temp;
	COORD cursor = { 55,10 };
	
	b.buildBoard();

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << " Sudoku Puzzle " << endl;
	cursor = { 45,11 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << "The rules of the game are as follows : " << endl;
	cursor = { 15,12 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << "1. Each number in the range of 1 to 9 should appear only once on a single row. " << endl;
	cursor = { 15,13 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << "2. Each digit in the range of 1 to 9 should appear only once on a single column. " << endl;
	cursor = { 15,14 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << "3. Upong dividing the board into 9 equal squares , each digit should appear only once in every square . " << endl;
	cursor = { 15,17 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
	cout << "Please  insert your name :  ";

	cin >> temp;
	P.setName(temp);
	short int i = 18;
	while (true)
	{
		cursor = { 15,i };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
		cout << "Please select your difficulty level : (Easy,Medium,Hard)  ";
		cin >> temp;
		if (temp == "Easy" || temp == "Medium" || temp == "Hard")
		{
			b.deleteCells(temp);
			break;
		}
		else
		{ 
			cursor = { 15,i + 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
			cout << "Please insert a valid option(Easy,Medium,Hard)" << endl;
			i++;
		}
	}
	int nr;
	int row;
	int col;

	cursor = { 35,5 };
	while (P.getWin() == false)
	{
		char aux;
		system("CLS");
		b.show();
		cout << "Please insert your next number :" << endl;
		cin >> nr;
		cout << "Please insert row number : " << endl;
		cin >> row;
		cout << "Please insert column number :" << endl;
		cin >> col;
		b.playMove(row-1, col-1, nr);
		if (b.checkMistakes() >= 3)
		{
			char ans;
			cout << "Press S to forfeit the game and see the solution , R to reset mistake count or anything else to continue : ";
			cin >> ans;
			cout << endl;
			if (ans == 'S')
			{
				P.setWin(false);
				break;
			}
			if (ans == 'R') b.setMistakes();

		}
		P.setWin(b.checkWin());
		cin.ignore();
		cout << "Press Enter to continue :  ";
		cin.get();
	}
	system("CLS");
	if (P.getWin() == true)
	{
		b.show();
		cout << "Congratulations you have won !" << endl;

	}
	else if (P.getWin() == false)
	{
		
		b.showSolution();
		cout << "Game Over." << endl;
	}
	return 0;
}
