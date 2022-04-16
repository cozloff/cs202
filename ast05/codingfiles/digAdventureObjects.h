/*
 * Name: Dylan Cozloff, 2001668380, Assignment 05
 * Description: Plays a miner game 
 * Input: Game functions such as move and mine
 * Output: Mines the certain block, and returns the subsequent reward or penalty
 */
#include <iostream>
using namespace std;

#define NOTHING     0
#define ROCK        1
#define SILVERFISH  2
#define ARMOR       3
#define TREASURE    4
#define WALL        5
#define EXIT        6 
#define MINER       7

/* empty_space and entity messages */
#define NOTH_MSG_DTSY "There is nothing here to dig..."
/* miner messages */
#define MINR_MSG_DSTY "The miner is attacked by Carnivorous Silverfish!"
#define MINR_MSG_DTOR "AAAAAAAGHHHHHHHHH!"
/* hardened_wall messages */
#define WALL_MSG_DTSY "The miner attempts to dig through the hardened wall. It cannot be destroyed."
/* rock messages */
#define ROCK_MSG_DTSY "The miner digs through some ordinary rock."
#define ROCK_MSG_DTOR "*crumbles*"
/* carnivorous_silverfish messages */
#define FISH_MSG_DTSY "The miner digs into rock invested with Carnivorous Silverfish!"
#define FISH_MSG_DTOR "*the silverfish hiss as they perish to the miner's spike armor*"
/* armor messages */
#define ARMR_MSG_DTSY "The miner digs up a component of the Spike Armor set!"
#define ARMR_MSG_DTOR "*the miner equips the spike armor*"
/* hidden_treasure messages */
#define TRSR_MSG_DTSY "The miner digs up some Hidden Treasure!"
#define TRSR_MSG_DTOR "*the miner stuffs shiny gems into their bag*"
/* exit messages */
#define EXIT_MSG_DTSY "The miner digs through the Exit!"
#define EXIT_MSG_DTOR "Congrats! You WIN!"

/*************************************
 * entity
*************************************/
// YOUR CODE HERE
class entity{
private:
    char shape; //this is what an entity will display as in the 2D grid
protected:
    static bool display_messages; //tells the objects if they should print their message
    entity(char); //constructor that needs to intialize the shape of the object
public:
    char getShape() const; //return the shape
    virtual unsigned int destroy() const; //called if the miner attempts to destroy an empty space
    virtual ~entity() = 0; //destructor 
};

/*************************************
 * miner
*************************************/
// YOUR CODE HERE
class miner : public entity{
private:
    unsigned int spike_armor; //The amount of armor the miner is wearing
    int point_total; //The amount of points the miner has
    bool is_alive; //tells the game if the miner survived the encounter or not
    unsigned int height; //The current height coordinate that corresponds to where the miner is in the grid
    unsigned int width; //The current width coordinate that corresponds to where the miner is in the grid
public:
    miner(); //The default constructor
    miner(unsigned int, unsigned int); //The parameter constructor
    ~miner(); //destructor
    unsigned int destroy(); // called from the miner if silverfish attack
    void givePoints(int); //add points to the point total
    int getPoints() const; //returns the point total
    void armorUp(); //adds 1 to spike armor variable
    bool isStillAlive() const; //returns is alive
    void updateLocation(unsigned int, unsigned int); //change the miner’s height and width to match the parameters
    unsigned int getHeight() const; //return the height
    unsigned int getWidth() const; //return the width
    unsigned int getArmor() const; //return the spike armor
};

/*************************************
 * empty_space
*************************************/
// YOUR CODE HERE
class empty_space : public entity{
public:
    empty_space(); //Passes a space ’ ’ as a shape
};

/*************************************
 * hardened_wall
*************************************/
// YOUR CODE HERE
class hardened_wall : public entity{
public:
    hardened_wall(); //Passes a pound sign ’#’ as a shape
    unsigned int destroy() const; //Print the WALL MSG DSTY message and return WALL
};

/*************************************
 * rock
*************************************/
// YOUR CODE HERE
class rock : public entity{
public:
    rock(); //Passes a zero ’0’ as a shape
    ~rock(); //Checks to see if messages are being displayed
    unsigned int destroy() const; //Print the ROCK MSG DSTY message and return ROCK
};

/*************************************
 * carnivorous_silverfish
*************************************/
// YOUR CODE HERE
class carnivorous_silverfish : public entity{
public:
    carnivorous_silverfish(); //Passes a zero ’0’ as a shape
    ~carnivorous_silverfish(); //Checks to see if messages are being dis- played
    unsigned int destroy() const; //Print the FISH MSG DSTY message and return SILVERFISH
};

/*************************************
 * spike_armor
*************************************/
// YOUR CODE HERE
class spike_armor : public entity{
public:
    spike_armor(); //Inlines a call to the entity constructor. Passes a hat ’ˆ’ as a shape
    ~spike_armor(); //Checks to see if messages are being displayed
    unsigned int destroy() const; //Print the ARMR MSG DSTY message and return ARMOR
};

/*************************************
 * hidden_treasure
*************************************/
// YOUR CODE HERE
class hidden_treasure : public entity{
public:
    hidden_treasure(); //Passes a dollar sign ’$’ as a shape
    ~hidden_treasure(); //Checks to see if messages are being displayed
    unsigned int destroy() const; //Print the TRSR MSG DSTY message and return TREASURE
};

/*************************************
 * mine_exit
*************************************/
// YOUR CODE HERE
class mine_exit : public entity{
public:
    mine_exit(); //Passes an ’E’ as a shape
    ~mine_exit(); //Checks to see if messages are being displayed
    unsigned int destroy() const; //Print the EXIT MSG DSTY message and return EXIT
};