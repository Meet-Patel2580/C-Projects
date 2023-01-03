/* 
// Meet Patel
// Feb 5th, 2022
// APS105 Winter 2022 Lab 4 Part 1
// program that outputs n amount of rows from pascals triangle
*/

#include <stdio.h>

    void triangle();
    int choose();
    int factorial();

int main(){

    int rows;

    do {
        printf("Enter the number of rows: ");
        scanf("%d", &rows);

        if (rows >= 0) {
            triangle(rows);
        }
    } while (rows >= 0);

    return 0;
}

//function for printing pascals triangle based on the amount of rows 
void triangle (int numRows){

    int spaces = (numRows-1);
    int num = 1;
    int count = 0;

    //prints each row at a time
    for (int row = 0; row <= numRows-1; row++){

        //adds spaces before the first term of each row
        for(int i = row ; i<spaces; i++){
                printf("   ");
            }

        //prints the terms within each row
        for (int term = row ; term >= 0; term--){

            num = choose(row, term);
            printf("%d", num);

            //to calculate amount of digits in the current term
            do {
                num /= 10;
                ++count;
            } while (num != 0);

            //creates spacing according to the length of the term
            for (int j = 0; j <= (5-count); j++){
                printf(" ");
            }
            count = 0;
        }
        printf("\n");
    }   
}

//function that takes two integer values and performs the nCr operation 
// nCr = n!/(r!(n-r)!)
//outputs the result
int choose (int n, int r){

    int nChooseR = (factorial(n) / (factorial(r) * factorial(n - r)));

    return nChooseR;
}

//function that takes an integer and returns the factorial of that number
int factorial (int n){

    int nFactorial = 1;

    for(int i = n ; i > 1; i--){
        nFactorial *= i;
    }
    return nFactorial;
}
