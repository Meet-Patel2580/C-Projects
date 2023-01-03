//#include "reversi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void initializeBoard(char[][26], int);
void printBoard(char[][26], int);
void playCpuTurn( char[][26], int, char, bool);
void playPlayerTurn(char[][26], int, char, bool);
bool checkMoveAvailable( const char[][26], int, char, char, char);
bool positionInBounds(int, int, int);
bool checkLegalInDirection( char[][26], int, int, int, char, int, int);
void performMove(char[][26], int, char, char, char);
int performDummyMove(char[][26], int, char, char, char);
bool checkEndGame(char[][26], int);
void endGame(char[][26], int);
void forceEndGame(char);
bool anyMoveAvailable(char[][26], int, char);
void createCopyBoard( char[][26], const char[][26], int);
int findScore(char[][26], int, char, char, char);
int makeMove(const char board[][26], int n, char turn, int *row, int *col);
int weakBias(int);
int strongBias(char[][26], int);
bool pointInCorner(int, int, int);
bool pointInEdge(int, int, int);
bool pointInRisk(int, int ,int);
int mobilityScore(char[][26], int, char, char, char);
int remainingTiles(char[][26], int);
bool riskCornerTaken(char[][26], int, int, int ,char);
char oppTurn(char);
bool bothMovesAvailable(char[][26], int);



// Prints the board with coordinates 
void printBoard(char board[][26], int n) {

  char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  
  printf("  ");

  //prints letters at the top
  for (int l = 0; l < n; l++){
    printf("%c",letters[l]);
  }

  printf("\n");

  // Prints letters on the left as well as the board itself
  for (int row = 0; row < n; row++){
   
    printf("%c ",letters[row]);

    for (int col = 0; col < n; col++){
      printf("%c", board[row][col]);
    }

    printf("\n");
  }
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col){
  char cpyBoard[26][26];
	int score, maxScore = -9999;
	char moveRow, moveCol;
	char r, c;
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			r = i + 'a';
			c = j + 'a';
			if (checkMoveAvailable(board, n, r, c, turn)) {
				createCopyBoard(cpyBoard, board, n);
				score = findScore(cpyBoard, n, r, c, turn);
				if (score > maxScore) {
					maxScore = score;
					moveRow = r;
					moveCol = c;
				}
			}
		}
	}
	*row = moveRow - 'a';
	*col = moveCol - 'a';
  return 0;
}

void createCopyBoard( char copy[][26], const char original[][26], int n) {
    int i,j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			copy[i][j] = original[i][j];
		}
	}
}


bool anyMoveAvailable(char board[][26], int n, char turn) {
	int r, c;
	char row, col;
	bool movesAvailable = false;
	for (r=0; r<n; r++) {
		for (c=0; c<n; c++) {
			row = r+'a';
			col = c+'a';
			if (checkMoveAvailable(board, n, row, col, turn)) {
				movesAvailable = true;
				break;
			}
		}
		if (movesAvailable) break;
	}
	return movesAvailable;
}


int findScore(char board[][26], int n, char row, char col, char turn) {
	int moveScore,score, tempScore, maxScore = -9999;
	score = performDummyMove(board, n, row, col, turn);
	int i = row-'a', j = col-'a';
	if (pointInCorner(n, i, j)) score += strongBias(board, n);
	if (pointInEdge(n, i, j)) score += weakBias(n);
	if (pointInRisk(n, i, j)) score -= weakBias(n);
	performMove(board, n, row, col, turn);
	clr = oppTurn(clr);
	bool cpuTurn = false;
	char moveRow, moveCol;
	
	while (bothMovesAvailable(board, n) && !checkEndGame(board, n)) {
		if (anyMoveAvailable(board, n, turn)) {
			for (i=0; i<n; i++) {
				for (j=0; j<n; j++) {
					row = i + 'a';
					col = j + 'a';
					if (checkMoveAvailable(board, n, row, col, turn)) {
						tempScore = performDummyMove(board, n, row, col, turn);
						if (pointInCorner(n, i, j)) tempScore += strongBias(board, n);
						if (pointInEdge(n, i, j)) tempScore += weakBias(n);
						if (pointInRisk(n, i, j)) {
							if (!riskCornerTaken(board, n, i, j, turn)) tempScore -= weakBias(n);
						}
						// UNCOMMENT BELOW TO INCLUDE PLAYER'S AVAILABLE MOVES INTO CONSIDERATION.
						moveScore = mobilityScore(board, n, row, col, turn);
						if (moveScore <= 0) tempScore += strongBias(board, n);
						else tempScore -= moveScore;
						if (tempScore > maxScore) {
							maxScore = tempScore;
							moveRow = i;
							moveCol = j;
						}
					}
				}
			}
			performMove(board, n, moveRow, moveCol, turn);
			if (cpuTurn) score += maxScore;
			else score -= maxScore;
		} else {
			if (cpuTurn) score -= strongBias(board, n);
			else score += strongBias(board, n);
		}
		cpuTurn = !cpuTurn;
		maxScore = -9999;
		clr = oppTurn(clr);
	}
	return score;
}

