/*
 * Name: Dylan Cozloff, 2001668380, Assignment 05
 * Description: Plays a miner game 
 * Input: Game functions such as move and mine
 * Output: Mines the certain block, and returns the subsequent reward or penalty
 */
#include "digAdventureGame.h"

using namespace std;
/*******************************
 * Student Functions
*******************************/
void dig_adventure_game::allocateGrid() { //This function should allocate the 2D grid
	// YOUR CODE HERE
	if(game_grid != nullptr){ // check to see if game grid already contains memory
		deallocateGrid(); 
	}

	game_grid = new entity** [game_height]; //allocate only the first 2 dimensions
	for(int i=0 ; i<game_height ; i++){ 
		game_grid[i] = new entity* [game_width];
	}

	for(int i=0 ; i<game_height ; i++){ //initialize each individual pointer within the grid to nullptr
		for(int j=0 ; j<game_width ; j++){
			game_grid[i][j] = nullptr;
		}
	}
}

void dig_adventure_game::deallocateGrid() { //This function should deallocate the memory used for the game grid
	// YOUR CODE HERE
	if(game_grid == nullptr){//check to see if game grid is empty
		return;  
	}
	else{ //deallocate all dimensions in proper order
		for(int i=0 ; i<game_height ; i++){
			for(int j=0 ; j<game_width ; j++){
				if(game_grid[i][j] != nullptr){
					delete game_grid[i][j]; //delete the objects
				}
			}
			if(game_grid[i] != nullptr){
				delete [] game_grid[i];	
			}
		}
		delete [] game_grid; 
	} 
}


entity *dig_adventure_game::allocateEntity(unsigned int i) { //A helper function used to allocate different derived objects
	// YOUR CODE HERE
	if(i == WALL){ //if parameter is WALL
		return (new hardened_wall()); 
	}
	if(i == NOTHING){//if parameter is NOTHING
		return (new empty_space()); 
	}
	if(i == ROCK){//if parameter is ROCK
		return (new rock()); 
	}
	if(i == SILVERFISH){//if parameter is SILVERFISH
		return (new carnivorous_silverfish()); 
	}
	if(i == ARMOR){//if parameter is ARMOR
		return (new spike_armor()); 
	}
	if(i == TREASURE){//if parameter is TREASURE
		return (new hidden_treasure()); 
	}
	if(i == EXIT){//if parameter is EXIT
		return (new mine_exit()); 
	}
	if(i == MINER){//if parameter is MINER
		return (new miner()); 
	}
	return nullptr; // You may want to replace. 
}

void dig_adventure_game::moveMiner(unsigned int nh, unsigned int nw) { //This function needs to move the miner within the grid
	// YOUR CODE HERE
	int oldHeight = player->getHeight(); 
	int oldWidth = player->getWidth(); 

	delete game_grid[nh][nw]; //delete for the object that miner is trying to move to
	game_grid[nh][nw] = player; //assign the player pointer to the new location in the grid

	game_grid[oldHeight][oldWidth]=allocateEntity(NOTHING); //overwrite the miner’s old location with a new empty space object
	player->updateLocation(nh,nw);//update the miner’s height and width
}

