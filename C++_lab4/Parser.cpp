//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool checkName(string name){
    
    bool isReserved = 0;
    for (int i = 0; i < NUM_KEYWORDS; i++){
        if(name == keyWordsList[i]){
            isReserved = 1;
        }
    }
    for(int j = 0; j < NUM_TYPES; j++){
        if(name == shapeTypesList[j]){
            isReserved = 1;
        }        
    }

    if(isReserved){
        cout << "error: invalid name" << endl;
        return 0;
    }
       for(GroupNode* current = gList->getHead(); current != NULL; current = current -> getNext()){
        if(current->getName() == name){
            cout << "error: name "<< name<< " exists"<< endl;
            return 0;
        }
        else if(current->getShapeList()->find(name) != NULL){
            cout << "error: name "<< name<< " exists"<< endl;
            return 0;
        }
    }
    return 1;
}

void shape(stringstream &ss){
//cout<<"test";
    string name, type;
    int loc_x, loc_y, size_x, size_y;

    ss >> name;

    if(!checkName(name)){
        return;
    }

    ss >> type;
    ss >> loc_x;
    ss >> loc_y;
    ss >> size_x;
    ss >> size_y;

    ShapeNode* node = new ShapeNode();
    Shape* shape = new Shape(name,type,loc_x,size_x,loc_y,size_y);
    node->setShape(shape);
    gList->getHead()->getShapeList()->insert(node);

    cout << name << ": " << type << " " << loc_x << " " << loc_y << " " << size_x << " " << size_y << endl;

    return;

}

void group(stringstream &ss){

    string name;
    ss >> name;
        
    if(!checkName(name)){
        return;
    }

    GroupNode* node = new GroupNode(name);
    gList->insert(node);

    cout << name << ": group" << endl;
    return;
}

void move(string ShapeName, string GroupName){

    GroupNode* newGroupLoc = NULL;
    GroupNode* oldloc = NULL;
    ShapeNode* ptr = NULL;

    for(GroupNode* current = gList->getHead(); current != NULL; current = current -> getNext()){
        if(current->getName() == GroupName){
            newGroupLoc = current;
        }
        if(current->getShapeList()->find(ShapeName) != NULL){
            oldloc = current;
        }
    }

    if((newGroupLoc != NULL) && (oldloc != NULL)){
        ptr = oldloc->getShapeList()->remove(ShapeName);
        newGroupLoc->getShapeList()->insert(ptr);
        
    }
    else if(oldloc == NULL){
        cout << "error: shape "<< ShapeName<< " not found"<< endl;
        return;
    }
    else if(newGroupLoc==NULL){
        cout << "error: group "<< GroupName<< " not found"<< endl;
        return;
    }
    
    cout << "moved " << ShapeName << " to " << GroupName << endl;  

    return;
    
}

void draw(){
    cout<<"drawing:"<< endl;
    gList->print();
    return;
}

void delete_(stringstream &ss){
    string name;
    GroupNode* GroupLoc = NULL;
    GroupNode* shapeGroupLoc = NULL;
    ShapeNode* shape = NULL;
    GroupNode* group = NULL;
    ShapeNode* loc = NULL;
    string name2;
    

    ss >> name;
    
    if(name == "pool"){
        cout << "error: invalid name"<< endl;
        return;
    }

    for(GroupNode* current = gList->getHead(); current != NULL; current = current -> getNext()){
        if(current->getName() == name){
            GroupLoc = current;
        }
        if(current->getShapeList()->find(name) != NULL){
            shapeGroupLoc = current;
        }
    }

    if(GroupLoc != NULL){

        group = gList->remove(name);

        ShapeList* x = group->getShapeList();
        while(x->getHead() != NULL){
            ShapeNode* toInsert = x->remove(x->getHead()->getShape()->getName());
            gList->getHead()->getShapeList()->insert(toInsert);
        }
        delete group;
        delete x; 
    }
    else if(shapeGroupLoc != NULL){
        shape = shapeGroupLoc->getShapeList()->remove(name);
        shape->~ShapeNode();
        delete shape;
    }
    else if(GroupLoc==NULL){
        cout << "error: shape "<< name<< " not found"<< endl;
        return;
    }
    else if(shapeGroupLoc == NULL){
        cout << "error: shape "<< name<< " not found"<< endl;
        return;
    }
    
    cout<< name << ": deleted" << endl;  
    
    return;

}

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string Line;
    string GroupName, ShapeName;
    
    
    cout << "> ";         // Prompt for input
    getline(cin, Line);    // Get a line from standard input

    while ( !cin.eof() ) {
        //cout<<"test";
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (Line);
        //cout<<"test";
        string command;
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if(command == keyWordsList[0]){
            shape(lineStream);
        }   
        else if(command == keyWordsList[1]){
            group(lineStream);
        } 
        else if(command == keyWordsList[2]){
            lineStream >> ShapeName >> GroupName;
            move(ShapeName, GroupName);
        }       
        else if(command == keyWordsList[3]){
            delete_(lineStream);
        } 
        else if(command == keyWordsList[4]){
            draw();
        } 
        else{
           // cout << "Error: invalid command" << endl;
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, Line);
      
    }  // End input loop until EOF.
    
    return 0;
}

