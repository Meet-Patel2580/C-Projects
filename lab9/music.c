//
// APS105 Lab 9
//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: Meet Patel
// Student Number: 1007896038
//

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
  char *artist;
  char *songName;
  char *genre;
  struct node *next;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser(char *prompt, char *s, int arraySize);
void songNameDuplicate(char *songName);
void songNameFound(char *songName);
void songNameNotFound(char *songName);
void songNameDeleted(char *songName);
void artistFound(char *artist);
void artistNotFound(char *artist);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

Node* insertSong( Node *head, char *songName, char *artist, char *genre);
void printList(Node *head);
bool searchForSong(Node *head, char *songToFind, bool forDeleting);
Node* deleteSong(Node *head, char *songToDelete);

const int MAX_LENGTH = 1024;

int main(void) {
  // Declare the head of the linked list.
  //   ADD YOUR STATEMENT(S) HERE
  Node *head = NULL;

  // Announce the start of the program
  printf("Personal Music Library.\n\n");
  printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
               "P (print), Q (quit).\n");

  char response;
  char input[MAX_LENGTH + 1];
  char inputSong[MAX_LENGTH + 1];
  char inputArtist[MAX_LENGTH + 1];
  char inputGenre[MAX_LENGTH + 1];
  do {
    inputStringFromUser("\nCommand", input, MAX_LENGTH);

    // Response is the first character entered by user.
    // Convert to uppercase to simplify later comparisons.
    response = toupper(input[0]);

    if (response == 'I') {
      // Insert a song into the linked list.
      // Maintain the list in alphabetical order by song name.
      //   ADD STATEMENT(S) HERE
      // USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
      char *promptName = "Song name" ;
      char *promptArtist =  "Artist" ;
      char *promptGenre = "Genre" ;

      inputStringFromUser(promptName,inputSong,MAX_LENGTH);
      inputStringFromUser(promptArtist,inputArtist,MAX_LENGTH);
      inputStringFromUser(promptGenre,inputGenre,MAX_LENGTH);

      head = insertSong(head, inputSong, inputArtist, inputGenre);

    } else if (response == 'D') {
      // Delete a song from the list.

      char *prompt = "\nEnter the name of the song to be deleted";

      inputStringFromUser(prompt, inputSong, MAX_LENGTH);
      head = deleteSong(head, inputSong);

      //   ADD STATEMENT(S) HERE

    } else if (response == 'S') {
      // Search for a song by its name.

      char *prompt = "\nEnter the name of the song to search for";

      inputStringFromUser(prompt, inputSong, MAX_LENGTH);
      searchForSong(head,inputSong, false);

      //   ADD STATEMENT(S) HERE

    } else if (response == 'P') {
      // Print the music library.
      printList(head);

    } else if (response == 'Q') {
      ; // do nothing, we'll catch this below
    } else {
      // do this if no command matched ...
      printf("\nInvalid command.\n");
    }
  } while (response != 'Q');

  // Delete the entire linked list.

    Node *temp = NULL;

    while(head!=NULL){
        temp = head -> next;
        head = deleteSong(head, head -> songName);
    }

  // Print the linked list to confirm deletion.
  //   ADD STATEMENT(S) HERE
  printList(head);

  return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
  int i = 0;
  char c;

  printf("%s --> ", prompt);
  while (i < maxStrLength && (c = getchar()) != '\n')
    s[i++] = c;
  s[i] = '\0';
}

// Function to call when the user is trying to insert a song name
// that is already in the personal music library.
void songNameDuplicate(char *songName) {
  printf("\nA song with the name '%s' is already in the music library.\n"
         "No new song entered.\n",
         songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char *songName) {
  printf("\nThe song name '%s' was found in the music library.\n", songName);
}

// Function to call when a song name was not found in the personal music
// library.
void songNameNotFound(char *songName) {
  printf("\nThe song name '%s' was not found in the music library.\n",
         songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char *songName) {
  printf("\nDeleting a song with name '%s' from the music library.\n",
         songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) { 
  printf("\nThe music library is empty.\n"); 
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) { 
  printf("\nMy Personal Music Library: \n"); 
}

// Add your functions below this line.


Node* insertSong( Node *head, char *songName, char *artist, char *genre){
    if(searchForSong(head, songName, true)){
        songNameDuplicate(songName);
        return head;
    }
    Node *temp = head;

    Node * newNode = (Node*)malloc(sizeof(Node));

    newNode -> songName = (char*) malloc(sizeof(char)*(strlen(songName)));
	newNode -> artist = (char*) malloc(sizeof(char)*(strlen(artist)));
	newNode -> genre = (char*) malloc(sizeof(char)*(strlen(genre)));
		
	strcpy(newNode->songName, songName);
	strcpy(newNode->artist, artist);
	strcpy(newNode->genre, genre);

    if(head == NULL || strcmp(songName, head -> songName) < 0){
        newNode -> next = head;
        head = newNode;
    }
    else{
        //finds spot to insert node so that list remains in alphabetical order
        while(temp -> next != NULL && strcmp(songName, temp -> next -> songName) > 0){
            temp = temp -> next;
        }
        newNode -> next = temp -> next;
        temp -> next = newNode;
    }
    return head; 
}

void printList(Node *head){
    
    if (head == NULL){
        printMusicLibraryEmpty();
    
    }
    else{
        printMusicLibraryTitle();

        Node* current = head;

        while(current != NULL){
            printf("\n%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> next;
        }
    }
}

bool searchForSong(Node *head, char *songToFind, bool forDeleting){

    Node *current = head;

    while(current != NULL && strcmp(current -> songName, songToFind) != 0){
        current = current -> next;
    }
    if(current == NULL){
        if(forDeleting == 0){
            songNameNotFound(songToFind);
        }
        return 0;
    }
    else{
         if(forDeleting == 0){
            songNameFound(songToFind);
            printf("\n%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
        }
        return 1;
    }
}

Node* deleteSong(Node *head, char *songToDelete){
    
    if(!searchForSong(head, songToDelete,true)){
        songNameNotFound(songToDelete);
        return head;
    }

    Node* current = head;

    if(strcmp(head -> songName, songToDelete) == 0){
		Node *new = head->next; // New head should be next node.
        songNameDeleted(songToDelete);
		// Free current head:
		free(head->songName);
		free(head->artist);
		free(head->genre);
		free(head);
        return new;
    }

    while(strcmp(current -> next -> songName, songToDelete) != 0){
        current = current -> next;
    }

	Node *temp = current->next; // Store next of node to delete.
	
    // Free node;
	free(current->next->songName);
	free(current->next->artist);
	free(current->next->genre);
	free(current->next);
	current->next = temp->next;  // Connect stored node to currentNode.
	
    songNameDeleted(songToDelete); // Confirm deletion.
	
	return head; // Return unchanged head.
}

//   ADD STATEMENT(S) HERE
