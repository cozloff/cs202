/*
 * Name: Dylan Cozloff, 2001668380, Assignment 06
 * Description: Finds a substring in a char array 
 * Input: NA 
 * Output: Substring Index 
 */
#include "CS202_String.h" //gets the header file class
using namespace std; //ignores std::


// Prints the to the terminal
void CS202_String::PrintString() const{ 
    cout << "Printing CS202_String: "; 
    for(int i = 0; i < size; i++){ 
        cout << charArr[i]; //Prints out element by element of char array
    }
    cout << endl;
}

// Assingment Operator to prevent memory leaks 
void CS202_String::operator=(const CS202_String &copy){
    delete[] charArr; //deallocates memory space
    size = copy.size; //sets copy size to class size
    charArr = new char[size]; //allocates memory 
    for(int i = 0; i < size; i++){
        charArr[i] = copy.charArr[i]; //deep copy the array to charArr
    }
}

/*************************************************
 *  YOUR CODE DOWN HERE
*************************************************/

CS202_String::CS202_String(){ //Default constructor
    charArr = nullptr; //sets array to be a nullptr
    size = 0; //sets size to 0 
}

CS202_String::CS202_String(const char *ch){
	// Figure out how long the array is, save that into the size variable,
	size = 0; 

	const char *temp = ch; //make a temp array
	while(*temp != 0){ //while the temp array doesn't get to the null element
		temp++; //increment the array
        size++;	//increment the size	   		   
    }

	// allocate enough memory to store the array into the class pointer
	charArr = new char[size + 1]; 

	// deep copy the contents of the parameter array into the class pointer array.
    for (int j = 0; j < size; j++) 
        charArr[j] = ch[j];
	charArr[size] = 0;
}

CS202_String::CS202_String(const CS202_String& cs){ //Copy array 
    size = cs.size; //sets size to equal parameter
    charArr = new char[size + 1]; //allocate memory 
    for (int i = 0; i < size; i++){ //deep copy the parameter elements 
        charArr[i] = cs.charArr[i];
    }
	charArr[size] = 0; //set to null 
}

CS202_String::~CS202_String(){ //destructor
    delete [] charArr; //deallocates memory
	size = 0; //sets size to 0 
}

void CS202_String::PushBack(const char* ch){ //pushback function
	// Figure out how long this parameter array is.
    int newsize = 0; //initialize new size variable 
	const char *temp = ch; //create temp pointer

	while (*temp != 0) { //while it doesnt get the null element
		temp++; //increment the temp
		newsize++; //increment the newsize
	}

	// Allocate a new array of a new size which is the objects size
	// plus the size of the parameter array.
    int totalSize = newsize + size; 
    char* newCharArr = new char[totalSize + 1]; 

	// Deep copy the old objects array into the new array
    for (int j = 0; j < size; j++) 
        newCharArr[j] = charArr[j];

	// Deep copy the elements of the parameter array into the remaining
	// spots of the new array.
    for (int i = size; i < totalSize; i++) 
        newCharArr[i] = ch[i - size]; //decrement the array
	newCharArr[totalSize] = 0; //set to null

	// Deallocate the old objects array.
	if( charArr != nullptr ) 
		delete [] charArr; 

	// Copy the address of new array into the pointer for the old objects	array.
    charArr = newCharArr;

	// Adjust the size member to reflect the new size.
    size = totalSize; 
}

void CS202_String::DeleteAt(int p){ //Delete at index function
    if(p < 0 || p >= size) { //if not a valid index
        cout<<"WARNING: CS202_String::DeleteAt(int) - Nothing Was Deleted ."<<endl; 
        return; //exit
    }


    char * tempCharArr = new char[size]; //create temp allocated memory
    for(int i= 0; i < p; i++){
        tempCharArr[i] = charArr[i]; //deep copy to the index
    }
      for(int i= p + 1 ; i < size; i++){
        tempCharArr[i - 1] = charArr[i]; //deep copy after the index
    }
	tempCharArr[size - 1] = 0; //decrement the array and set to null

	// delete the old objects array
    delete [] charArr; 

	// copy the address of the new array into the pointer of the old objects array.
    charArr = tempCharArr; 
	size--;
}
    
int CS202_String::GetSize() const { //get size function
    return size; 
}

char CS202_String::At(int p) const{ //returns index element 
    if(p < 0 || p >= size){ //if invalid index
        cout<<"ERROR: CS202_String::At(int) - Index out of bounds , returning NULL character."<<endl; 
        return 0; 
    }
    return charArr[p]; //return the element 
}

int CS202_String::FindSubString(const CS202_String& cs) const{ //find substring function
	if (cs.size < 1 || cs.size > size) //if invalid substring size 
		return -1;

	int find_pos = -1; 
	for (int i = 0; i < size - cs.size + 1; i++){ //for the difference 
		bool match_flag = true;
		for (int j = i; j < i + cs.size; j++) { //for the subset size + the index
			if (charArr[j] != cs.charArr[j - i]) // if some position does not matched
			{
				match_flag = false;
				break;
			}
		}

		if (match_flag) // find the matched substring
		{
			find_pos = i; //make the index equal to the position
			break;
		}
	}

	return find_pos; //return the position 
        
}

CS202_String CS202_String::Concatinate(const CS202_String& cs1, const CS202_String& cs2){ //concatinate function
    int concatSize = cs1.GetSize() + cs2.GetSize(); //get the concatinate size 
    char *newArr = new char[concatSize + 1]; //allocate memory 

    for(int i=0 ; i < cs1.GetSize(); i++){ //for the size of the first 
        newArr[i] = cs1.At(i); //deep copy the elements of the first 
    }
    
	for (int i = 0; i < cs2.GetSize(); i++) { //for the size of the second
        newArr[cs1.GetSize() + i] = cs2.At(i); //deep copy the elements of the second after the first    
    }

	newArr[concatSize] = 0; //set to null 
	

	CS202_String result(newArr); //create an object with array

	delete[]newArr; //deallocate memory

	return result; //return the object 
}

