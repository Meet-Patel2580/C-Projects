//
// Author: Meet Patel
//

#include "reversi.h"
#include <stdio.h>

// Prints the board with coordinates 
void printBoard(char board[][26], int n) {

  char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  
  printf("  ");

  //prints letters at the top
  for (int l = 0; l < n; l++){
    printf("%c",letters[l]);
  }

  printf("\n");

  // Prints letters on the left as well as the board itself
  for (int row = 0; row < n; row++){
   
    printf("%c ",letters[row]);

    for (int col = 0; col < n; col++){
      printf("%c", board[row][col]);
    }

    printf("\n");
  }
}

// Checks whether the current position is within the bounds of the board
bool positionInBounds(int n, int row, int col) {
  if(row < n && row >= 0 && col < n && col >= 0){
    return 1;
  }
  else{
    return 0;
  }
}

// Checks whether a move is legal in a specified direction
// If the same colored piece lies in the direction specified, function returns true
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {

  char oppositeColour;
  bool isColorPresent = 0;
  int r = row + deltaRow;
  int c = col + deltaCol;

  if(colour == 'W'){
    oppositeColour = 'B';
  }
  else{
    oppositeColour = 'W';
  }

  if(board[r][c] == oppositeColour){
    r += deltaRow;
    c += deltaCol;
    while(board[r][c] != 'U' && positionInBounds(n, r, c)){
        if(board[r][c] == colour){
          return 1;
        }
        else if(board[r][c] ==  oppositeColour){
           r += deltaRow;
           c += deltaCol;
        }
    }
  }
  return isColorPresent;
}

// Checks whether move input by the user is valid or not
bool checkMoveValidity(int row, int col, char color, int validW[26][26], int validB[26][26]){
  if(color == 'W'){
    if(validW[row][col] == 1){
      return 1;
    }
    else{
      return 0;
    }
  }
  else if(color == 'B'){
    if(validB[row][col] == 1){
      return 1;
    }
    else{
      return 0;
    }
  }
  else{
    return 0;
  }
}

void assignMoves(char board[][26], int dimension, int rowDir[], int colDir[], int validMovesW[][26], int validMovesB[][26], char color){

  int rowD;
  int colD;

    for (int rows = 0; rows < dimension; rows++){
      for (int cols = 0; cols < dimension; cols++){
        if (board[rows][cols] == 'U'){
            for(int dir = 0; dir < 8 && positionInBounds(dimension, rows, cols); dir++){
                rowD = rowDir[dir];
                colD = colDir[dir];
                if(checkLegalInDirection(board,dimension,rows,cols,color,rowD,colD)){
                    //printf("%c%c\n",letters[rows],letters[cols]);
                    if(color == 'W'){
                        validMovesW[rows][cols] = 1;
                        break;
                    }
                    if(color == 'B'){
                        validMovesB[rows][cols] = 1;
                        break;
                    }
                }
            }
        }
      }
    }
}

//places move if valid
bool placeMove(char board[][26], int n, char colour, int row, int col, int validMovesW[][26], int validMovesB[][26]){
    
    int rowDir[] = {1,1,0,-1,-1,-1,0,1};
    int colDir[] = {0,-1,-1,-1,0,1,1,1};
    int r;
    int c;
    int dir = 0;
    int rowD;
    int colD;

    if(checkMoveValidity(row, col, colour, validMovesW, validMovesB)){
         // printf("Valid move.\n");

          for(dir = 0; dir < 8; dir++){
            rowD = rowDir[dir];
            colD = colDir[dir];
              if(checkLegalInDirection(board,n,row,col,colour,rowD,colD)){
                for (r = row+rowD,c = col+colD; positionInBounds(n, r, c) && board[r][c] != colour; r = r + rowD, c = c + colD){
                  board[r][c] = colour;
                }           
              }                  
          }
          board[row][col] = colour;
        }
    else{
        return false;
    }
    return true;
}

void highestScoreLoc(char board[][26], int n, char colour, int validMovesW[][26], int validMovesB[][26], int location[]){
   
    int rowDir[] = {1,1,0,-1,-1,-1,0,1};
    int colDir[] = {0,-1,-1,-1,0,1,1,1};
    int r;
    int c;
    int dir = 0;
    int rowD;
    int colD;
    int scoreGrid[26][26]={0};
    int largestScore = 0;

    //assignMoves(board,n,rowDir,colDir,validMovesW,validMovesB,colour);

    for (int row = 0; row < n; row++){
      for (int col = 0; col < n; col++){
        if(checkMoveValidity(row, col, colour, validMovesW, validMovesB)){
            for(dir = 0; dir < 8; dir++){
                rowD = rowDir[dir];
                colD = colDir[dir];
                if(checkLegalInDirection(board,n,row,col,colour,rowD,colD)){
                    for (r = row+rowD,c = col+colD; positionInBounds(n, r, c) && board[r][c] != colour; r = r + rowD, c = c + colD){
                        scoreGrid[row][col] += 1 ;
                    }           
                }           
            }
        }
        if(scoreGrid[row][col] > largestScore){
            largestScore = scoreGrid[row][col];
            location[0] = row;
            location[1] = col; 
        }
      }
    }
}

void computerMove(char board[][26], int n, char color, int location[], int validW[][26], int validB[][26]){

    int row = location[0];
    int col = location[1];

    char r = 97 + row;
    char c = 97 + col;

    placeMove(board, n, color, row,col, validW, validB);
    printf("Computer places %c at %c%c.\n", color,r,c);
}

