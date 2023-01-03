#include <stdio.h>
#include <stdbool.h>

void search2D(char word[], int wordSize, const int Size, char grid[Size][Size]);
bool search1D(char word[], int wordSize, const int Size, char grid[Size][Size],int row, int col, int rowDir, int colDir);
void printFoundLocation(int rowDir, int colDir);

int main(){

}

bool search1D(char word[], int wordSize, const int Size, char grid[Size][Size],int row, int col, int rowDir, int colDir){

    int count = 0;
    int isLetter = 0;

    for(int letter = 1; letter < wordSize; letter++){
            if(grid[row+rowDir*letter][col+colDir*letter] == word[letter]){
                count++;
            }
    }
    if(count == wordSize - 1){
        isLetter = true;
    }
    return isLetter;
}

void printFoundLocation(int rowDir, int colDir){

    if(rowDir == 1 && colDir == 0){
        printf("south");
    }
    else if(rowDir == 1 && colDir == -1){
        printf("south-west");
    }
    else if(rowDir == 0 && colDir == -1){
        printf("west");
    }
    else if(rowDir == -1 && colDir == -1){
        printf("north-west");
    }
    else if(rowDir == -1 && colDir == 0){
        printf("north");
    }
    else if(rowDir == -1 && colDir == 1){
        printf("north-east");
    }
    else if(rowDir == 0 && colDir == 1){
        printf("east");
    }
    else if(rowDir == 1 && colDir == 1){
        printf("south-east");
    }

}


void search2D(char word[], int wordSize, const int Size, char grid[Size][Size]){

    int rowDir[] = {1,1,0,-1,-1,-1,0,1};
    int colDir[] = {0,-1,-1,-1,0,1,1,1};

    int rowD;
    int colD;

    bool end = 0;

    for(int row = 0; row < Size; row++){
        for(int col = 0; col < Size; col++){
            if(grid[row][col] == word[0]){
                for(int dir = 0; dir < 8; dir++){
                    rowD = rowDir[dir];
                    colD = colDir[dir];
                    if(search1D(word, wordSize, Size, grid, row, col, rowD, colD)){
                        printf("Word found at row %d and column %d in the ",row,col);
                        printFoundLocation(rowD, colD);
                        printf(" direction.");
                        return;
                    }
                    
                    
                }
            }
        }
    }
    printf("Word not found.");
}