/* 
// Meet Patel
// Feb 14th, 2022
// APS105 Winter 2022 Lab 5 Part 1
// program that receives two arrays as parameters passed and returns
// the median of the values stored in these two arrays
*/

#include <stdio.h>

double median(int a[], int b[], int sizeA, int sizeB);

int main(){

    double medianNum =0;
    int a[] = {1,1,2,12,100};
    int b[] = {3,3,5,7,88};

    medianNum = median(a,b,5,5);

    printf("\n%lf",medianNum);
}

double median(int a[], int b[], int sizeA, int sizeB){ 

    double medianValue = 0;
    int totalSize = sizeA + sizeB;
    int combine[totalSize];

    int index = 0;
    int indexA = 0;
    int indexB = 0;
  
    // loops through arrray a and array b
    while(indexA<sizeA && indexB<sizeB){

        // checks whether current value from array a is greater than the current value from array b
        if(a[indexA] > b[indexB]){

            // if the 'a' value is higher than the 'b' value the b value is stored in the current index of the combined array
            combine[index] = b[indexB]; 
            indexB++;
        }
        else{
            //otherwise the 'a' value is stored in the current index of combined array
            combine[index] = a[indexA];
            indexA++;
        }
        index++; //increment to next index in the combine array
    }

    // fills in remaining 'a' values into the combined aray
    while (indexA < sizeA){
        combine[index] = a[indexA];
        index++;
        indexA++;
    }

    // fills in remaining 'b' values into the combines array 
    while(indexB < sizeB){
        combine[index] = b[indexB];
        index++;
        indexB++;
    }

    // calculates median based on whether the combined array has an even or odd amount of values.
    if((totalSize%2) != 0){
        medianValue  = combine[totalSize/2];
    }
    else{
        medianValue = (combine[(totalSize-1)/2]+combine[totalSize/2])/2.0; 
    }

    for(int i =0;i<totalSize;i++){
        printf("%d, ", combine[i]);
    }


    return medianValue;
}

/*double median2(int a[], int b[], int sizeA, int sizeB){

    int size = sizeA+sizeB;
    int combine[size];
    double medianValue = 0;

    for(int j = 0 ; j < 100 ; j++)
        combine[j] = 0;  //This will make all ZERO

    int count = 0;
    int index = 0;

    for (int i = 0; i < size ; i++ ){
        for (int ai = 0; ai < sizeA; ai++){
            for (int bi = 0; bi < sizeB; bi++){
                if (a[ai] < b[bi]){
                    count++;
                }
                else{
                    index++;
                }
            }
            if (count == sizeB){
                combine[i] = a[ai];
            }
            else{
                combine[ai + (sizeB - index)] = a[ai]; 
            }
        }
    }

    for (int i = 0; i < size ; i++ ){
        for (int bi = 0; bi < sizeB; bi++){
            if (combine[i] == 0){
                combine[i] =b[bi];
            }
        }
    }

    if ((size%2) != 0){
        medianValue = combine[size/2+1];
    }
    else{
        medianValue = (combine[size/2] + combine[size/2+1])/2;
    }
    return medianValue;
}
*/

