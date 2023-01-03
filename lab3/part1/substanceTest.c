/* 
// Meet Patel
// Jan 24th, 2021
// APS105 Winter 2022 Lab 3 Part 1
// program that outputs substance type based on boiling point and threshold value input by user
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
   int threshold = 0;
   int boilingPoint = 0;

   //boiling points 
   const int WATER = 100;
   const int MERCURY = 357;
   const int COPPER = 1187;
   const int SILVER = 2193;
   const int GOLD = 2660;

   //user input for the threshold in celsius
   printf("Enter the threshold in Celsius: ");
   scanf("%d", &threshold);

   //user input for the observed boiling point in celsius
   printf("Enter the observed boiling point in Celsius: ");
   scanf("%d", &boilingPoint);

   //prints substance corresponding to the boiling point input by user
   if (abs(boilingPoint - GOLD) <= threshold){
      printf("The substance you tested is: Gold");
   }
   else if ((abs(boilingPoint - SILVER) <= threshold)){
      printf("The substance you tested is: Silver");
   }
   else if ((abs(boilingPoint - COPPER) <= threshold)){
      printf("The substance you tested is: Copper");
   }
   else if ((abs(boilingPoint - MERCURY) <= threshold)){
      printf("The substance you tested is: Mercury");
   }
   else if ((abs(boilingPoint - WATER) <= threshold)){
      printf("The substance you tested is: Water");
   }
   else{
      printf("Substance unknown.");
   }

   return 0;
}
