

#include <stdio.h>
#include <stdbool.h>

bool checkRowCol(const int Size, int sudoko [Size][Size], int currentRow, int currentCol, int trial){

    bool isPossible = 1;

    for(int i = 0; i < 4; i++){
        if(sudoko[currentRow][i] == trial){
            isPossible = 0;
        }
    }

    for(int j = 0; j < 4; j++){
        if(sudoko[j][currentCol] == trial){
            isPossible = 0;
        }       
    }

    return isPossible;
}


void fillSudoko(const int Size, int sudoko [Size][Size]){

    for(int row = 0; row < Size; row++){
        for(int col = 0; col < Size; col++){
            if(sudoko[row][col]==0){
                for(int trial = 1; trial<=4; trial++){
                    if(checkRowCol(Size, sudoko, row, col, trial)){
                        sudoko[row][col] = trial;
                    }
                }
            }
        }
    }
}






int main(){

    
}