/*************************************************
 *  Operators 
*************************************************/
//Friend operators 
istream& operator>>(istream& LHS, CS202_String&  RHS){
    // '\n', ' ', '\t' -> Whitespace characters
    if(RHS.charArr != nullptr){ // Avoid Memory leaks
        delete[] RHS.charArr;
        RHS.charArr = nullptr; // Avoid dangling ptr
    }
    RHS.size = 0; // Reset Size
    char temp; // Temp character to read into
    while(LHS.get(temp) && !LHS.eof() ){ // Read in char by char
        if(isspace(temp)){ // If whitespace
            break; // Break out of while loop
        } 
        RHS.size++;
        char *newArr = new char[RHS.size]; // Allocate arr of bigger size
        for(int i = 0; i < RHS.size - 1; i++){
            newArr[i] = RHS.charArr[i]; // Copy old elements
        }
        newArr[RHS.size - 1] = temp; // Add read char
        delete[] RHS.charArr; // delete old arr
        RHS.charArr = newArr; 
    }
    return LHS;
}

ostream& operator<<(ostream& LHS, CS202_String RHS){
    for(int i = 0 ; i<RHS.GetSize() ; i++){
        LHS<<RHS.At(i);
    }
    return LHS;
}

//Member Operators 
char& CS202_String::operator[](int index){
    if(0 <= index && index < (*this).size){
        return charArr[index];
    }
    else{
        exit(1);
    }
}

CS202_String CS202_String::operator+(CS202_String rhs){
    CS202_String temp = Concatinate(*this, rhs);
    return temp;
}

CS202_String CS202_String::operator+(const char* rhs){
    CS202_String temp = CS202_String(rhs);
    CS202_String temp2 = Concatinate(*this, temp);
    return temp2;
}

CS202_String CS202_String::operator++(){ //Pre-increment operation overloaded 
    int concatSize = (*this).GetSize() + 1; //get the concatinate size 
    char *newArr = new char[concatSize + 1]; //allocate memory 
    char firstChar = (*this).At(0);
    
    newArr[0] = firstChar; //deep copy the elements of the first 
    
	for (int i = 0; i < (*this).GetSize(); i++) { //for the size of the second
        newArr[i + 1] = (*this).At(i); //deep copy the elements of the second after the first    
    }

	newArr[concatSize] = 0; //set to null 

	CS202_String result(newArr); //create an object with array

    *this = result; 

	delete[]newArr; //deallocate memory

	return *this; //return the object 
}

CS202_String CS202_String::operator++(int){ //Post-increment operation overloaded
    int concatSize = (*this).GetSize() + 1; //get the concatinate size 
    char *newArr = new char[concatSize + 1]; //allocate memory 
    
    //CS202_String incrementLastChar(lastChar);
    //newArr[concatSize] = lastChar; //deep copy the elements of the first 
    
	for (int i = 0; i < (*this).GetSize(); i++) { //for the size of the second
        newArr[i] = (*this).At(i); //deep copy the elements of the second after the first    
    }
    char lastChar = (*this).At((*this).GetSize() - 1);
   
    newArr[(*this).GetSize()] = lastChar; //set to null

    newArr[concatSize] = 0; //set to null

	CS202_String result(newArr); //create an object with array

    *this = result;

	delete[]newArr; //deallocate memory

	return *this; //return the object 
}

CS202_String CS202_String::operator-(CS202_String rhs){
   int index = (*this).FindSubString(rhs);
    int j = 0;
    for(int i = index ; i < index + rhs.GetSize() ; i++){
        (*this).DeleteAt(i -j); 
        j++;
    }
    return *this;
}

CS202_String CS202_String::operator-(const char* rhs){
    CS202_String temp(rhs);
    int index = (*this).FindSubString(temp);
    int j = 0;
    for(int i = index ; i < index + temp.GetSize() ; i++){
        (*this).DeleteAt(i -j); 
        j++;
    }
    return *this;
}

CS202_String CS202_String::operator*(unsigned int rhs){
    if(rhs == 0){
        return "";
    }
    CS202_String temp = *this;
    for(int i = 1 ; i < rhs ; i++){
        *this = Concatinate(*this, temp); 
    }
    return *this;
}


bool CS202_String::operator<(const CS202_String & rhs){
    for(int i = 0 ; i < this->GetSize() ; i++){
        if(rhs.At(i) != this->At(i)){
            if(rhs.At(i) > this->At(i)){
                return true; 
            }
            else{
                return false;
            }
        }
    }
    return false;
} 

bool CS202_String::operator==(const CS202_String & rhs){
    for(int i = 0 ; i < (*this).GetSize() ; i++){
        if(this->At(i) != rhs.At(i)){
            return false; 
        }
    }
    if(this == &rhs){
        cout<<"Duh! This is the same CS202_string obviously. Just look at their addresses!"<<endl; 
    }
    return true;
}

bool CS202_String::operator!=(const CS202_String & rhs){
    return !(*this == rhs);
}

bool CS202_String::operator>(const CS202_String & rhs){
    return !(*this < rhs);
}

bool CS202_String::operator<=(const CS202_String & rhs){
    return (*this < rhs || *this == rhs);
}

bool CS202_String::operator>=(const CS202_String & rhs){
    return (*this > rhs || *this == rhs);
}
