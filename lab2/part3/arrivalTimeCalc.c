/* 
// Meet Patel
// Jan 19th, 2021
// APS105 Winter 2022 Lab 2 Part 3
// program that outputs the arrival time in 24H format given the 
// current time as well as the travel time,
*/

#include <stdio.h>
#include <string.h>

int main()
{

    int currentHour, currentMin, tripHour, tripMin, hours, min, arrivalHour, arrivalMin;
    double tripTime;
    char arrivalDay[9];
    char same[9] = "same day";
    char next[9] = "next day";

    printf("Enter current time: ");
    scanf("%d %d", &currentHour, &currentMin);

    printf("Enter trip time: ");
    scanf("%lf", &tripTime);

    tripHour = tripTime / 1;
    tripMin = ((tripTime - tripHour) * 60) / 1;

    hours = (currentMin + tripMin) / 60;
    min = ((currentMin + tripMin) % 60) / 1;

    if ((currentHour + tripHour + hours) > 23){
        arrivalHour = (currentHour + tripHour + hours) % 24;
        strcpy(arrivalDay, next);
     }
    else{
        arrivalHour = currentHour + tripHour + hours;
        strcpy(arrivalDay, same);
    }

    arrivalMin = min;

    printf("\nCurrent time is %.2d:%.2d", currentHour, currentMin);
    printf("\nArrival Time is %s %.2d:%.2d", arrivalDay, arrivalHour, arrivalMin);

    return 0;
}
