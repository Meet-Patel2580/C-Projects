/* 
// Meet Patel
// Jan 24th, 2021
// APS105 Winter 2022 Lab 3 Part 2
// program that outputs a triangle made with the '*' character with n number of rows based on the user input 
*/

#include <stdio.h>

int main()
{
    int numRows;

    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &numRows);

    // loop goes through one row at a time
    for (int i = 1; i <= numRows; i++)
    {
        // loop to print leading spaces in each line
        for (int spaces = 1; spaces <= numRows - i; spaces++){
            printf(" ");
        }
        // loop to print *'s and inner spaces within triangle
        for (int j = 1; j <= i * 2 - 1; j++){
            
            if (j == 1 || (j == i * 2 - 1) || i == numRows){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;

}