char oppTurn(char turn) {
	if (turn == 'W') return 'B';
	else return 'W';
}

bool bothMovesAvailable(char board[26][26], int n) {
	if (anyMoveAvailable(board, n, 'W') && anyMoveAvailable(board, n, 'B')) return true;
	else return false;
}


int chooseMove(const char board[][26], int n, char turn, int *row, int *col) {
	char cpyBoard[26][26];
	int score, maxScore = -9999;
	char moveRow, moveCol;
	char r, c;
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			r = i + 'a';
			c = j + 'a';
			if (checkMoveAvailable(board, n, r, c, turn)) {
				createCopyBoard(cpyBoard, board, n);
				score = findScore(cpyBoard, n, r, c, turn);
				if (score > maxScore) {
					maxScore = score;
					moveRow = r;
					moveCol = c;
				}
			}
		}
	}
	*row = moveRow;
	*col = moveCol;
    return 0;
}

int performDummyMove(char board[][26], int n, char row, char col, char clr) {
	int count = 1;
	int i = row - 'a';
	int j = col - 'a';
	int k,m;
	int dR, dC;
	board[i][j] = clr;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row - 'a', col - 'a', clr, dR, dC)) {
					for (k=dR, m=dC; true; k+=dR, m+=dC) {
						if (board[i+k][j+m] != clr) count++;
						else break;
					}
				}
			}
		}
	}
	return count;
}

bool checkMoveAvailable(const char board[][26], int n, char row, char col, char clr) {
  char cpy[26][26];
	int i=row-'a';
	int j=col-'a';
	if (clr != 'B' && clr != 'W') return false;
	if (!positionInBounds(n, row - 'a', col - 'a')) return false;
	if (board[i][j] != 'U') return false;
	bool available = false;
	int dR, dC;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
        createCopyBoard(cpy,board,n);
				if (checkLegalInDirection(cpy, n, row - 'a', col - 'a', clr, dR, dC)) {
						available = true;
						break;
				}
			}
		}
		if (available) break;
	}
	return available;
}

bool positionInBounds(int n, int row, int col){
	if (row>=n || row<0) return false;
	if (col>=n || col<0) return false;
	return true;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
	if (!positionInBounds(n, row+deltaRow, col+deltaCol)) return false;
	char antiColour = (colour == 'W')? 'B' : 'W';
	int i, j;
	if (board[row+deltaRow][col+deltaCol] != antiColour) return false;
	bool foundColour = false;
	for (i=row+deltaRow, j=col+deltaCol; ((i+deltaRow<n+1) && (i+deltaRow>=-1)) && ((j+deltaCol)<n+1 && (j+deltaCol>=-1)); i+=deltaRow, j+=deltaCol) {
		if (board[i][j] == colour) {
			foundColour = true;
			break;
		} else if (board[i][j] == 'U') {
			foundColour = false;
			break;
		}
	}
	return foundColour;
}

void performMove(char board[][26], int n, char row, char col, char clr) {
	int i = row - 'a';
	int j = col - 'a';
	int k,m;
	int dR, dC;
	board[i][j] = clr;
	for (dR=-1; dR<=1; dR++) {
		for (dC=-1; dC<=1; dC++) {
			if (!(dR == 0 && dC == 0)) {
				if (checkLegalInDirection(board, n, row - 'a', col - 'a', clr, dR, dC)) {
					for (k=dR, m=dC; true; k+=dR, m+=dC) {
						if (board[i+k][j+m] != clr) board[i+k][j+m] = clr;
						else break;
					}
				}
			}
		}
	}	
}