bool availableMove(int n, int valid[][26]){
  for(int row = 0; row < n; row++){
    for(int col = 0; col < n; col++){
      if(valid[row][col] == 1){
        return 1;
      }
    }
  }
  return 0;
}

void resetValidArrays(int n, int validW[][26], int validB[][26]){
  for(int row = 0; row < n; row++){
    for(int col = 0; col < n; col++){
      validB[row][col] = 0;
      validW[row][col] = 0;
      }
    }  
}

void printWinner(char board[][26], int n){
  int w = 0,b = 0;

  for(int row = 0; row < n; row++){
    for(int col = 0; col < n; col++){
      if(board[row][col] == 'W'){
        w++;
      }
      if(board[row][col] == 'B'){
        b++;
      }
    }
  }
  if(b>w){
    printf("B player wins.");
  }  
  else if(w>b){
    printf("W player wins.");
  }
  else{
    printf("Draw!");
  }
}

bool isBoardFull(char board[][26], int n){
  for(int row = 0; row < n; row++){
    for(int col = 0; col < n; col++){
      if(board[row][col] == 'U'){
        return 0;
      }
    }
  }
  return 1;
}

int main(void) {

  int dimension = 0;   
  char humanColor = 'B';
  char computerColor = '\0';

  printf("Enter the board dimension: ");
  scanf("%d", &dimension);

  printf("Computer plays (B/W): ");
  scanf(" %c", &computerColor);

  char board[dimension][26];

  // Creating initial board setup 
  for (int row = 0; row < dimension; row++){
    for (int col = 0; col < dimension; col++){
      if (((row == dimension/2-1) && (col == dimension/2-1))|| ((row == dimension/2) && (col == dimension/2))){
        board[row][col] = 'W';
      }
      else if ((row == dimension/2 && col == dimension/2-1) || (row == dimension/2-1 && col == dimension/2)){
        board[row][col] = 'B';
      }
      else{
        board[row][col] = 'U';
      }
    }
  }
  if(computerColor == 'B'){
      humanColor = 'W';
  }

  printBoard(board, dimension);


  int rowNum, colNum;
  int rowDir[] = {1,1,0,-1,-1,-1,0,1};
  int colDir[] = {0,-1,-1,-1,0,1,1,1};
  int validMovesW[26][26]={0};
  int validMovesB[26][26]={0};
  int location[2] = {0};
  char row,col;
  bool game = 1;

if(computerColor == 'W'){
    do{
      assignMoves(board,dimension, rowDir,colDir,validMovesW, validMovesB,humanColor);
      assignMoves(board,dimension,rowDir,colDir,validMovesW, validMovesB,computerColor);
      if(availableMove(dimension, validMovesB)){
        printf("Enter move for colour B (RowCol): ");
        scanf(" %c%c", &row, &col);
        rowNum = 26 - ('z' - row+1);
        colNum =  26 - ('z' - col+1);
        if(checkMoveValidity(rowNum,colNum,humanColor,validMovesW,validMovesB)){
          placeMove(board,dimension,humanColor,rowNum, colNum,validMovesW,validMovesB);
          printBoard(board, dimension);
        }
        else{
          printf("Invalid move.\n");
          game = 0;
          break;
        }
      }
      else if(availableMove(dimension, validMovesB)){
        printf("B player has no valid move.\n");
      }
      else{
        game = 0;
        break;
      }
      assignMoves(board,dimension,rowDir,colDir,validMovesW, validMovesB,computerColor);
      if(availableMove(dimension, validMovesW)){
        highestScoreLoc(board,dimension,computerColor,validMovesW,validMovesB,location);
        computerMove(board,dimension,computerColor,location,validMovesW,validMovesB);
        printBoard(board,dimension);
      }
      else if(isBoardFull(board,dimension)){
        game = 0;
      }
      else{
        printf("W player has no valid move.\n");
      }
      

      resetValidArrays(dimension,validMovesW,validMovesB);

    }while(game == 1);

}
else{
    do{
      assignMoves(board,dimension, rowDir,colDir,validMovesW, validMovesB,humanColor);
      assignMoves(board,dimension,rowDir,colDir,validMovesW, validMovesB,computerColor);

      if(availableMove(dimension, validMovesB)){
        highestScoreLoc(board,dimension,computerColor,validMovesW,validMovesB,location);
        computerMove(board,dimension,computerColor,location,validMovesW,validMovesB);
        printBoard(board,dimension);
      }
      else if(availableMove(dimension, validMovesB)){
        printf("B player has no valid move.\n");
      }
      else{
        game = 0;
        break;
      }

      assignMoves(board,dimension, rowDir,colDir,validMovesW, validMovesB,humanColor);
      if(availableMove(dimension, validMovesW)){
        printf("Enter move for colour W (RowCol): ");
        scanf(" %c%c", &row, &col);
        rowNum = 26 - ('z' - row+1);
        colNum =  26 - ('z' - col+1);
        if(checkMoveValidity(rowNum,colNum,humanColor,validMovesW,validMovesB)){
          placeMove(board,dimension,humanColor,rowNum, colNum,validMovesW,validMovesB);
          printBoard(board, dimension);
        }
        else{
          printf("Invalid move.\n");
          game = 0;
          break;
        }
      }
      else if(isBoardFull(board,dimension)){
        game = 0;
      }
      else{
        printf("W player has no valid move.\n");
      }

      resetValidArrays(dimension,validMovesW,validMovesB);

    }while(game == 1);
}

printWinner(board, dimension);

}
