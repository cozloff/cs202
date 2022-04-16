/*
 * Name: Dylan Cozloff, 2001668380, Assignment 05
 * Description: Plays a miner game 
 * Input: Game functions such as move and mine
 * Output: Mines the certain block, and returns the subsequent reward or penalty
 */
#include "digAdventureObjects.h"
#include <string>

#define GAME_CONTINUE	0
#define GAME_EXIT_LOSE	1
#define GAME_EXIT_WIN	2
#define GAME_ERROR	   -1

class dig_adventure_game {
private:
	entity ***game_grid = nullptr; //This is the triple pointer where the game is held
	unsigned int game_width = 10; //The height of the grid (indexed first).
	unsigned int game_height = 10; //The width of the grid
	unsigned int difficulty = 1; //The difficulty of the game
	miner *player = nullptr; //A pointer to the miner object that the player is controlling

	void allocateGrid(); //This function should allocate the 2D grid
	void deallocateGrid(); //This function should deallocate the memory used for the game grid
	entity *allocateEntity(unsigned int); //A helper function used to allocate different derived objects

	void populateGrid(); //randomly populates all the nullptrs in the grid with objects

	void moveMiner(unsigned int nh, unsigned int nw); //This function needs to move the miner within the grid
public:
	dig_adventure_game(unsigned int, unsigned int, unsigned int); //The constructor for a game

	~dig_adventure_game(); //The destructor checks to see if the miner has been deallocated
	dig_adventure_game(const dig_adventure_game &copy); //The copy constructor
	void operator=(const dig_adventure_game &copy); //The assignment operator overload

	unsigned int playerMove(); //This function is responsible for one turn
	void playGame(); //An infinite loop that prints the grid and then calls playerMove()
	void printGrid() const; //Prints the grid with the score and armor
};
