/*
 * Name: Dylan Cozloff, 2001668380, Assignment 03
 * Description: Plays a chess game with selected piece. 
 * Input: Choose seed, tutorial mode, difficulty, piece type, piece movement.  
 * Output: Movements on the chess board.
 */
#include "battleChess.h"
using namespace std;

/*******************************
 * I have given this function to you
*******************************/
void entity::printGrid(){ 
    // Print the top line
    for(unsigned int i = 0; i < grid_width * 2; i++){
        cout << "--";
    }
    cout << '-';
    cout << endl;
    // Print the grid
    for(unsigned int i = 0; i < grid_height; i++){
        cout << "| ";
        for(unsigned int j = 0; j < grid_width; j++){
            cout << grid[i][j].getShape() << " | ";
        }
        cout << endl;
        for(unsigned int j = 0; j < grid_width * 2; j++){
            cout << "--";
        }
        cout << '-';
        cout << endl;
    }
}

char piece::getRandomDirection() const{
    char entry = '\0';
    // Loop until proper entry
    while(true){
        // Get random direction
        switch(rand() % 4){
            case(0): { entry = 'L'; break; }
            case(1): { entry = 'R'; break; }
            case(2): { entry = 'U'; break; }
            case(3): { entry = 'D'; break; }
        }
        // Check to see if the piece can move that way
        unsigned int io = i_coord, jo = j_coord;
        computeNextCoordinate(entry,io,jo);
        // If they can move, break
        if(io != i_coord || jo != j_coord){
            break;
        }
    }
    return entry;
}

void piece::randomMove(){
    // Get a random direction
    char d = getRandomDirection();
    // Compute the next coordinates
    unsigned int i, j;
    computeNextCoordinate(d,i,j);
    // Save the old coordinates
    unsigned io = i_coord, jo = j_coord;
    // Move the entity to new location
    entity::move(i,j);
    // Overwrite the old location
    placeEmptyEntity(io,jo);
}



/***************************************************
*************** YOUR CODE HERE *********************
*** |   |   |   |   |   |   |   |   |   |   |   |***
*** V   V   V   V   V   V   V   V   V   V   V   V***
***----------------------------------------------***/

// Initialize all 3 entity static vars here
unsigned int entity::idCounter = 100;
unsigned int entity::number_of_entities = 0;
entity entity::grid[grid_width][grid_height];


bool entity::inBounds(unsigned int i, unsigned int j){
    // Your code here
    if(i >= 10 || i < 0){
        return false; 
    }
    if(j >= 10 || j < 0){
        return false;
    }
    return true; 
}

entity::entity(){
    // Your code here
    shape = ' ';
    i_coord = number_of_entities % grid_width;
    j_coord = number_of_entities / grid_width;
    grid[i_coord][j_coord] = (*this);
    number_of_entities++;
    id = 99999999; 
}

entity::entity(unsigned int i, unsigned int j, char s){
    // Your code here
    i_coord = i; 
    j_coord = j; 
    shape = s; 
    grid[i_coord][j_coord] = (*this);
    number_of_entities++;
}

entity::entity(const entity &copy){
    // Your code here
    i_coord = copy.i_coord; 
    j_coord = copy.j_coord; 
    id = copy.id;
    shape = copy.shape; 
    grid[i_coord][j_coord] = (*this);
    number_of_entities++;
}

entity::~entity(){
    // Your code here
    number_of_entities--; 
}

char entity::getShape() const{
    // Your code here
    return shape; 
}

void entity::move(unsigned int i, unsigned int j){
    // Your code here
    i_coord = i;
    j_coord = j; 
    grid[i_coord][j_coord] = (*this);
}

unsigned int entity::getWidth(){
    // Your code here
    return grid_width; 
}

unsigned int entity::getHeight(){
    // Your code here
    return grid_height; 
}

unsigned int entity::getId(unsigned int i, unsigned int j){
    // Your code here
    return grid[i][j].getId(); 
}

void entity::placeEmptyEntity(unsigned int i, unsigned int j){
    // Your code here
    entity emptyEntity; 
    grid[i][j] = emptyEntity; 
}

unsigned int entity::getNumEntities(){
    // Your code here
    return number_of_entities; 
}

bool entity::isEmptyEntity() const{
    // Your code here
    if(shape == ' '){
        return true; 
    }
    return false; 
}

bool entity::isEmptyEntity(unsigned int i, unsigned int j){
    // Your code here
    if(grid[i][j].isEmptyEntity()){
        return true; 
    }
    return false; 
}

unsigned int entity::getId() const{
    // Your code here
    return id; 
}

// Initialize static piece variable
unsigned int piece::number_of_pieces = 0;

