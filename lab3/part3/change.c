/* 
// Meet Patel
// Jan 24th, 2021
// APS105 Winter 2022 Lab 3 Part 3
// program that outputs change for amounts less than a dollar. Outputs the amount of quarters,
// dimes, nickels and cents required to make up the amount with a minimum number of coins.
*/

#include <stdio.h>
#include <stdbool.h>

int main()
{
    int totalCents = 0;
    int cents = 0;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;

    bool valid = 1;

    //continuously prompts user for a value until invalid input is entered
    //invalid input: >= 100 or <= 0
    while (valid == 1)
    {
        //prompt user for # of cents 
        printf("Please give an amount in cents less than 100: ");
        scanf("%d", &totalCents);

        //checks validity of input
        if (totalCents < 100 && totalCents > 0){

            //calculations of the # of quarters, dimes, nickels and cents
            cents = totalCents;
            quarters = cents / 25;
            cents -= (quarters * 25);
            dimes = cents / 10;
            cents -= (dimes * 10);
            nickels = cents / 5;
            cents -= (nickels * 5);

            if (totalCents == 1){
                printf("%d cent:", totalCents);
            }
            else{
                printf("%d cents:", totalCents);
            }

            //Prints # of quarters
            if (quarters > 0){
                if (quarters == 1){
                    printf(" %d quarter", quarters);
                }
                else{
                    printf(" %d quarters", quarters);
                }
            }

            //Prints # of dimes as well as "and" and "," if necessary
            if (dimes > 0){
                if (quarters > 0){
                    if (cents == 0 && nickels == 0){
                        printf(" and");
                    }
                    else{
                        printf(",");
                    }
                }
                if (dimes == 1){
                    printf(" %d dime", dimes);
                }
                else{
                    printf(" %d dimes", dimes);
                }
            }

            //Prints # of nickels as well as "and" and "," if necessary
            if (nickels > 0){
                if (dimes > 0 || quarters > 0){
                    if (cents == 0 && (quarters > 0 && dimes > 0)){
                        printf(", and");
                    }
                    else if (cents == 0 && (quarters == 0 || dimes == 0)){
                        printf(" and");
                    }
                    else{
                        printf(",");
                    }
                }
                if (nickels == 1){
                    printf(" %d nickel", nickels);
                }
                else{
                    printf(" %d nickels", nickels);
                }
            }

            //Prints # of cents as well as "and" and "," if necessary
            if (cents > 0){
                if ((quarters > 0 && dimes > 0) || (quarters > 0 && nickels > 0) || (dimes > 0 && nickels > 0)){
                    printf(", and");
                }
                else if (((quarters == 0 && dimes == 0) || (quarters == 0 && nickels == 0) || 
                        (dimes == 0 && nickels == 0)) && (quarters != 0 || dimes != 0 || nickels != 0)){
                    printf(" and");
                }
                if (cents == 1){
                    printf(" %d cent", cents);
                }
                else{
                    printf(" %d cents", cents);
                }
            }
            printf(".\n");
        }
        //prints "invalid amount" message and sets valid = 0 to break out of loop
        else{
            printf("%d cents: invalid amount.", totalCents);
            valid = 0;
        }
    }
    return 0;
}
