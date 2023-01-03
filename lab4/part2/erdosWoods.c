/* 
// Meet Patel
// Feb 5th, 2022
// APS105 Winter 2022 Lab 4 Part 1
// In number theory, a positive integer k is said to be an Erdos–Woods number if there exists a positive
// integer a such that each of the consecutive integers a + i for 0 < i < k shares at least one prime
// factor with either a or a + k. In other words, if for a k there is an a such that each evaluation of
// gcd(a, a + i) > 1 or gcd(a + k, a + i) > 1 returns true, then k is an Erdos–Woods number.
// This program takes in the range of 'a' and 'k' from the user and goes through the range of k values to determine the Erdos-woods number 
// and then outputs the corresponding k and a values. 
// If an Erdos-woods number doesnt exist, the program will output that the Erdos-woods number was not found
*/

#include <stdio.h>
#include <stdbool.h>

void erdosWoodsNumber(int startA, int endA, int startK, int endK);

int main(){

    int kStart = 0;
    int kEnd = 0;
    int aStart = 0;
    int aEnd = 0;

    // following lines prompt user to enter the ranges for the 'k' and 'a' values 
    // If input is not valid, the user will be promtped again until valid input is entered.

    do{
    printf("Enter the number to start searching for k (> 2, inclusive): ");
    scanf("%d", &kStart);
    } while (kStart <= 2);

    do{
    printf("Enter the number to stop searching for k (inclusive): ");
    scanf("%d", &kEnd);
    } while (kEnd < kStart);

    do{
    printf("Enter the number to start searching for a (> 0, inclusive): ");
    scanf("%d", &aStart);
    } while (aStart <= 0);

    do{
    printf("Enter the number to stop searching for a (inclusive): ");
    scanf("%d", &aEnd);
    } while (aEnd < aStart);

    erdosWoodsNumber(aStart, aEnd, kStart, kEnd);

    return 0;
}

// function that takes in two integers and returns the the greatest common divisor 
int gcd(int a, int b){

    if (a == 0){
        return b;
    }

    return gcd(b % a, a);
}


// function that takes in 4 integer values for the start and end values of 'a' and 'k' and then prints the erdos-woods number and corresponding 'a' value.
// Prints the current 'k' value that is being tested as well
void erdosWoodsNumber(int startA, int endA, int startK, int endK){

    int erdosWoodsNum = 0;
    int aValue = 0;
    int counter = 0;

    // loops through K values within the range 
    for (int k = startK; k <= endK; k++){

        // prints the current k value that is being tested 
        printf("Trying k = %d...\n", k);

        // loops through a values within the range
        for (int a = startA; a <= endA; a++){

            // loops through i values : (0 < i < K)
            for (int i = 1; i < k; i++){
                if ((gcd(a,a + i) > 1) || (gcd(a + k, a + i) > 1)){
                    counter ++;
                }
            }

            // When the condition above is true for all i values where (0 < i < K), the current K 
            // is an erdos-woods number and the current 'a' is the corresponding 'a' value.
            if (counter == (k - 1)){

                erdosWoodsNum = k;
                aValue = a;

                // ensures that loop ends after erdos-woods number is found 
                k = endK+1; 
            }
            counter = 0; 
        }
    }

    // Prints the erdos-woods number and corresponding 'a' value if an erdos-woods number exists.
    // Otherwise "Erdos-Woods number not found." is printed.
    if (erdosWoodsNum != 0){
        printf("Erdos-Woods number: %d\n", erdosWoodsNum);
        printf("a = %d", aValue);
    }
    else {
        printf("Erdos-Woods number not found.");
    }
}

