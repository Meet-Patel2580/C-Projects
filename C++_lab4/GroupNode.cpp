//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below

#include "GroupNode.h"

// sets group name to n and makes myShapeList
// point to a new ShapeList; sets next to nullptr
GroupNode::GroupNode(string n){
    name = n;
    myShapeList = new ShapeList();
    next = NULL;
}                   

// deletes the myShapeList list                   
GroupNode::~GroupNode(){
     myShapeList->~ShapeList();
     myShapeList = NULL;
     return;
}              

 // returns group name           
string GroupNode::getName() const{
    return name;
}               

// returns myShapeList
ShapeList* GroupNode::getShapeList() const{
    return myShapeList;
}   

// sets myShapeList to ptr
void GroupNode::setShapeList(ShapeList* ptr){
    myShapeList = ptr;
    return;
}   

  // returns next
GroupNode* GroupNode::getNext() const{
    return next;
}         

// sets next to ptr
void GroupNode::setNext(GroupNode* ptr){
    next = ptr;
}         

// prints the GroupNode
void GroupNode::print() const{
    cout << this->getName() << ": " << endl;
    this->getShapeList()->print();
}                 


