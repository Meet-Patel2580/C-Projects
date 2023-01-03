//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

 // Constructor
    Triangle:: Triangle (string n, float a1, float a2, float a3, float b1, float b2, float b3): Shape(n,(a1+a2+a3)/3.0,(b1+b2+b3)/3.0){
        x1 = a1;
        x2 = a2;
        x3 = a3;
        y1 = b1;
        y2 = b2; 
        y3 = b3;
    }
    
    // Destructor
     Triangle:: ~Triangle(){
        
     }
    
    // Accessor
    float Triangle:: getx1() const{
        return x1;
    }       
    float Triangle:: getx2() const{
        return x2;
    }
    float Triangle:: getx3() const{
        return x3;
    }
    float Triangle:: gety1() const{
        return y1;
    }
    float Triangle:: gety2() const{
        return y2;
    }
    float Triangle:: gety3() const{
        return y3;
    }

    // Mutator
    void Triangle:: setx1(float a1){
        x1 = a1;
    }    
    void Triangle:: setx2(float a2){
        x2 = a2;
    }
    void Triangle:: setx3(float a3){
        x3 = a3;
    }
    void Triangle:: sety1(float b1){
        y1 = b1;
    }
    void Triangle:: sety2(float b2){
        y2 = b2;
    }
    void Triangle:: sety3(float b3){
        y3 = b3;
    }
    
    // Utility methods
    void Triangle:: draw() const{
        cout << std::fixed;
        cout << std::setprecision(2);
    
         // Print the information
        cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << x1 << " " << y1 << " " <<" " << x2 << " " << " " << y2 << " " <<" " << x3 << " " <<" " << y3 << " " <<computeArea()
         << endl;
    }     // Draws thye Triangle; for the assignment it
                                   // prints the information of the Triangle
    
    float Triangle:: computeArea() const{
        return abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2))/ 2.0);
    }   // Computes the area of the Tirangle
    
    Shape* Triangle:: clone() const{
        return (new Triangle(*this));
    }  // Clones the object

