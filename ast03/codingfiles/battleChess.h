/*
 * Name: Dylan Cozloff, 2001668380, Assignment 03
 * Description: Plays a chess game with selected piece. 
 * Input: Choose seed, tutorial mode, difficulty, piece type, piece movement.  
 * Output: Movements on the chess board.
 */
#include <iostream>
/******************************
 *  Entity Class
 * ---------------------------
    All things in the board
    are entities. There is 
    even an empty entity. 
******************************/
class entity{
private:
    // The shape of the entity
    // Empty entites have the shape of ' ' (space)
    char shape;
protected:
    // Some entities may have an ID
    // This allows us to tell entites apart. 
    unsigned int id = 0;
    // Location of entity in grid 
    unsigned int i_coord, j_coord; 
    // The idCounter is used to assign unique ids to entities
    static unsigned int idCounter;
    // Number of entities in the board (including empty entites)
    static unsigned int number_of_entities;
    // Board dimensions
    static const unsigned int grid_height = 10;
    static const unsigned int grid_width = 10;
    // The board
    static entity grid[grid_width][grid_height];
    // All constructors for entity are protected 
    // This means that main() cannot declare entities
    // Default ctor
    entity();
    // Param ctor used to place entity in a particular spot on the board
    entity(unsigned int, unsigned int, char);
    // Copy ctor
    entity(const entity &copy);
    // Move function allows entities to move to other spots on the board
    void move(unsigned int i, unsigned int j);
public:
    // Public destructor
    ~entity();
    // Getter for the shape of the entity
    char getShape() const;
    // Function to see if object (this) is an empty entity
    bool isEmptyEntity() const;
    // Getter for the id of the entity
    unsigned int getId() const;
    // Function to print the grid
    static void printGrid();
    // Function to place an empty entity
    static void placeEmptyEntity(unsigned int, unsigned int);
    // Function to get the number of entities
    static unsigned int getNumEntities();
    // Function to see if object is an empty entity
    static bool isEmptyEntity(unsigned int i, unsigned int j);
    // Function to see if the i,j params are in bounds
    static bool inBounds(unsigned int i, unsigned int j);
    // Functions to get dimensions of the board
    static unsigned int getWidth();
    static unsigned int getHeight();
    // Function to get the ID of an entity at a location on the board
    static unsigned int getId(unsigned int i, unsigned int j);
};

/********************************
 * piece CLASS (YOUR CODE HERE)
********************************/
class piece : public entity{
private:
    unsigned int direct_distance;
    int perpendicular_distance;
    unsigned static int number_of_pieces;
    char getRandomDirection() const; 
protected:
    piece(unsigned int d, int p, unsigned int i, unsigned int j, char s); 
    void computeNextCoordinate(char i, unsigned int& j, unsigned int& k) const;
    char promptDirection() const; 
public:
    ~piece(); 
    void move();
    void randomMove(); 
    static unsigned int getNumberOfPieces();
};
// piece class declaration...

/********************************
 * pawn CLASS (YOUR CODE HERE)
********************************/
class pawn : public piece{
public:
    pawn();
    pawn(unsigned int i, unsigned int j);
};
// pawn class declaration...

/********************************
 * forwardKnight CLASS (YOUR CODE HERE)
********************************/
class forwardKnight : public piece{
public:
    forwardKnight();
    forwardKnight(unsigned int i, unsigned int j);
};
// forwardKnight class declaration...

/********************************
 * leftRook CLASS (YOUR CODE HERE)
********************************/
class leftRook : public piece{
public:
    leftRook();
    leftRook(unsigned int i, unsigned int j);
};
// leftRook class declaration...

/********************************
 * rightRook CLASS (YOUR CODE HERE)
********************************/
class rightRook : public piece{
public:
    rightRook();
    rightRook(unsigned int i, unsigned int j);
};
// rightRook class declaration...

/********************************
 * leftBishop CLASS (YOUR CODE HERE)
********************************/
class leftBishop : public piece{
public:
    leftBishop();
    leftBishop(unsigned int i, unsigned int j);
};
// leftBishop class declaration...

/********************************
 * rightBishop CLASS (YOUR CODE HERE)
********************************/
class rightBishop : public piece{
public:
    rightBishop();
    rightBishop(unsigned int i, unsigned int j);
};
// rightBishop class declaration...