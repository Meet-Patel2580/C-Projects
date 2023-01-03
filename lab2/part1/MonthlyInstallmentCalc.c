/* 
// Meet Patel
// Jan 19th, 2021
// APS105 Winter 2022 Lab 2 Part 1
// program that outputs monthly payment required to purchase a car 
// given the purchase price, down payment, finance term, and monthly interest rate
*/

#include <stdio.h>
#include <math.h>

int main (){

    int price, downPayment, term;
    double interestRate, monthlyPayment;
     
    printf("Enter the purchase price P: ");
    scanf("%d", &price);

    printf("Enter the amount of down payment D: ");
    scanf("%d", &downPayment);

    printf("Enter the finance term (in months): ");
    scanf("%d", &term);

    printf("Enter the monthly interest rate (in percent): ");
    scanf("%lf", &interestRate);

    monthlyPayment = ((price-downPayment) * interestRate/100 * pow((1+interestRate/100), term))/(pow((1+interestRate/100),term)-1);

    printf("The monthly payment is: %.2lf", monthlyPayment);

    return 0;
}
