/*
// Meet Patel
// Jan 13th, 2021
// APS105 Winter 2022 Lab 1 Part 2
//
// Program that reads in the daily rate, number of rental days,
// and prints the eligible free rental days and the total rental
// charge tax inclusive.
//
// Note: Every 4-day block in a rental period is counted as 3 days.
// Assumption: All input values are valid.
//
*/

#include <stdio.h>
int main(){

    double dailyRate, totalCharge;
    int rentalPeriod;
    int freeDays;
    const double HST = 1.13;

    printf("Enter the daily rate: ");
    scanf("%lf", &dailyRate);

    printf("Enter the rental period (in days): ");
    scanf("%d", &rentalPeriod);

    freeDays = rentalPeriod/4;
    totalCharge = (rentalPeriod - freeDays) * dailyRate * HST;

    printf("Your total free day(s) in this rental is: %d\n", freeDays);
    printf("Your total charge including taxes is: %.2lf\n", totalCharge);

}
