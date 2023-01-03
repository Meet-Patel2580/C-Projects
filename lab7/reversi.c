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

void printMoves(char board[][26], int dimension, char letters[], int rowDir[], int colDir[], int validMovesW[][26], int validMovesB[][26]){

  int rowD;
  int colD;

  char color[] = {'W','B'};

  for(int x = 0; x<2; x++){
    if(x == 0){
      printf("Available moves for W:\n");
    }
    else{
      printf("Available moves for B:\n");
    }
    for (int rows = 0; rows < dimension; rows++){
      for (int cols = 0; cols < dimension; cols++){
        if (board[rows][cols] == 'U'){
            for(int dir = 0; dir < 8 && positionInBounds(dimension, rows, cols); dir++){
                rowD = rowDir[dir];
                colD = colDir[dir];
                if(checkLegalInDirection(board,dimension,rows,cols,color[x],rowD,colD)){
                    printf("%c%c\n",letters[rows],letters[cols]);
                    if(x == 0){
                        validMovesW[rows][cols] = 1;
                        break;
                    }
                    if(x == 1){
                        validMovesB[rows][cols] = 1;
                        break;
                    }
                }
            }
        }
      }
    }
  }

}


void placeMove(char board[][26], int n, char colour, int row, int col, int validMovesW[][26], int validMovesB[][26]){
    
    int rowDir[] = {1,1,0,-1,-1,-1,0,1};
    int colDir[] = {0,-1,-1,-1,0,1,1,1};
    int r;
    int c;
    int dir = 0;
    int rowD;
    int colD;

    if(checkMoveValidity(row, col, colour, validMovesW, validMovesB)){
          printf("Valid move.\n");

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
          printBoard(board, n);
        }
    else{
        printf("Invalid move.\n");
        printBoard(board,n);
    }
}



int main(void) {

  int dimension = 0;   

  printf("Enter the board dimension: ");
  scanf("%d", &dimension);

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

  printBoard(board, dimension); // Output initial setup of board

  printf("Enter board configuration:\n");

  char current = '\0';
  char previous = '\0';
  char previous2 = '\0';

  // Get configuration from user
  do{
    for(int i = 0; i <= 3; i++){
      scanf("%c", &current);
        if(i == 3){
          board[26 - ('z' - previous+1)][26 - ('z' - current+1)] = previous2;
        }
      previous2 = previous;
      previous = current;
    } 
  }while(current != '!' && previous != '!' && previous2 != '!');

  printBoard(board, dimension); // output configured board

  int rowDir[] = {1,1,0,-1,-1,-1,0,1};
  int colDir[] = {0,-1,-1,-1,0,1,1,1};

  char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


  int validMovesW[26][26] = {0};
  int validMovesB[26][26] = {0};

  printMoves(board, dimension, letters, rowDir, colDir, validMovesW, validMovesB);
  
  printf("Enter a move:\n");

  current, previous, previous2 = '\0';

  int rowNum;
  int colNum;

  // receives move from user and determines whether its valid or not 
  for(int i = 0; i <= 3; i++){
    scanf("%c", &current);
      if(i == 3){
        rowNum = 26 - ('z' - previous+1);
        colNum =  26 - ('z' - current+1);
        placeMove(board,dimension,previous2,rowNum, colNum, validMovesW,validMovesB);
      }
      previous2 = previous;
      previous = current;
    } 

  return 0;
}