bool checkEndGame(char board[][26], int n) {
	int i,j;
	bool over = true;
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'U') {
				over = false;
				break;
			}
		}
		if (!over) break;
	}
	return over;
}

void endGame(char board[][26], int n) {
	int wPts=0, bPts=0;
	int i,j;
	
	for (i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if (board[i][j] == 'W') wPts++;
			else if (board[i][j] == 'B') bPts++;
		}
	}
	
	if (wPts > bPts) printf("W player wins.");
	else if (bPts > wPts) printf("B player wins.");
	else printf("Draw!");
}

void forceEndGame(char clr) {
	printf("%c player wins", clr);
}

int weakBias(int n) {
	return n/2;
}

int strongBias(char board[][26], int n) {
	int tilesRemain = remainingTiles(board, n);
	tilesRemain *= 100;
	tilesRemain /= n*n;
	n *= (tilesRemain > 75)? 2 : 1;
	return n;
}

bool pointInCorner(int n, int row, int col) {
	if (row == 0 && col == 0) return true;
	if (row == 0 && col == n-1) return true;
	if (row == n-1 && col == 0) return true;
	if (row == n-1 && col == n-1) return true;
	return false;
}

bool pointInEdge(int n, int row, int col) {
	if (row == 0 && col > 1 && col < n-2) return true;
	if (row > 1 && row < n-2 && col == 0) return true;
	if (row == n-1 && col > 1 && col < n-2) return true;
	if (row > 1 && row < n-2 && col == n-1) return true;
	return false;
}

bool pointInRisk(int n, int row, int col) {
	if (row == 0 && (col == 1 || col == n-2)) return true;
	if (row == 1 && (col < 2 || col > n-3)) return true;
	if (row == n-2 && (col < 2 || col > n-3)) return true;
	if (row == n-1 && (col == 1 || col == n-2)) return true;
	return false;
}

int mobilityScore(char board[][26], int n, char row, char col, char clr) {
	char antiClr = oppTurn(clr);
	char copyBoard[26][26];
	createCopyBoard(copyBoard, board, n);
	performMove(copyBoard, n, row, col, clr);
	int i, j;
	char r, c;
	int count=0;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			r = i+'a';
			c = j+'a';
			if (checkMoveAvailable(copyBoard, n, r, c, antiClr)) {
				if (pointInCorner(n, i, j)) count += strongBias(copyBoard, n);
				else if (pointInEdge(n, i, j)) count += weakBias(n);
				else if (pointInRisk(n, i, j)) count -= weakBias(n);
				else count++;
			}
		}
	}
	return count;
}

int remainingTiles(char board[][26], int n) {
	int i, j;
	int count = 0;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			if (board[i][j] == 'U') count++;
		}
	}
	return count;
}

bool riskCornerTaken(char board[][26], int n, int row, int col, char clr) {
	if (row == 0 && col == 1) { // Top Left Corner
		if (board[0][0] == clr) return true;
		else return false;
	}
	if (row == 0 && col == n-2) { // Top Right Corner
		if (board[0][n-1] == clr) return true;
		else return false;
	}
	if (row == 1 && col < 2) { // Top Left Corner
		if (board[0][0] == clr) return true;
		else return false;
	}
	if (row == 1 && col > n-3) { // Top Right Corner
		if (board[0][n-1] == clr) return true;
		else return false;
	}
	if (row == n-2 && col < 2) { // Bottom Left Corner
		if (board[n-1][0] == clr) return true;
		else return false;
	}
	if (row == n-2 && col > n-3) { // Bottom Right Corner
		if (board[n-1][n-1] == clr) return true;
		else return false;
	}
	if (row == n-1 && col == 1) { // Bottom Left Corner
		if (board[n-1][0] == clr) return true;
		else return false;
	}
	if (row == n-1 && col == n-2) { // Bottom Right Corner
		if (board[n-1][n-1] == clr) return true;
		else return false;
	}
	return false;
}

