/**
 * @file reversi.c
 * @author Aryan Hussain
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 * 
 */

#if !defined(TESTER_P1) && !defined(TESTER_P2)
#include "reversi.h"
#endif

void printBoard(char board[][26], int n) {

    printf("  ");
    char letter = 'a';

    for(int i = 0; i < n; i++){
        printf("%c", (letter+i));
    }

    printf("\n");

    for(int j = 0; j < n; j++){

        printf("%c", (letter+j));
        printf(" ");

        for(int k = 0; k < n; k++){

            printf("%c", board[j][k]);

        }

        printf("\n");

    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool positionInBounds(int n, int row, int col) {

    if(row < n && col < n && row >= 0 && col >= 0){
        return true;
    }
    return false;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void updateRowCol(int* row, int* col, int DeltaRow, int DeltaCol){
  
    if(DeltaRow == -1 && DeltaCol==0){  //North
        (*row)--;
    }
    else if(DeltaRow == 1 && DeltaCol==0){  //South
        (*row)++;
    }
    else if(DeltaRow == 0 && DeltaCol==1){  //East
        (*col)++;     
    }
    else if(DeltaRow == 0 && DeltaCol==-1){ //West
        (*col)--;
    }
 
    else if(DeltaRow == -1 && DeltaCol==1){ //Northeast
        (*row)--;
        (*col)++;
    }
    else if(DeltaRow == -1 && DeltaCol==-1){ //NorthWest
        (*row)--;
        (*col)--;
    }
    else if(DeltaRow == 1 && DeltaCol==1){ //SouthEast
        (*row)++;
        (*col)++;
    }
    else if(DeltaRow == 1 && DeltaCol==-1){ //Southwest
        (*row)++;
        (*col)--;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {

    int count = 1;
    if(board[row][col] != 'U'){
      
            return false;
        }

        updateRowCol(&row, &col, deltaRow, deltaCol);

        while( positionInBounds(n, row, col) && (board[row][col] != colour)){

            if(board[row][col] == 'U'){ 
           
                return false; 
            }

            updateRowCol(&row, &col, deltaRow, deltaCol);
            count++;
        }


    if(!positionInBounds(n, row, col)){
        return false;
    }
    else if(count == 1){
        return false;
    }
    return true; 

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool movesChecker(char board[][26], int dim, int row, int col, char colour){

    for(int Drow = -1; Drow <= 1; Drow++){

        for(int Dcol = -1; Dcol <= 1; Dcol++){

            if(!(Dcol == 0 && Drow == 0) && checkLegalInDirection(*board, dim, row, col, colour, Drow, Dcol) ){
    
                return true;

            }
        }
    }

    false;           
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tileFlipper(char board[][26], int dim, int row, int col, char colour){

    int trow = row;
    int tcol = col;

    for(int Drow = -1; Drow <= 1; Drow++){
        for(int Dcol = -1; Dcol <= 1; Dcol++){

            if( (Dcol != 0 || Drow != 0) && checkLegalInDirection(*board, dim, row, col, colour, Drow, Dcol)){ 

                updateRowCol(&row, &col, Drow, Dcol);    

                while(board[row][col] != colour){
                    board[row][col] = colour;
                    updateRowCol(&row, &col, Drow, Dcol);                 
                }  

                row = trow;
                col = tcol;

            }                               
        }
    } 

    board[row][col] = colour;       
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int tileFlipCounter(char board[][26], int dim, int row, int col, char colour){

    int count = 1;
    int trow = row;
    int tcol = col;

    for(int Drow = -1; Drow <= 1; Drow++){
        for(int Dcol = -1; Dcol <= 1; Dcol++){

            if( (Dcol != 0 || Drow != 0) && checkLegalInDirection(*board, dim, row, col, colour, Drow, Dcol)){ 

                updateRowCol(&row, &col, Drow, Dcol);    

                while(board[row][col] != colour){
                    count++;
                    updateRowCol(&row, &col, Drow, Dcol);                 
                }  
                                        
                row = trow;
                col = tcol;

            }                               
        }
    }

    return count; 
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int makePlayerMove(char board[26][26], int n, char turn, int row, int col) {

    int realRow = row - 'a', realCol = col -'a';

    if(movesChecker(*board, n, realRow, realCol, turn)){      
        tileFlipper(*board, n, realRow, realCol, turn);
        printBoard(*board, n);
        return 0;
    }
    else{
        printf("Invalid move.\n");
        return 2;

    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int makeMove(char board[26][26], int n, char turn, int *row, int *col) {

    int Count = 0, MaxCount = 0;
    char maxRow = '0', maxCol = '0';

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(movesChecker( *board, n, i, j, turn)){

                Count = tileFlipCounter(*board, n, i, j, turn);

                if(Count > MaxCount){
                    MaxCount = Count;
                    maxRow = i;
                    maxCol = j;
                }
            }
        }
    }

    *row = maxRow;
    *col = maxCol;


    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compMove(char board[26][26], int n, char turn) {

    int row = 0;
    int col = 0;

    int pHolder = makeMove(*board, n, turn, &row, &col);

    printf("Computer places %c at %c%c.\n", turn, row + 'a', col + 'a');
    tileFlipper(*board, n, row, col, turn);
    printBoard(*board, n);
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool moveLegality(char board[26][26], int dim, char turn){

    for(int i = 0; i < dim; i++){

        for(int j = 0; j < dim; j++){

            for(int Drow = -1; Drow <= 1; Drow++){

                for(int Dcol = -1; Dcol <= 1; Dcol++){

                    if(!(Dcol == 0 && Drow == 0) && checkLegalInDirection(*board, dim, i, j, turn, Drow, Dcol) ){
                    
                        return true;

                    }
                }
            }       
        }
    }
    
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char gameWinner(char board[][26], int dim){

    int countB = 0;
    int countW = 0;

    for(int j = 0; j < dim; j++){
        for(int k = 0; k < dim; k++){

           if(board[j][k] == 'B'){
            countB++;
           }
           else if(board[j][k] == 'W'){
            countW++;
           }
        }
    }

    if(countB > countW){
            return 'B';
        }
    else if(countW > countB){
            return 'W';
        }
    else{
        return 'D';
    }



}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TESTER_P2

int main(void) {
  
    int dim = 0;
    printf("Enter the board dimension: ");
    scanf("%d", &dim);

    char Pcol = '0', Ccol ='0';

    printf("Computer plays (B/W): ");
    scanf(" %c", &Ccol);

    if(Ccol == 'B'){
        Pcol = 'W';
    }
    else{
        Pcol = 'B';
    }

    char board[26][26];

    for(int j = 0; j < dim; j++){
        for(int k = 0; k < dim; k++){
           board[j][k] = 'U';
        }
    }

    board[dim/2][dim/2] = 'W';
    board[dim/2 - 1][dim/2 - 1] = 'W';
    board[dim/2 - 1][dim/2] = 'B';
    board[dim/2][dim/2 - 1] = 'B';

    int mRow = 0, mCol = 0;
    int winner = 0;
    printBoard(*board, dim);

    while(winner == 0 && Ccol == 'B'){

        if(moveLegality(*board, dim, Ccol)){
            compMove(*board, dim, Ccol);
        }
        else if(!moveLegality(*board, dim, Ccol) && moveLegality(*board, dim, Pcol)){
            printf("B player has no valid move.\n");
        }

        if(moveLegality(*board, dim, Pcol)){
            printf("Enter move for colour %c (RowCol): ", Pcol);
            scanf(" %c%c", &mRow, &mCol);    
            winner = makePlayerMove(*board, dim, Pcol, mRow, mCol);
        }
        else if(!moveLegality(*board, dim, Pcol) && moveLegality(*board, dim, Ccol)){
            printf("W player has no valid move.\n");
        }

        if(!(moveLegality(*board, dim, Ccol)) && !(moveLegality(*board, dim, Pcol))){
            winner = gameWinner(*board, dim);
        }
    }

    while(winner == 0 && Ccol == 'W'){

        if(moveLegality(*board, dim, Pcol)){
            printf("Enter move for colour %c (RowCol): ", Pcol);
            scanf(" %c%c", &mRow, &mCol);    
            winner = makePlayerMove(*board, dim, Pcol, mRow, mCol);
        }
        else if(!moveLegality(*board, dim, Pcol) && moveLegality(*board, dim, Ccol)){
            printf("B player has no valid move.\n");
        }

        if(moveLegality(*board, dim, Ccol)){
            compMove(*board, dim, Ccol);
        }
        else if(!moveLegality(*board, dim, Ccol) && moveLegality(*board, dim, Pcol)){
            printf("W player has no valid move.\n");
        }

        if(!(moveLegality(*board, dim, Ccol)) && !(moveLegality(*board, dim, Pcol))){
            winner = gameWinner(*board, dim);
        }
    }

    if(winner == 2){
        printf("%c player wins.", Ccol);
    }
    else if(winner == 'W'){
        printf("W player wins.");
    }
    else if(winner == 'B'){
        printf("B player wins.");
    }
    else{
        printf("Draw!");
    }

    return 0;
}

#endif