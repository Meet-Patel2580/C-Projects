//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.
#include "Shape.h"

class Triangle : public Shape {
private:
    float x1;
    float x2;
    float x3;
    float y1;
    float y2;
    float y3;         

public:
    // Constructor
    Triangle (string n, float x1, float x2, float x3, float y1, float y2, float y3);
    
    // Destructor
    virtual ~Triangle();
    
    // Accessor
    float getx1() const;       
    float getx2() const;
    float getx3() const;
    float gety1() const;
    float gety2() const;
    float gety3() const;

    // Mutator
    void setx1(float a1);    
    void setx2(float a2);
    void setx3(float a3);
    void sety1(float b1);
    void sety2(float b2);
    void sety3(float b3);
    
    // Utility methods
    virtual void draw() const;     // Draws thye Triangle; for the assignment it
                                   // prints the information of the Triangle
    
    virtual float computeArea() const;   // Computes the area of the Tirangle
    
    virtual Shape* clone() const;  // Clones the object
};

#endif /* Triangle_h */


