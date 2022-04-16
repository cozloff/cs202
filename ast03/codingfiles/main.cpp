/*
 * Name: Dylan Cozloff, 2001668380, Assignment 03
 * Description: Plays a chess game with selected piece. 
 * Input: Choose seed, tutorial mode, difficulty, piece type, piece movement.  
 * Output: Movements on the chess board.
 */
#include "battleChess.h"
#include <vector>
using namespace std;

/*****************************
 * MAIN CODE FOR BATTLE CHESS
 * This file hosts the game
 * 
 * YOU DO NOT HAVE TO EDIT
 * THIS FILE!!
*****************************/

//Function Prototypes
piece getPlayerPiece(unsigned int selection);
piece getRandomPiece(unsigned int position);
void checkForLostPieces(bool &playerRemains, unsigned int playerID, vector<piece> &pieces);
void playGame(unsigned int difficulty, char tutorial, unsigned int chessPiece);


int main(){
    cout << "Welcome to Battle Chess (TM)!" << endl; 
    cout << "Please enter the seed for your game : " << endl; 
    unsigned int seed = 0;
    cin >> seed;
    srand(seed);
    cout << "Tutorial Mode? (Y/N) : " << endl;
    char tutorial = 'Y'; 
    while(true){
        cin >> tutorial;
        if(tutorial == 89 || tutorial == 78){
            break;
        }
    }
    cout << "Please enter the difficulty level (1-3) : " << endl;
    unsigned int difficultyLevel = 0; 
    while(true){
        cin >> difficultyLevel;
        if(difficultyLevel > 0 && difficultyLevel < 4){
            break;
        }
    }

    cout << "Pick your chess piece!" << endl;
    cout << "---------------------------" << endl
        << "||     The Barracks      ||" << endl
        << "---------------------------" << endl
        << "|| (0) pawn          [P] ||" << endl
        << "|| (1) forwardKnight [X] ||" << endl
        << "|| (2) leftRook      [#] ||" << endl
        << "|| (3) rightRook     [%] ||" << endl
        << "|| (4) leftBishop    [&] ||" << endl
        << "|| (5) rightBishop   [Q] ||" << endl
        << "---------------------------" << endl;
    unsigned int chessPiece = 6; 
    while(true){
        cin >> chessPiece;
        if(chessPiece >= 0 && chessPiece < 6){
            break;
        }
    }
    playGame(difficultyLevel,tutorial,chessPiece);
}

// Returns the piece corresponding to the players selection
piece getPlayerPiece(unsigned int selection){
    unsigned int startX = entity::getWidth() / 2;
    unsigned int startY = entity::getHeight() - 1;
    switch(selection){
        case(1) : {return forwardKnight(startY , startX);}
        case(2) : {return leftRook(startY , startX);}
        case(3) : {return rightRook(startY , startX);}
        case(4) : { return leftBishop(startY , startX);}
        case(5) : {return rightBishop(startY , startX);}
        default : {return pawn(startY , startX);}
    }
    return pawn(startY , startX);
}

// Returns a random piece
// It will place the piece away from the others using the "position" param
piece getRandomPiece(unsigned int position){
    const unsigned int startY = 0;
    switch(rand() % 6){
        case(0) : {
            return pawn(startY + (position * 3),entity::getWidth() / 2);
        }
        case(1) : {
            return forwardKnight(startY + (position * 3),entity::getWidth() / 2);
        }
        case(2) : {
            return rightRook(startY + (position * 3),entity::getWidth() / 2);
        }
        case(3) : {
            return leftRook(startY + (position * 3),entity::getWidth() / 2);
        }
        case(4) : {
            return rightBishop(startY + (position * 3),entity::getWidth() / 2);
        }
        case(5) : {
            return leftBishop(startY + (position * 3),entity::getWidth() / 2);
        }
    }
    return pawn(startY + (position * 3), entity::getWidth() / 2);
}

// Checks to see if any pieces got knocked out.
void checkForLostPieces(bool &playerRemains, unsigned int playerID, vector<piece> &pieces){
    // Vector for remaining pieces
    vector<piece> remaining;
    // Bool to see if the player remains
    playerRemains = false;
    // For the entire grid
    for(unsigned int i = 0; i < entity::getHeight(); i++){
        for(unsigned int j = 0; j < entity::getWidth(); j++){
            // If there is a piece here
            if(!entity::isEmptyEntity(i,j)){
                // Find the piece in the vector
                for(unsigned int k = 0; k < pieces.size(); k++){
                    // If found
                    if(pieces[k].getId() == entity::getId(i,j)){
                        // Add it to remaining pieces
                        remaining.push_back(pieces[k]);
                    }
                }
                // If this piece is the player
                if(entity::getId(i,j) == playerID){
                    // The player is still playing
                    playerRemains = true;
                }
            }
        }
    }
    if(pieces.size() != remaining.size()){
        cout << "Piece knocked out!" << endl;
    }
    if(!playerRemains){
        cout << "You Lost!" << endl; 
    }
    // Sort them to perserve order of turns
    if(remaining.size() > 1){
        for(unsigned int i = 0; i < remaining.size() - 1; i++){
            for(unsigned int j = 0; j < remaining.size() - i - 1; j++){
                if(remaining[j].getId() > remaining[j+1].getId()){
                    piece temp = remaining[j];
                    remaining[j] = remaining[j+1];
                    remaining[j+1] = temp;
                }
            }
        }
    }
    pieces = remaining;
    return;
}

// Function to play one game of battle chess
void playGame(unsigned int difficulty, char tutorial, unsigned int chessPiece){
    vector<piece> pieces;
    const unsigned int startY = 0;
    /* First, add all pieces to the board. */
    // Having one pawn ensure game end
    pieces.push_back(pawn(startY,(entity::getWidth() / 2)));
    // Add remaining pieces
    for(unsigned int i = 1; i < difficulty ; i++){
        if(tutorial == 'Y'){
            pieces.push_back(pawn(startY + (i * 3),(entity::getWidth() / 2)) );
        }
        else{
            pieces.push_back(getRandomPiece(i));
        }
        cout << "Piece " << pieces[i].getId() << " added to the board!" << endl;
    }
    // Add the player piece
    pieces.push_back(getPlayerPiece(chessPiece));
    unsigned int playerPiece = pieces[pieces.size() - 1].getId();
    cout << "Player is piece " << playerPiece << endl;
    cout << "***************************************" << endl
        << "||           GAME START              ||" << endl
        << "***************************************" << endl << endl;

    entity::printGrid();
    // Begin game
    while(true){
        // For all pieces
        for(unsigned int i = 0; i < pieces.size(); i++){
            // If computer player
            if(pieces[i].getId() != playerPiece){
                cout << pieces[i].getId() << " is moving." << endl;
                // Move randomly
                pieces[i].randomMove();
            }
            // If player
            else{
                cout << "Player is moving." << endl;
                // Prompt and move
                pieces[i].move();
            }
            // Print current board
            entity::printGrid();
            bool playerRemains = false;
            // Check to see if anyone got knocked out
            checkForLostPieces(playerRemains,playerPiece,pieces);
            // If the player does not remain, you lost
            if(!playerRemains){
                return;
            }
            // If no more players are left, you won
            else if(playerRemains && pieces.size() == 1){
                cout << "You won!" << endl;
                return;
            }
        }
    }
}