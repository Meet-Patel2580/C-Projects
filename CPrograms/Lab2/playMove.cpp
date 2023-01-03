//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

#include <iostream>
#include <string>
using namespace std;

void playMove(GameState& game_state) {

    int row = game_state.get_selectedRow();
    int col = game_state.get_selectedColumn();
    bool turn = game_state.get_turn();
    int winCode = 0;

    int rowDir[] = {1,-1,-1,1,-1,1,0,0};
    int colDir[] = {-1,1,-1,1,0,0,-1,1};
    int rowD;
    int colD;
    int currentPlayer;
    int count = 1;
    int r ;
    int c ;
    int num;


    if(turn == 0){
        currentPlayer = -1;
    }
    else if (turn == 1)
    {
        currentPlayer = 1;
    }

    if(row < boardSize && row >= 0 && col < boardSize && col >= 0 && game_state.get_gameBoard(row,col) == Empty){
        game_state.set_moveValid(true);
    }
    else{
        game_state.set_moveValid(false);
        game_state.set_gameOver(false);
    }

    if(game_state.get_moveValid()){
        game_state.set_gameBoard(row, col, currentPlayer);
        game_state.set_turn(!turn);
    }

        for(int dir = 0; dir < 8; dir++){
            rowD = rowDir[dir];
            colD = colDir[dir];
            row = game_state.get_selectedRow();
            col = game_state.get_selectedColumn();
            r = row +rowD;
            c = col + colD;

                if((((row+rowD) >= 0 && (row+rowD) < boardSize) && ((row-rowD) >= 0 && (row-rowD) < boardSize)) && (((col+colD) >= 0 && (col+colD) < boardSize) && ((col-colD) >= 0 && (col-colD) < boardSize)) ){
                        if((game_state.get_gameBoard(row + rowD, col + colD) == currentPlayer) && (game_state.get_gameBoard(row - rowD, col - colD) == currentPlayer)){
                            count += 2;
                        }
                } 
                else{
                    while((game_state.get_gameBoard(r,c) == currentPlayer)){
                        count++;
                        r += rowD;
                        c += colD;
                    }
                }

                if(count == 3){

                    if ((row + col == 2) && (game_state.get_gameBoard(0,2) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,2) == game_state.get_gameBoard(2,0)))
                    {
                        winCode = 8;
                        game_state.set_gameOver(true);
                    }
                    else if ((row == col) && (game_state.get_gameBoard(0,0) == game_state.get_gameBoard(1,1) && game_state.get_gameBoard(0,0) == game_state.get_gameBoard(2,2)))
                    {
                        winCode = 7;
                        game_state.set_gameOver(true);
                    }
                    else if ((game_state.get_gameBoard(0,col) == game_state.get_gameBoard(1,col)) && (game_state.get_gameBoard(0,col) == game_state.get_gameBoard(2,col)))
                    {
                        if(col == 0){
                            winCode = 4;
                        }
                        else if (col == 1){
                            winCode = 5;
                        }
                        else {
                            winCode = 6;
                        }
                        game_state.set_gameOver(true);
                    }
                    else if ((game_state.get_gameBoard(row,0) == game_state.get_gameBoard(row,1)) && (game_state.get_gameBoard(row,0) == game_state.get_gameBoard(row,2)))
                    {
                        if(row == 0){
                            winCode = 1;
                        }
                        else if (row == 1){
                            winCode = 2;
                        }
                        else {
                            winCode = 3;
                        }
                        game_state.set_gameOver(true);
                    }
                    else{
                        winCode = 0;
                    }
              }
                else{
                    count = 1;
                }
                for(int i = 0; i < boardSize; i++){
                    for (int j = 0; j < boardSize; j++){
                        if (game_state.get_gameBoard(i,j) != Empty){
                            num++;
                        }
                    }
                }
                if(num == 9){
                    game_state.set_gameOver(true);
                }
                num = 0;
        }

    game_state.set_winCode(winCode);
}

/*
                    if(dir == 0 || dir == 1){
                        winCode = 8;
                    }
                    else if(dir == 2 || dir == 3){
                        winCode = 7;
                    }
                    else if(dir == 4 || dir == 5){
                        winCode = 4 + col;
                    }
                    else if(dir == 6 || dir == 7){
                        winCode = 1 + row;
                    }
*/
