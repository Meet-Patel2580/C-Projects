/* 
// Meet Patel
// Feb 14th, 2022
// APS105 Winter 2022 Lab 5 Part 3
// this program contains a fucntion that finds the longest common sequence of values between two arrays.
*/

#include <stdio.h>

void longestMutualSequence(int firstArr[], int secondArr[], int sizeA, int sizeB){

    int count = 0;
    int previousLength = 0;
    int indexStart = -1;
    int indexEnd = -1;
    int index = -1;
    int firstCommonValue = 1;

    // loops through values of first array
    for(int i = 0; i < sizeA; i++){

        //loops through values of second array
        for(int j = 0; j < sizeB; j++)

            // checks whether current value in first array is equal to current value in second array
            if(firstArr[i] == secondArr[j]){
                count = 1;

                // once a common value is found, this loop goes through both arrays in single increments from the current index.
                for(int f = i + 1, s = j + 1; f < sizeA && j < sizeB; f++, s++){

                    // checks whether current value in first array is equal to current value in second array
                    if(firstArr[f] == secondArr[s]){
                        count++;

                        // checks if current sequence is longer than any previous sequence
                        if(previousLength < count){
                            previousLength = count; // stores length of longest common sequence 
                            indexEnd = f; // end index of sequence 
                            indexStart = f - previousLength + 1; //beginning index of sequence
                        }
                    }
                    else{
                        count = 1; //reset counter 

                        if(firstCommonValue == 1){
                            index = i;  // index of first single common value (in case there are no sequences larger than 1 value)
                            firstCommonValue = 0 ;
                        }
                        break;
                    }
                }
            }
            else{
                count = 0;
            }
            
    }

    printf("Longest common sequence is ");

    if(indexStart == -1 && indexEnd == -1 ){
        printf("%d.", firstArr[index]); // prints out single commmon value if no sequence exists
    }
    else{
        // prints out values of the array within the longest sequence using the start and end index
        for( int i = indexStart; i<= indexEnd; i++){
            if (i == indexEnd){
                printf("%d.", firstArr[i]);
            }
            else{
                printf("%d, ", firstArr[i]);
            }
        }
    }

}

int main(){

    int a[] = {1,1,1,1,5,6,7,8,9};
    int b[] = {1,1,1,1,1,2,38,4,5,69,7};

    longestMutualSequence(a,b,9,11);


}