unsigned int dig_adventure_game::playerMove() { //This function is responsible for one turn
	if (player == nullptr) {
		return GAME_ERROR;
	}
	string selection;
	cout << "Where will the miner go?" << endl;
	cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
	cin >> selection;
	while (true) { //repeatedly prompt the user until they enter a proper left, right, down, or up input
		if (selection.length() >= 1) {
			if (selection[0] == 'l' || selection[0] == 'r' || selection[0] == 'u' || selection[0] == 'd') {
				break;
			}
		}
		cout << "Invalid entry!" << endl;
		cout << "(l)eft, (r)ight, (u)p, (d)own :" << endl;
		cin >> selection;
	}
	char direction = selection[0];

	// YOUR CODE HERE
	int h = 0; //initialize height int 
	int w = 0; //initialize width int
	int oldh = player->getHeight(); //get old height 
	int oldw = player->getWidth(); //get old width 

	if(direction == 'l'){ //if direction left 
		h = player->getHeight(); 
		w = player->getWidth() - 1; //subract one to move left
	}
	else if(direction == 'r'){ //if direction right 
		h = player->getHeight(); 
		w = player->getWidth() + 1; //add one to move right
	}
	else if(direction == 'u'){//if direction up
		h = player->getHeight() - 1; //subtract one to go up
		w = player->getWidth(); 
	}
	else if(direction == 'd'){//if direction down
		h = player->getHeight() + 1; //add one to go down
		w = player->getWidth(); 
	}
	else{
		return GAME_ERROR; // You may want to replace. 
	}

	int objectNum = 0; //initialize objectNum to 0
	objectNum = game_grid[h][w]->destroy(); //get the object destroy return 

	if(objectNum == NOTHING){ //if nothing 
		moveMiner(h, w); //move miner 
		return GAME_CONTINUE; //continue game
	}
	else if(objectNum == ROCK){ //if rock
		moveMiner(h, w); //move miner
		player->givePoints(1); //give one point
		return GAME_CONTINUE;//continue game
	}
	else if(objectNum == SILVERFISH){ //if silverfish
		player->destroy(); //destroy player
		player->givePoints(-5);//take 5 points 
		if(player->isStillAlive() == true){//if still alive
			moveMiner(h, w);//move miner
			return GAME_CONTINUE;//continue game
		}
		else{//if dead
			delete player;//delete player
			player = nullptr; //set to nullptr
			game_grid[oldh][oldw]=nullptr; //set player location to nullptr
			return GAME_EXIT_LOSE; //exit game
		}
	}
	else if(objectNum == ARMOR){ //if armor 
		moveMiner(h, w); //move miner
		player->armorUp(); //armor up player 
		return GAME_CONTINUE;//continue game
	}
	else if(objectNum == TREASURE){ //if treasure
		player->givePoints(3); //give 3 points 
		moveMiner(h, w);//move miner
		return GAME_CONTINUE;//continue game
	}
	else if(objectNum == EXIT){ //if exit 
		moveMiner(h, w);//move miner
		return GAME_EXIT_WIN; //game exit 
	}
	else if(objectNum == WALL){ //if wall 
		return GAME_CONTINUE;//continue game
	}
	return GAME_ERROR; 
}

/*******************************
 * Mr. P Functions
*******************************/
void dig_adventure_game::populateGrid() { //randomly populates all the nullptrs in the grid with objects
	if(game_width < 2 || game_height < 2){
		return;
	}
	// Place the miner
	player = new miner(1, 1);//The miner is always placed at (1,1) and the exit is always placed in the bottom right.
	game_grid[1][1] = player;
	/* Place the exit */
	game_grid[game_height - 2][game_width - 1] = allocateEntity(EXIT);
	/* Put up the walls */
	for (unsigned int h = 0; h < game_height; h++) {// the walls are put up
		// Vertical Walls
		if(game_grid[h][0] == nullptr){
			game_grid[h][0] = allocateEntity(WALL);
		}
		if (h != (game_height - 2) && game_grid[h][game_width - 1] == nullptr) {
			game_grid[h][game_width - 1] = allocateEntity(WALL);
		}
	}
	for (unsigned int w = 0; w < game_width; w++) {
		// Horizontal Walls
		if(game_grid[0][w] == nullptr){
			game_grid[0][w] = allocateEntity(WALL);
		}
		if(game_grid[game_height - 1][w] == nullptr){
			game_grid[game_height - 1][w] = allocateEntity(WALL);
		}
	}
	/* Place the events */
	unsigned int sflh, sflw, htlh, htlw, salh, salw;
	unsigned int quadrant = 4;
	// Quadrant height
	for (unsigned int qh = 0; qh < quadrant / 2; qh++) {

		unsigned int startH, startW;
		startH = (qh * (game_height / 2));
		// Quadrant width
		for (unsigned int qw = 0; qw < quadrant / 2; qw++) {

			startW = (qw * (game_width / 2));
			// Add silverfish
			for (unsigned int d = 0; d < difficulty; d++) {
				
				do {
					sflh = startH + (rand() % (game_height / 2));
					sflw = startW + (rand() % (game_width / 2));
				} while (game_grid[sflh][sflw] != nullptr);
				game_grid[sflh][sflw] = allocateEntity(SILVERFISH);
				
			}
			// Add treasure
			do {
				htlh = startH + (rand() % (game_height / 2));
				htlw = startW + (rand() % (game_width / 2));
			} while (game_grid[htlh][htlw] != nullptr);
			game_grid[htlh][htlw] = allocateEntity(TREASURE);
			// add armor
			do {
				salh = startH + (rand() % (game_height / 2));
				salw = startW + (rand() % (game_width / 2));
			} while (game_grid[salh][salw] != nullptr);
			game_grid[salh][salw] = allocateEntity(ARMOR);
		}
	}
	/* Fill the rest with rock */
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				game_grid[i][j] = allocateEntity(ROCK);
			}
		}
	}
}

