/*
 * Name: Dylan Cozloff, 2001668380, Assignment 05
 * Description: Plays a miner game 
 * Input: Game functions such as move and mine
 * Output: Mines the certain block, and returns the subsequent reward or penalty
 */
#include "digAdventureObjects.h"
using namespace std;

/*************************************
 * entity function definitions
*************************************/
// YOUR CODE HERE
entity::~entity(){} //entity destructor

bool entity::display_messages = true; //tells the objects if they should print their message, static initialized to true

entity::entity(char x){ //constructor that needs to intialize the shape of the object
    shape = x; //initialize shape with parameter
}

char entity::getShape() const{ //return the shape
    return shape; 
} 

unsigned int entity::destroy() const{//called if the miner attempts to destroy an empty space
    cout<<NOTH_MSG_DTSY<<endl; //prints the NOTH_MSG_DTSY
    return NOTHING; //returns NOTHING
} 

/*************************************
 * miner function definitions
*************************************/
// YOUR CODE HERE
miner::miner() 
        : entity('M'){ //The default constructor
    spike_armor = 0; //0 armor
    point_total = 0; //0 points
    is_alive = true; //is alive
    height = 1; //1 on the grid
    width = 1; //1 on the grid
}

miner::miner(unsigned int x, unsigned int y)
        : entity('M'){ //The parameter constructor
    spike_armor = 0; //0 armor
    point_total = 0; //0 points
    is_alive = true; //is alive
    height = x; //parameter height
    width = y; //parameter width
}

miner::~miner(){ //destructor
    if(entity::display_messages == true){ //if display is on 
        cout<<MINR_MSG_DTOR<<endl; //display MINR_MSG_DTOR
        entity::display_messages = false; //set display to false 
    }
}
unsigned int miner::destroy(){ // called from the miner if silverfish attack
    cout<<MINR_MSG_DSTY<<endl; //display MINR_MSG_DSTY
    if(spike_armor < 1){ //if no armor
        is_alive = false; //kill him
    }
    else{
        spike_armor--; //if armor deplete armor
    }
    return MINER; //return MINER
}

void miner::givePoints(int x){ //add points to the point total
    point_total = point_total + x; //add parameter to point total
}

int miner::getPoints() const{ //returns the point total
    return point_total; 
} 

void miner::armorUp(){ //adds 1 to spike armor variable
    spike_armor++; 
}

bool miner::isStillAlive() const{ //returns is alive
    return is_alive; 
}

void miner::updateLocation(unsigned int x, unsigned int y){ //change the miner’s height and width to match the parameters
    height = x; 
    width = y; 
}

unsigned int miner::getHeight() const{ //return the height
    return height; 
}

unsigned int miner::getWidth() const{ //return the width
    return width; 
}

unsigned int miner::getArmor() const{ //return the spike armor
    return spike_armor; 
}

/*************************************
 * empty_space function definitions
*************************************/
// YOUR CODE HERE
empty_space::empty_space() 
        : entity(' '){}//Passes a space ’ ’ as a shape

/*************************************
 * hardened_wall function definitions
*************************************/
// YOUR CODE HERE
hardened_wall::hardened_wall() 
        : entity('#'){}//Passes a space ’#’ as a shape

unsigned int hardened_wall::destroy() const{ //Print the WALL MSG DSTY message and return WALL
    cout<<WALL_MSG_DTSY<<endl;
    return WALL; 
}

/*************************************
 * rock function definitions
*************************************/
// YOUR CODE HERE
rock::rock() 
        : entity('0'){}//Passes a space ’0’ as a shape

rock::~rock(){ //Checks to see if messages are being displayed
    if(entity::display_messages == true){ //if its being displayed
        cout<<ROCK_MSG_DTOR<<endl; //print the ROCK_MSG_DTOR
    }
}

unsigned int rock::destroy() const{ //Print the ROCK MSG DSTY message and return ROCK
    cout<<ROCK_MSG_DTSY<<endl;
    return ROCK;
}

/*************************************
 * carnivorous_silverfish function definitions
*************************************/
// YOUR CODE HERE
carnivorous_silverfish::carnivorous_silverfish() 
        : entity('0'){}//Passes a space ’0’ as a shape

carnivorous_silverfish::~carnivorous_silverfish(){ //Checks to see if messages are being displayed
    if(entity::display_messages == true){ //if its being displayed
        cout<<FISH_MSG_DTOR<<endl; //print the FISH_MSG_DTOR
    }
}

unsigned int carnivorous_silverfish::destroy() const{ //Print the FISH MSG DSTY message and return SILVERFISH
    cout<<FISH_MSG_DTSY<<endl;
    return SILVERFISH;
}

/*************************************
 * spike_armor function definitions
*************************************/
// YOUR CODE HERE
spike_armor::spike_armor() 
        : entity('^'){}//Passes a space ’^’ as a shape

spike_armor::~spike_armor(){ //Checks to see if messages are being displayed
    if(entity::display_messages == true){ //if its being displayed
        cout<<ARMR_MSG_DTOR<<endl; //print the ARMR_MSG_DTOR
    }
}

unsigned int spike_armor::destroy() const{ //Print the ARMR MSG DSTY message and return ARMOR
    cout<<ARMR_MSG_DTSY<<endl;
    return ARMOR;
}

/*************************************
 * hidden_treasure function definitions
*************************************/
// YOUR CODE HERE
hidden_treasure::hidden_treasure() 
        : entity('$'){}//Passes a space ’$’ as a shape

hidden_treasure::~hidden_treasure(){ //Checks to see if messages are being displayed
    if(entity::display_messages == true){ //if its being displayed
        cout<<TRSR_MSG_DTOR<<endl; //print the TRSR_MSG_DTOR
    }
}

unsigned int hidden_treasure::destroy() const{ //Print the TRSR MSG DSTY message and return TREASURE
    cout<<TRSR_MSG_DTSY<<endl;
    return TREASURE;
}

/*************************************
 * mine_exit function definitions
*************************************/
// YOUR CODE HERE
mine_exit::mine_exit() 
        : entity('E'){}//Passes a space ’E’ as a shape

mine_exit::~mine_exit(){ //Checks to see if messages are being displayed
    if(entity::display_messages == true){ //if its being displayed
        cout<<EXIT_MSG_DTOR<<endl; //print the EXIT_MSG_DTOR
    }
    display_messages = false; 
}

unsigned int mine_exit::destroy() const{ //Print the EXIT MSG DSTY message and return EXIT
    cout<<EXIT_MSG_DTSY<<endl;
    return EXIT;
}