//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below

#include "GroupList.h"
#include "GroupNode.h"

    // sets head to nullptr
    GroupList :: GroupList(){
        head = NULL;
    }                     

    // deletes all list nodes, including all the ShapeList
    // attached to each GroupNode
    GroupList :: ~GroupList(){
        GroupNode *p;
        while (head != NULL) {
            p = head;
            head = p->getNext();
            p->~GroupNode();
            delete p;
         }
        head = NULL;
    }                     
    
     // returns the head pointer
    GroupNode* GroupList ::getHead() const{
        return head;
    }   

    // sets the head pointer to ptr
    void GroupList :: setHead(GroupNode* ptr){
        head = ptr;
    }   

    // inserts the node pointed to by s at the end of the list
    void GroupList :: insert(GroupNode* s){
        s->setNext(NULL);
        GroupNode* temp = head;
       
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

    // removes the group with the name "name" from the list
    // and returns a pointer to the removed GroupNode
    // returns nullptr is name is not found on list
    GroupNode* GroupList :: remove(string name){
        GroupNode* loc = NULL;
        GroupNode* temp = NULL;
        if(head->getName() == name){
            loc = head;
            temp = head->getNext();
            head->setNext(NULL);
            head = temp;
            return loc;
        }
        else{
            for(GroupNode* current = head; current->getNext() != NULL; current = current -> getNext()){
                if(current->getNext()->getName() == name){
                    loc = current -> getNext();
                    temp = current -> getNext()->getNext();
                    current->getNext()->setNext(NULL);
                    current->setNext(temp);
                    return loc;
                }
            }
        }
        return NULL;
    }   

    // prints the list, one GroupNode at a time
    void GroupList :: print() const{
        for(GroupNode* current = head; current != NULL; current = current -> getNext()){
            current->print();
    
        }
    }             