// Piece constructor
piece::piece(unsigned int d, int p, unsigned int i, unsigned int j, char s) 
        : entity(i, j, s){
    direct_distance = d; 
    perpendicular_distance = p; 
    number_of_pieces++; 
    id = idCounter; 
    idCounter++; 
}

// Piece destructor
piece::~piece(){
    number_of_pieces--;
}

// computeNextCoordinate
void piece::computeNextCoordinate(char i, unsigned int& j, unsigned int& k) const{ 
    j = i_coord;
    k = j_coord;
    if(i=='L'){
        j = i_coord - perpendicular_distance; 
        k = j_coord - direct_distance;
    }
    if(i=='R'){
        j = i_coord + perpendicular_distance; 
        k = j_coord + direct_distance;
    }
    if(i=='U'){
        j = i_coord - direct_distance; 
        k = j_coord + perpendicular_distance;
    }
    if(i=='D'){
        j = i_coord + direct_distance; 
        k = j_coord - perpendicular_distance;
    }
    if(!inBounds(j, k)){
        j = i_coord;
        k = j_coord; 
    }
}

char piece::promptDirection() const{
    cout<<"What direction would you like to move?"<<endl; 
    cout<<"  -> (L)"<<endl; 
    cout<<"  -> (R)"<<endl;
    cout<<"  -> (U)"<<endl; 
    cout<<"  -> (D)"<<endl; 
    cout<<" :"<<endl; 
    char entry;
    cin>>entry; 
    while(entry!='L' && entry!='R' && entry!='U' && entry!='D'){
            cout<<"Invalid Entry."<<endl; 
            cout<<" :"<<endl;
            cin>>entry; 
    }
    unsigned int newi_coord, newj_coord; 
    newi_coord = i_coord; 
    newj_coord = j_coord;  
    computeNextCoordinate(entry, newi_coord, newj_coord);
    while(i_coord == newi_coord && j_coord == newj_coord){
        cout<<"Invalid Entry."<<endl; 
        cout<<" :"<<endl;
        cin>>entry;  
        newi_coord = i_coord; 
        newj_coord = j_coord; 
        computeNextCoordinate(entry, newi_coord, newj_coord);
        if(i_coord != newi_coord || j_coord != newj_coord){
            return entry; 
        }
    }
    return entry; 
}

void piece::move(){
    /*
    unsigned int lasti_coord = i_coord; 
    unsigned int lastj_coord = j_coord; 
    char x = promptDirection();
    computeNextCoordinate(x, i_coord, j_coord);
    entity::move(i_coord, j_coord); 
    placeEmptyEntity(lasti_coord , lastj_coord);
    */
  
    char x = promptDirection();
    // Compute the next coordinates
    unsigned int i, j;
    computeNextCoordinate(x,i,j);
    // Save the old coordinates
    unsigned io = i_coord, jo = j_coord;
    // Move the entity to new location
    entity::move(i,j);
    // Overwrite the old location
    placeEmptyEntity(io,jo);
}

unsigned int piece::getNumberOfPieces(){
    return number_of_pieces;
}

/***************************
 * I gave you:
  - piece::getRandomDirection
  - piece::randomMove()

They are up above. Go uncomment them 
or move them down here
***************************/

// Pawn ctors
pawn::pawn() 
        : piece(1, 0, 0, 0, 'P'){}

pawn::pawn(unsigned int i, unsigned int j)
        : piece(1, 0, i, j, 'P'){}

// forwardKnight ctors
forwardKnight::forwardKnight() 
        : piece(3, 0, 0, 0, 'X'){}

forwardKnight::forwardKnight(unsigned int i, unsigned int j)
        : piece(3, 0, i, j, 'X'){}

// leftRook ctors
leftRook::leftRook() 
        : piece(2, -1, 0, 0, '#'){}

leftRook::leftRook(unsigned int i, unsigned int j)
        : piece(2, -1, i, j, '#'){}

// rightRook ctors
rightRook::rightRook() 
        : piece(2, 1, 0, 0, '%'){}

rightRook::rightRook(unsigned int i, unsigned int j)
        : piece(2, 1, i, j, '%'){}

// leftBishop ctors
leftBishop::leftBishop() 
        : piece(1, -2, 0, 0, '&'){}

leftBishop::leftBishop(unsigned int i, unsigned int j)
        : piece(1, -2, i, j, '&'){}

// rightBishop ctors
rightBishop::rightBishop() 
        : piece(1, 2, 0, 0, 'Q'){}

rightBishop::rightBishop(unsigned int i, unsigned int j)
        : piece(1, 2, i, j, 'Q'){}
