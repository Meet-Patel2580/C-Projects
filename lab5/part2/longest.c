/* 
// Meet Patel
// Feb 14th, 2022
// APS105 Winter 2022 Lab 5 Part 1
// program that receives two arrays as parameters passed and returns
// the median of the values stored in these two arrays
*/

#include <stdio.h>

void longestSequence(int a[], int sizeA);

int main(){



}

/* 
// Meet Patel
// Feb 19th, 2022
// APS105 Winter 2022 Lab 5 Part 1
// this program contains a fucntion that finds the longest sequence of increasing numbers
// in an array.
*/

void longestSequence(int a[], int sizeA)
{

    int previousNum = 0;
    int currentNum = 0;
    int count = 0;
    int previousLength = 0;
    int indexStart = 0;
    int indexEnd = 0;

    //loops through the array and compares adjacent values
    for (int i = 1; i < sizeA; i++){

        currentNum = a[i];
        previousNum = a[i - 1];

        // If the current value is greater than the previous value the counter increases by 1.
        if (currentNum > previousNum){

            count++;

            // Current length of sequence of increasing numbers is compared with the previous sequence 
            // If the current length is greater, this becomes stored as the new longest sequence
            if (previousLength < count){

                previousLength = count;
                indexEnd = i; // end index of sequence 
                indexStart = indexEnd - previousLength; //beginning index of sequence
            }
        }
        // counter is reset to zero when a sequence of increasing values ends
        else{
            count = 0;
        }
    }

    printf("Longest sequence is ");

    // prints out values of the array within the longest sequence using the start and end index
    for( int i = indexStart; i<= indexEnd; i++){
        if (i == indexEnd){
            printf("%d.", a[i]);
        }
        else{
            printf("%d, ", a[i]);
        }
    }
}
