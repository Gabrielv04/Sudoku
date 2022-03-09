#pragma once
#include<iostream>
#include<string>
#include"Board.h"

using namespace std;


class Player
{
    string name;
    bool win = false;

public:

    void setName(string name)
    {
        this->name=name;


    }
    void getName()
    {


        cout << this->name << endl;
    }
    void setWin(bool win)
    {
        this->win = win;
    }
    bool getWin()
    {
        return win;

    }




};