dig_adventure_game::dig_adventure_game(unsigned int h, unsigned int w, unsigned int d) : game_height(h), game_width(w), difficulty(d){
	// Sanatize parameters
	//The constructor for a game
	if (w < 10) {
		game_width = 10;
	}
	if (h < 10) {
		game_height = 10;
	}

	if (d == 0) {
		d = 1;
	}
	else {
		unsigned int hd = d, wd = d;
		if (d > (((game_height - 2) / 2) - 1)) {
			hd = (((game_height - 2) / 2) - 1);
		}
		if (d > (((game_width - 2) / 2) - 1)) {
			wd = (((game_width - 2) / 2) - 1);
		}
		d = (wd < hd) ? wd : hd;
	}
	difficulty = d;
	// Allocate the grid
	allocateGrid();
	// Populate with objects
	populateGrid();
}

dig_adventure_game::~dig_adventure_game() { //The destructor checks to see if the miner has been deallocated
	// Check to see if player still exists
	if (player != nullptr) {
		game_grid[player->getHeight()][player->getWidth()] = nullptr;
		delete player;
	}
	// Deallocate the grid
	deallocateGrid();	
}

void dig_adventure_game::playGame() { //An infinite loop that prints the grid and then calls playerMove()
	while (true) {
		// Print the game board
		printGrid();
		// Let the player move
		unsigned int rslt = playerMove();
		// If error
		if (rslt == GAME_ERROR) {
			cout << "An Error Ocurred. Please report this incident to yourself." << endl;
			return;
		}
		// If player loses or wins
		if (rslt == GAME_EXIT_LOSE || rslt == GAME_EXIT_WIN) {
			return;
		}
	}
}

void dig_adventure_game::printGrid() const { //Prints the grid with the score and armor
	// Use a string so output happens all at once. 
	string output("");
	output += "\n";
	output += "------------------\n";
	output += string("| Current Score: |  ") + to_string(player->getPoints()) + string("\n");
	output += string("------------------\n");
	output += string(" * Armor Bonus: *  ") + to_string(player->getArmor()) + string("\n\n");
	for (unsigned int i = 0; i < game_height; i++) {
		for (unsigned int j = 0; j < game_width; j++) {
			if (game_grid[i][j] == nullptr) {
				// In case your grid contains nullptrs, you will question marks
				output += string("|?");
			}
			else {
				output += '|';
				output += game_grid[i][j]->getShape();
			}
		}
		output += "|\n";
	}
	output += '\n';
	cout << output;
}

// Copy ctor is here to prevent memory problems. 
// Does not make an identical copy
dig_adventure_game::dig_adventure_game(const dig_adventure_game &copy) { //The copy constructor
	game_grid = nullptr; 
	player = nullptr;
	game_width = 0;
	game_height = 0;
	(*this) = copy;
}

// Operator= is here to prevent memory problems. 
// Does not make an identical copy
void dig_adventure_game::operator=(const dig_adventure_game &copy) { //The assignment operator overload
	cout << "WARNING: You have called the Copy Ctor or Operator= for game object." << endl;
	cout << "A new game will be made instead because Mr.P was too lazy to do a deep copy." << endl;
	cout << "If you are a student who is still completing the assignment, you should not be seeing this message." << endl;
	deallocateGrid();
	if (player != nullptr) {
		delete player;
	}
	game_width = copy.game_width;
	game_height = copy.game_height;
	difficulty = copy.difficulty;
	allocateGrid();
	populateGrid();
}

