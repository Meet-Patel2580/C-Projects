/*
// Meet Patel
// Jan 13th, 2021
// APS105 Winter 2022 Lab 1 Part 3
// A C program that converts metres to yards, feet and inches.
*/

#include <stdio.h>

int main(){

    double distanceInMetres;
    double inchRemainder, totalInches;
    int yards,feet,inches;
    const double conversionRate = 0.0254;

    printf("Please provide a distance in metres: ");
    scanf("%lf", &distanceInMetres);

    totalInches = distanceInMetres/conversionRate;
    inches = totalInches/1;
    inchRemainder = totalInches-inches;

    yards = inches/36;
    feet = (inches%36)/12;
    inches = (inches%36)%12;

    printf("%d yards, %d feet, %d inches, and %.2lf inch remainder", yards,feet,inches,inchRemainder);

    return 0;

}


