#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gameControl(char board[8][8], FILE *fptr){

    int blackControl = 0;
    int whiteControl = 0;

    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(board[i][j] == 'g'){
                blackControl = 1;
            }
            if(board[i][j] == 'G'){
                whiteControl = 1;
            }
        }
    }
    if(whiteControl == 0){
        fprintf(fptr,"\n\n BLACK WIN !!!...");
        printf("\n\n BLACK WIN !!!...\n\n");
        return 1;
    }
    if(blackControl == 0){
        fprintf(fptr,"\n\n WHITE WIN !!!...");
        printf("\n\n WHITE WIN !!!...\n\n");
        return 1;
    }
    return 0;
}

void selectionBlack(char board[8][8], FILE *moves);
void selectionWhite(char board[8][8], FILE *moves);

void movesToText(int row, int column, char piece, int oldRow, int oldColumn, FILE *moves){

    char movedPiece[3] = {""};

    switch(piece){
        case 'p':
            strcat(movedPiece,"BP");
            break;
        case 'P':
            strcat(movedPiece,"WP");
            break;
        case 'r':
            strcat(movedPiece,"BR");
            break;
        case 'R':
            strcat(movedPiece,"WR");
            break;
        case 'k':
            strcat(movedPiece,"BK");
            break;
        case 'K':
            strcat(movedPiece,"WK");
            break;
        case 'b':
            strcat(movedPiece,"BB");
            break;
        case 'B':
            strcat(movedPiece,"WB");
            break;
        case 'q':
            strcat(movedPiece,"BQ");
            break;
        case 'Q':
            strcat(movedPiece,"WQ");
            break;
        case 'g':
            strcat(movedPiece,"BG");
            break;
        case 'G':
            strcat(movedPiece,"WG");
            break;
        default:
            printf("\n\n!!!!!!!!!!\n\n");    //if there is any error
            break;
        }

    fprintf(moves,"\n\tMove : %c%d %s -> %c%d ",(char)oldColumn+65,8-oldRow,movedPiece,(char)column+65,8-row);


}
void eliminate(char board[8][8], int row, int column, char piece, int oldRow, int oldColumn, FILE *moves){

    char eliminatedPiece[3] = {""};
    char conquerorPiece[3] = {""};

    switch(board[row][column]){
        case 'p':
            strcat(eliminatedPiece,"BP");
            break;
        case 'P':
            strcat(eliminatedPiece,"WP");
            break;
        case 'r':
            strcat(eliminatedPiece,"BR");
            break;
        case 'R':
            strcat(eliminatedPiece,"WR");
            break;
        case 'k':
            strcat(eliminatedPiece,"BK");
            break;
        case 'K':
            strcat(eliminatedPiece,"WK");
            break;
        case 'b':
            strcat(eliminatedPiece,"BB");
            break;
        case 'B':
            strcat(eliminatedPiece,"WB");
            break;
        case 'q':
            strcat(eliminatedPiece,"BQ");
            break;
        case 'Q':
            strcat(eliminatedPiece,"WQ");
            break;
        case 'g':
            strcat(eliminatedPiece,"BG");
            break;
        case 'G':
            strcat(eliminatedPiece,"WG");
            break;
        default:
            printf("\n\n!!!!!!!!!!\n\n");    //if there is any error
            break;
        }
    switch(piece){
        case 'p':
            strcat(conquerorPiece,"BP");
            break;
        case 'P':
            strcat(conquerorPiece,"WP");
            break;
        case 'r':
            strcat(conquerorPiece,"BR");
            break;
        case 'R':
            strcat(conquerorPiece,"WR");
            break;
        case 'k':
            strcat(conquerorPiece,"BK");
            break;
        case 'K':
            strcat(conquerorPiece,"WK");
            break;
        case 'b':
            strcat(conquerorPiece,"BB");
            break;
        case 'B':
            strcat(conquerorPiece,"WB");
            break;
        case 'q':
            strcat(conquerorPiece,"BQ");
            break;
        case 'Q':
            strcat(conquerorPiece,"WQ");
            break;
        case 'g':
            strcat(conquerorPiece,"BG");
            break;
        case 'G':
            strcat(conquerorPiece,"WG");
            break;
        default:
            printf("\n\n!!!!!!!!!!\n\n");    //if there is any error
            break;
        }

    printf("\n\nElimination : %c%d %s -> %c%d %s\n\n\n",(char)oldColumn+65,8-oldRow,conquerorPiece,(char)column+65,8-row,eliminatedPiece);
    board[row][column] = piece;
    fprintf(moves,"\n\tElimination : %c%d %s -> %c%d %s",(char)oldColumn+65,8-oldRow,conquerorPiece,(char)column+65,8-row,eliminatedPiece);


}

