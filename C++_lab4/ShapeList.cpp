//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"

// sets head to nullptr
ShapeList::ShapeList(){
    head = NULL;
}             

// deletes all list nodes starting
// with head plus associated Shapes
ShapeList::~ShapeList(){
        ShapeNode *p;
        while (head != NULL) {
            p = head;
            head = p->getNext();
            p->~ShapeNode();
            delete p;
         }
        head = NULL;
}                       

// returns the head pointer
 ShapeNode* ShapeList::getHead() const{
    return head;
}         

// sets the head pointer to ptr
void ShapeList::setHead(ShapeNode* ptr){
    head = ptr;
}       

// finds a shape node with the specified shape name
// returns a pointer to the node if found, otherwise
// returns nullptr if the node is not found
ShapeNode* ShapeList::find(string name) const{
    ShapeNode* loc = NULL;
    //cout<<"hi";
            for(ShapeNode* current = head; current != NULL; current = current -> getNext()){
                //cout<<"hi";
                if(current->getShape()->getName() == name){
                    loc = current;
                    return loc;
                }
            }
        return loc;
}

// inserts the node pointed to by s at the end
// of the list; s should never be nullptr
void ShapeList::insert(ShapeNode* s){
    s->setNext(NULL);
        ShapeNode* temp = head;
       if(s==NULL){
        return;
       }
        if(head == NULL){
            head = s;
        }
        else{
            while(temp->getNext() != NULL){
                temp = temp -> getNext();
            }
            temp->setNext(s);
        }
        return;
}         

// removes the node with the shape called name
// returns a pointer to the removed node or
// nullptr is a node with name does not exist
ShapeNode* ShapeList::remove(string name){
    ShapeNode* loc = NULL;
        ShapeNode* temp = NULL;
        if(this->find(name)!= NULL){
            if(head->getShape()->getName() == name){
                loc = head;
                temp = head->getNext();
                head->setNext(NULL);
                head = temp;
                return loc;
            }
            else{
                for(ShapeNode* current = head; current->getNext() != NULL; current = current -> getNext()){
                    if(current->getNext()->getShape()->getName() == name){
                        loc = current -> getNext();
                        temp = current -> getNext()->getNext();
                        current->getNext()->setNext(NULL);
                        current->setNext(temp);
                        return loc;
                    }
                }
            }
        }
        return NULL;
} 
// prints the list
void ShapeList::print() const{
    for(ShapeNode* current = head; current != NULL; current = current -> getNext()){
            current->print();
        }
}


