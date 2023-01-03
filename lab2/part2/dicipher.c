/* 
// Meet Patel
// Jan 19th, 2021
// APS105 Winter 2022 Lab 2 Part 2
// program that outputs the real combination of a safe when 
// an encrypted key is entered.
*/

#include <stdio.h>

int main(){

    int a,b,c,d,encrypted;

    printf("Enter an encrypted 4-digit combination: ");
    scanf("%d", &encrypted);

    a = encrypted%10;
    b = 9 - (encrypted/100)%10;
    c = 9 - (encrypted/10)%10;
    d = encrypted/1000;
    
    printf("The real combination is: %d%d%d%d",a,b,c,d);
   
    return 0;
}