void movePawn(char board[8][8],int row,int column, FILE *moves){

    char letters[10];
    int numbers[10];

    int counter = 0;
    char table[20] = {" ABCDEFGH"};
    char pieces[6] = {""};

    if(board[row][column] == 'p'){                  //black pawn
        strcat(pieces,"RKBQGP");
        if(row+1 < 8){
            if(column-1 > -1){
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row+1][column-1] == pieces[i]){        //left corner
                        numbers[counter] = (8-row-1);
                        letters[counter] = table[column-1+1];
                        counter++;
                    }
                }
            }
            if(column+1 <8){
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row+1][column+1] == pieces[i]){       //right corner
                        numbers[counter] = (8-row-1);
                        letters[counter] = table[column+1+1];
                        counter++;
                    }
                }
            }
             if(board[row+1][column] == 'x'){        //forward movement
                numbers[counter] = (8-row-1);
                letters[counter] = table[column+1];
                counter++;

                if(row == 1){
                    if(board[row+2][column] == 'x'){    //double forward
                        numbers[counter] = (8-row-2);
                        letters[counter] = table[column+1];
                        counter++;
                    }
                }
            }
        }
    }
    else{                                           //white pawn
        strcat(pieces,"rkbqgp");

        if(row-1 > -1){
            if(column-1 > -1){
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row-1][column-1] == pieces[i]){        //left corner
                        numbers[counter] = (8-row+1);
                        letters[counter] = table[column-1+1];
                        counter++;
                    }
                }
            }
            if(column+1 <8){
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row-1][column+1] == pieces[i]){       //right corner
                        numbers[counter] = (8-row+1);
                        letters[counter] = table[column+1+1];
                        counter++;
                    }
                }
            }
            if(board[row-1][column] == 'x'){        //forward movement
                numbers[counter] = (8-row+1);
                letters[counter] = table[column+1];
                counter++;

                if(row == 6){
                    if(board[row-2][column] == 'x'){    //double forward
                        numbers[counter] = (8-row+2);
                        letters[counter] = table[column+1];
                        counter++;
                    }
                }
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'p'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'P'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }
    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){

            board[row][column] = 'x';   //reseting pawn's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating pawn's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text
        }
    }
}
void moveRock(char board[8][8],int row,int column, FILE *moves){

    char pieces[6] = {""};
    if(board[row][column] == 'r'){
        strcat(pieces,"RKBQGP");
    }
    else{
        strcat(pieces,"rkbqgp");
    }

    char letters[40];
    int numbers[40];

    int counter = 0;
    char table[8] = {"ABCDEFGH"};

    for(int i = 1 ; board[row][column+i] == 'x' ; i++){     //right
        if(column+i < 8){
            numbers[counter] = (8-row);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(column+i+1 < 8){
                    if(board[row][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(column+1 < 8){
            if(board[row][column+1] == pieces[i]){
                numbers[counter] = (8-row);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row][column-i] == 'x' ; i++){     //left
        if(column-i > -1){
            numbers[counter] = (8-row);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(column-i-1 > -1){
                    if(board[row][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(column-1 > -1){
            if(board[row][column-1] == pieces[i]){
                numbers[counter] = (8-row);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row-i][column] == 'x' ; i++){     //up
        if(row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1){
                    if(board[row-i-1][column] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1){
            if(board[row-1][column] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column] == 'x' ; i++){     //down
        if(row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8){
                    if(board[row+i+1][column] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8){
            if(board[row+1][column] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column];
                counter++;
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'r'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'R'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }
    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){

            board[row][column] = 'x';   //reseting rock's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating rock's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text

        }
    }
}
void moveKnight(char board[8][8],int row,int column, FILE *moves){

    char pieces[6] = {""};
    if(board[row][column] == 'k'){
        strcat(pieces,"RKBQGP");
    }
    else{
        strcat(pieces,"rkbqgp");
    }

    printf("\n\n");
    char letters[10];
    int numbers[10];

    int counter = 0;
    char table[8] = {"ABCDEFGH"};

    if(row - 2 > -1 && column - 1 > -1){
        if(board[row-2][column-1] == 'x'){      //upper left move
            numbers[counter] = (8-row+2);
            letters[counter] = table[column-1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row-2][column-1] == pieces[i]){
                    numbers[counter] = (8-row+2);
                    letters[counter] = table[column-1];
                    counter++;
                }
            }
        }
    }
    if(row - 2 > -1 && column + 1 < 8){
        if(board[row-2][column+1] == 'x'){      //upper right move
            numbers[counter] = (8-row+2);
            letters[counter] = table[column+1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row-2][column+1] == pieces[i]){
                    numbers[counter] = (8-row+2);
                    letters[counter] = table[column+1];
                    counter++;
                }
            }
        }
    }
    if(row + 2 > -1 && column - 1 > -1){
        if(board[row+2][column-1] == 'x'){      //lower left move
            numbers[counter] = (8-row-2);
            letters[counter] = table[column-1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row+2][column-1] == pieces[i]){
                    numbers[counter] = (8-row-2);
                    letters[counter] = table[column-1];
                    counter++;
                }
            }
        }
    }
    if(row + 2 > -1 && column + 1 < 8){
        if(board[row+2][column+1] == 'x'){      //lower right move
            numbers[counter] = (8-row-2);
            letters[counter] = table[column+1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row+2][column+1] == pieces[i]){
                    numbers[counter] = (8-row-2);
                    letters[counter] = table[column+1];
                    counter++;
                }
            }
        }
    }
    if(row + 1 < 8 && column - 2 > -1){
        if(board[row+1][column-2] == 'x'){      //right-down move
            numbers[counter] = (8-row-1);
            letters[counter] = table[column-2];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row+1][column-2] == pieces[i]){
                    numbers[counter] = (8-row-1);
                    letters[counter] = table[column-2];
                    counter++;
                }
            }
        }
    }
    if(row - 1 > -1 && column - 2 > -1){
        if(board[row-1][column-2] == 'x'){      //right-up move
            numbers[counter] = (8-row+1);
            letters[counter] = table[column-2];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row-1][column-2] == pieces[i]){
                    numbers[counter] = (8-row+1);
                    letters[counter] = table[column-2];
                    counter++;
                }
            }
        }
    }
    if(row + 1 < 8 && column + 2 < 8){
        if(board[row+1][column+2] == 'x'){      //left-down move
            numbers[counter] = (8-row-1);
            letters[counter] = table[column+2];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row+1][column+2] == pieces[i]){
                    numbers[counter] = (8-row-1);
                    letters[counter] = table[column+2];
                    counter++;
                }
            }
        }
    }
    if(row - 1 > -1 && column + 2 < 8){
        if(board[row-1][column+2] == 'x'){      //left-up move
            numbers[counter] = (8-row+1);
            letters[counter] = table[column+2];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row-1][column+2] == pieces[i]){
                    numbers[counter] = (8-row+1);
                    letters[counter] = table[column+2];
                    counter++;
                }
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'k'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'K'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }

    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){

            board[row][column] = 'x';   //reseting knight's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating knight's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text
        }
    }

}
void moveBishop(char board[8][8],int row,int column, FILE *moves){

    char pieces[6] = {""};
    if(board[row][column] == 'b'){
        strcat(pieces,"RKBQGP");
    }
    else{
        strcat(pieces,"rkbqgp");
    }

    char letters[40];
    int numbers[40];

    int counter = 0;
    char table[8] = {"ABCDEFGH"};


    for(int i = 1 ; board[row-i][column+i] == 'x' ; i++){     //upper right
        if(column+i < 8 && row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1 && column+i+1 < 8){
                    if(board[row-i-1][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1 && column+1 < 8){
            if(board[row-1][column+1] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row-i][column-i] == 'x' ; i++){     //upper left
        if(column-i > -1 && row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1 && column-i-1 > -1){
                    if(board[row-i-1][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1 && column-1 > -1){
            if(board[row-1][column-1] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column+i] == 'x' ; i++){     //lower right
        if(column+i < 8 && row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8 && column+i+1 < 8){
                    if(board[row+i+1][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8 && column+1 < 8){
            if(board[row+1][column+1] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column-i] == 'x' ; i++){     //lower left
        if(column-i > -1 && row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8 && column-i-1 > -1){
                    if(board[row+i+1][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8 && column-1 > -1){
            if(board[row+1][column-1] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'b'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'B'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }

    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){
            board[row][column] = 'x';   //reseting bishop's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating bishop's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text

        }
    }

}
void moveQueen(char board[8][8],int row,int column, FILE *moves){

    char pieces[6] = {""};
    if(board[row][column] == 'q'){
        strcat(pieces,"RKBQGP");
    }
    else{
        strcat(pieces,"rkbqgp");
    }

    char letters[40];
    int numbers[40];

    int counter = 0;
    char table[8] = {"ABCDEFGH"};

    for(int i = 1 ; board[row][column+i] == 'x' ; i++){     //right
        if(column+i < 8){
            numbers[counter] = (8-row);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(column+i+1 < 8){
                    if(board[row][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(column+1 < 8){
            if(board[row][column+1] == pieces[i]){
                numbers[counter] = (8-row);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row][column-i] == 'x' ; i++){     //left
        if(column-i > -1){
            numbers[counter] = (8-row);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(column-i-1 > -1){
                    if(board[row][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(column-1 > -1){
            if(board[row][column-1] == pieces[i]){
                numbers[counter] = (8-row);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row-i][column] == 'x' ; i++){     //up
        if(row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1){
                    if(board[row-i-1][column] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1){
            if(board[row-1][column] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column] == 'x' ; i++){     //down
        if(row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8){
                    if(board[row+i+1][column] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8){
            if(board[row+1][column] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row-i][column+i] == 'x' ; i++){     //upper right
        if(column+i < 8 && row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1 && column+i+1 < 8){
                    if(board[row-i-1][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1 && column+1 < 8){
            if(board[row-1][column+1] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row-i][column-i] == 'x' ; i++){     //upper left
        if(column-i > -1 && row-i > -1){
            numbers[counter] = (8-row+i);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row-i-1 > -1 && column-i-1 > -1){
                    if(board[row-i-1][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row+i+1);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row-1 > -1 && column-1 > -1){
            if(board[row-1][column-1] == pieces[i]){
                numbers[counter] = (8-row+1);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column+i] == 'x' ; i++){     //lower right
        if(column+i < 8 && row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column+i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8 && column+i+1 < 8){
                    if(board[row+i+1][column+i+1] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column+i+1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8 && column+1 < 8){
            if(board[row+1][column+1] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column+1];
                counter++;
            }
        }
    }
    for(int i = 1 ; board[row+i][column-i] == 'x' ; i++){     //lower left
        if(column-i > -1 && row+i < 8){
            numbers[counter] = (8-row-i);
            letters[counter] = table[column-i];
            counter++;

            for(int j = 0 ; j < 6 ; j++){
                if(row+i+1 < 8 && column-i-1 > -1){
                    if(board[row+i+1][column-i-1] == pieces[j]){
                        numbers[counter] = (8-row-i-1);
                        letters[counter] = table[column-i-1];
                        counter++;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < 6 ; i++){
        if(row+1 < 8 && column-1 > -1){
            if(board[row+1][column-1] == pieces[i]){
                numbers[counter] = (8-row-1);
                letters[counter] = table[column-1];
                counter++;
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'q'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'Q'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }
    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){
            board[row][column] = 'x';   //reseting queen's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating queen's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text
        }
    }
}
void moveKing(char board[8][8],int row,int column, FILE *moves){

    char pieces[6] = {""};
    if(board[row][column] == 'g'){
        strcat(pieces,"RKBQGP");
    }
    else{
        strcat(pieces,"rkbqgp");
    }

    char letters[10];
    int numbers[10];

    int counter = 0;
    char table[8] = {"ABCDEFGH"};

    if(column-1 > -1){
        if(board[row][column-1] == 'x'){        //left
            numbers[counter] = (8-row);
            letters[counter] = table[column-1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row][column-1] == pieces[i]){
                    numbers[counter] = (8-row);
                    letters[counter] = table[column-1];
                    counter++;
                }
            }
        }
        if(row-1 > -1){
            if(board[row-1][column-1] == 'x'){        //upper left
                numbers[counter] = (8-row+1);
                letters[counter] = table[column-1];
                counter++;
            }
            else{
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row-1][column-1] == pieces[i]){
                        numbers[counter] = (8-row+1);
                        letters[counter] = table[column-1];
                        counter++;
                    }
                }
            }
        }
    }
    if(column+1 < 8){
        if(board[row][column+1] == 'x'){        //right
            numbers[counter] = (8-row);
            letters[counter] = table[column+1];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row][column+1] == pieces[i]){
                    numbers[counter] = (8-row);
                    letters[counter] = table[column+1];
                    counter++;
                }
            }
        }
        if(row+1 < 8){
            if(board[row+1][column+1] == 'x'){        //right down
                numbers[counter] = (8-row-1);
                letters[counter] = table[column+1];
                counter++;
            }
            else{
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row+1][column+1] == pieces[i]){
                        numbers[counter] = (8-row-1);
                        letters[counter] = table[column+1];
                        counter++;
                    }
                }
            }
        }
    }
    if(row-1 > -1){
        if(board[row-1][column] == 'x'){        //up
            numbers[counter] = (8-row+1);
            letters[counter] = table[column];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row-1][column] == pieces[i]){
                    numbers[counter] = (8-row+1);
                    letters[counter] = table[column];
                    counter++;
                }
            }
        }
        if(column+1 < 8){
            if(board[row-1][column+1] == 'x'){        //upper right
                numbers[counter] = (8-row+1);
                letters[counter] = table[column+1];
                counter++;
            }
            else{
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row-1][column+1] == pieces[i]){
                        numbers[counter] = (8-row+1);
                        letters[counter] = table[column+1];
                        counter++;
                    }
                }
            }
        }
    }
    if(row+1 < 8){
        if(board[row+1][column] == 'x'){        //down
            numbers[counter] = (8-row-1);
            letters[counter] = table[column];
            counter++;
        }
        else{
            for(int i = 0 ; i < 6 ; i++){
                if(board[row+1][column] == pieces[i]){
                    numbers[counter] = (8-row-1);
                    letters[counter] = table[column];
                    counter++;
                }
            }
        }
        if(column-1 > -1){
            if(board[row+1][column-1] == 'x'){        //down left
                numbers[counter] = (8-row-1);
                letters[counter] = table[column-1];
                counter++;
            }
            else{
                for(int i = 0 ; i < 6 ; i++){
                    if(board[row+1][column-1] == pieces[i]){
                        numbers[counter] = (8-row-1);
                        letters[counter] = table[column-1];
                        counter++;
                    }
                }
            }
        }
    }

    char newline;
    if(counter == 0){
        printf("\nThis piece has not any potential move. Please select another one!!!...\n\n");
        if(board[row][column] == 'g'){
            scanf("%c",&newline);
            selectionBlack(board,moves);
            return;
        }
        else if(board[row][column] == 'G'){
            scanf("%c",&newline);
            selectionWhite(board,moves);
            return;
        }
    }

    printf("\nPress...");
    for(int i = 0 ; i < counter ; i++){
        printf("  %d.%c%d",i+1,letters[i],numbers[i]);
    }

    int choice;
    printf("\n\n");
    scanf("%d",&choice);

    char choosenPiece = board[row][column];

    system("cls");

    for(int i = 1 ; i <= counter ; i++){
        if(choice == i){
            board[row][column] = 'x';   //reseting king's previous location

            int row1 = row;
            int column1 = column;
            column = (int)letters[i-1]-65;
            row = 8-numbers[i-1];

            if(board[row][column] != 'x'){
                eliminate(board, row, column, choosenPiece, row1, column1, moves);
                break;
            }
            board[row][column] = choosenPiece;   //updating king's current location

            movesToText(row, column, choosenPiece, row1, column1, moves);   //prints move to text
        }
    }
}

void printBoard(char board[8][8]){

    printf("\n............................................................\n\n");

    for(int i = 0 ; i < 8 ; i++){

        printf("\t%d    ",8-i);      //the numbers on the board

        for(int j = 0 ; j < 8 ; j++){

            switch(board[i][j]){
                case 'x':
                    printf("0   ");   //space
                    break;
                case 'p':
                    printf("BP  ");  //black pawn
                    break;
                case 'P':
                    printf("WP  ");  //white pawn
                    break;
                case 'r':
                    printf("BR  ");  //black rock
                    break;
                case 'R':
                    printf("WR  ");  //white rock
                    break;
                case 'k':
                    printf("BK  ");  //black knight
                    break;
                case 'K':
                    printf("WK  ");  //white knight
                    break;
                case 'b':
                    printf("BB  ");  //black bishop
                    break;
                case 'B':
                    printf("WB  ");  //white bishop
                    break;
                case 'q':
                    printf("BQ  ");  //black queen
                    break;
                case 'Q':
                    printf("WQ  ");  //white queen
                    break;
                case 'g':
                    printf("BG  ");  //black king
                    break;
                case 'G':
                    printf("WG  ");  //white king
                    break;
                default:
                    printf("!");    //if there is any error
                    break;
                }
        }
        printf("\n\n");
    }

    printf("\t     A   B   C   D   E   F   G   H\n\n");   //for letters on the board

}

void printToText(char board[8][8],FILE *fptr);

int main(){

    char newline;
    char board[8][8] =     {"rkbqgbkr",
                            "pppppppp",     //uppercase for white
                            "xxxxxxxx",     //lowercase for black
                            "xxxxxxxx",     //x for space
                            "xxxxxxxx",
                            "xxxxxxxx",     //coded board
                            "PPPPPPPP",
                            "RKBQGBKR" };

    FILE *fptr;
    FILE *moves;

    moves = fopen("moves.txt","w");
    fclose(moves);

    printf("Chess Board (t - 0):");
    printBoard(board);

    fptr = fopen("board.txt","w");
    printToText(board,fptr);
    fclose(fptr);

    for(int i = 0 ;  ; i++){

        moves = fopen("moves.txt","a");

        printf("Player 1 (White):\n\n");        //white takes turn
        selectionWhite(board, moves);
        scanf("%c",&newline);

        fclose(moves);



        printf("Chess Board (t - %d):",i);      //printing board after white's move
        printBoard(board);

        fptr = fopen("board.txt","w");      //writing board to file
        printToText(board,fptr);

        if(gameControl(board, fptr) == 1){      //checking kings on board
            break;
        }
        fclose(fptr);


        moves = fopen("moves.txt","a");

        printf("Player 2 (Black):\n\n");        //black takes turn
        selectionBlack(board,moves);
        scanf("%c",&newline);

        fclose(moves);




        printf("Chess Board (t - %d):",i+1);        //printing board after black's move
        printBoard(board);

        fptr = fopen("board.txt","w");      //writing board to file
        printToText(board,fptr);

        if(gameControl(board, fptr) == 1){      //checking kings on board
            break;
        }
        fclose(fptr);

    }
    system("pause");

    return 0;
}

void printToText(char board[8][8], FILE *fptr){

    fprintf(fptr,"\n\n");

    for(int i = 0 ; i < 8 ; i++){

        fprintf(fptr,"\t%d    ",8-i);      //the numbers on the board

        for(int j = 0 ; j < 8 ; j++){

            switch(board[i][j]){
                case 'x':
                    fprintf(fptr,"0   ");   //space
                    break;
                case 'p':
                    fprintf(fptr,"BP  ");  //black pawn
                    break;
                case 'P':
                    fprintf(fptr,"WP  ");  //white pawn
                    break;
                case 'r':
                    fprintf(fptr,"BR  ");  //black rock
                    break;
                case 'R':
                    fprintf(fptr,"WR  ");  //white rock
                    break;
                case 'k':
                    fprintf(fptr,"BK  ");  //black knight
                    break;
                case 'K':
                    fprintf(fptr,"WK  ");  //white knight
                    break;
                case 'b':
                    fprintf(fptr,"BB  ");  //black bishop
                    break;
                case 'B':
                    fprintf(fptr,"WB  ");  //white bishop
                    break;
                case 'q':
                    fprintf(fptr,"BQ  ");  //black queen
                    break;
                case 'Q':
                    fprintf(fptr,"WQ  ");  //white queen
                    break;
                case 'g':
                    fprintf(fptr,"BG  ");  //black king
                    break;
                case 'G':
                    fprintf(fptr,"WG  ");  //white king
                    break;
                default:
                    fprintf(fptr,"!");    //if there is any error
                    break;
                }
        }
        fprintf(fptr,"\n\n");
    }

    fprintf(fptr,"\t     A   B   C   D   E   F   G   H\n");   //for letters on the board

}
void selectionWhite(char board[8][8], FILE *moves){

    char letter,newline;
    int number;
    char piece;

    select:

        printf("Select a Piece: \n");
        scanf("%c%d",&letter,&number);

        switch(letter){
            case 'A':
                piece = board[8-number][(int)letter-65];
                break;
            case 'B':
                piece = board[8-number][(int)letter-65];
                break;
            case 'C':
                piece = board[8-number][(int)letter-65];
                break;
            case 'D':
                piece = board[8-number][(int)letter-65];
                break;
            case 'E':
                piece = board[8-number][(int)letter-65];
                break;
            case 'F':
                piece = board[8-number][(int)letter-65];
                break;
            case 'G':
                piece = board[8-number][(int)letter-65];
                break;
            case 'H':
                piece = board[8-number][(int)letter-65];
                break;
            default:
                printf("\nIncorrect Selection. ");
                scanf("%c",&newline);
                goto select;
        }

        switch(piece){
            case 'P':     //pawn
                movePawn(board,8-number,(int)letter-65,moves);
                break;
            case 'R':     //rock
                moveRock(board,8-number,(int)letter-65,moves);
                break;
            case 'K'://knight
                moveKnight(board,8-number,(int)letter-65,moves);
                break;
            case 'B':    //bishop
                moveBishop(board,8-number,(int)letter-65,moves);
                break;
            case 'Q':      //queen
                moveQueen(board,8-number,(int)letter-65,moves);
                break;
            case 'G':      //king
                moveKing(board,8-number,(int)letter-65,moves);
                break;
            default:
                printf("\nPlease just select white pieces!!!...\n\n");
                scanf("%c",&newline);
                goto select;

        }

}
void selectionBlack(char board[8][8], FILE *moves){

    char letter,newline;
    int number;
    char piece;

    select:

        printf("Select a Piece: \n");
        scanf("%c%d",&letter,&number);

        switch(letter){
            case 'A':
                piece = board[8-number][(int)letter-65];
                break;
            case 'B':
                piece = board[8-number][(int)letter-65];
                break;
            case 'C':
                piece = board[8-number][(int)letter-65];
                break;
            case 'D':
                piece = board[8-number][(int)letter-65];
                break;
            case 'E':
                piece = board[8-number][(int)letter-65];
                break;
            case 'F':
                piece = board[8-number][(int)letter-65];
                break;
            case 'G':
                piece = board[8-number][(int)letter-65];
                break;
            case 'H':
                piece = board[8-number][(int)letter-65];
                break;
            default:
                printf("\nIncorrect Selection. ");
                scanf("%c",&newline);
                goto select;
        }

        switch(piece){
            case 'p':      //pawn
                movePawn(board,8-number,(int)letter-65,moves);
                break;
            case 'r':      //rock
                moveRock(board,8-number,(int)letter-65,moves);
                break;
            case 'k':   //knight
                moveKnight(board,8-number,(int)letter-65,moves);
                break;
            case 'b':    //bishop
                moveBishop(board,8-number,(int)letter-65,moves);
                break;
            case 'q':   //queen
                moveQueen(board,8-number,(int)letter-65,moves);
                break;
            case 'g':     //king
                moveKing(board,8-number,(int)letter-65,moves);
                break;
            default:
                printf("\nPlease just select black pieces!!!...\n\n");
                scanf("%c",&newline);
                goto select;
        }

}







