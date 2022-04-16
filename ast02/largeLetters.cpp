#ifndef LL_H
#define LL_H
#include "largeLetters.h"
#endif 
/***********************************
 * Large Letter Definitions
***********************************/
largeLetter::largeLetter(){ //default constructor, used to initialize an empty largeLetter
    // YOUR CODE HERE
    for(int i=0 ; i<letterHeight ; i++){
        rows[i] = string(8,' '); // 8 is the length of the string, and 32 is the space character
    }
}

largeLetter::largeLetter(char l, const string s[]){ //initializes letter, and each string of rows array 
    // YOUR CODE HERE
    letter = l; 
    for(int i=0 ; i<letterHeight ; i++){ //initializes each row
        rows[i] = s[i]; 
    }
}

string largeLetter::getRow(int r) const{ //returns the string in rows array at the index paramater
    // YOUR CODE HERE
    if(r<0 || r>letterHeight){ //if the param isn't within the letterHeight return -1
        return "error"; 
    }
    return rows[r]; 
}

void largeLetter::printLetter(ostream &out) const{ //prints a single largeLetter to the ostream
    // YOUR CODE HERE
    for(int i=0 ;  i<letterHeight ; i++){ //prints out the largeLetter row by row
        out<<rows[i]<<endl; 
    }
}

void largeLetter::printLetter() const{ //prints a single letter to the screen
    // YOUR CODE HERE
    printLetter(cout); //calls the printLetter function with a cout ostream
}

char largeLetter::getSmallLetter() const{ //returns a copy of letter 
    // YOUR CODE HERE
    return letter; 
}

/***********************************
 * Large Letter Dictionary Definitions
***********************************/
largeLetterDictionary::largeLetterDictionary(){ //default constructor for the dictionary, sets numLetters to 0
    // YOUR CODE HERE
    numLetters = 0; 
}

largeLetterDictionary::largeLetterDictionary(string fName){ //fName constructor that reads "Letters.txt" or similar file
    // YOUR CODE HERE
    ifstream inFile; //create an in file stream
    inFile.open(fName); //open the text file
    if(inFile.is_open()){ //if the file opens
        cout<<"File Opened... Initializing Dictionary..."<< endl; 
    }
    char smallLetter; 
    numLetters = 0; //initialize numLetters to 0 
    string temp = ""; //initialize a temp string to hold what we read from the file 
    while(numLetters<maxDictSize){ //iterates through and reads the whole text file 
        if(!getline(inFile, temp)){
            break;
        }
        smallLetter = temp[0]; //get the ASCII character and store it in the array 
        string r[largeLetter::letterHeight]; //create a largeLetter array for the ASCII art 
        for(int i=0 ; i<largeLetter::letterHeight ; i++){ //read ascii art goes into the r array
            getline(inFile, r[i]); 
        }
        largeLetter L(smallLetter, r); //create a largeLetter object using the ASCII and its art 
        letters[numLetters] = L; //store the large letter objects in the array 
        numLetters++; //increases the size of numLetters 
    }
}


largeLetter largeLetterDictionary::getLargeLetter(char l) const{ //returns a copy of a largeLetter object
    // YOUR CODE HERE
    for(int i = 0 ; i<numLetters ; i++){ //goes through each largeLetter object
        largeLetter L = letters[i];
        if(L.getSmallLetter()==l){ //if its the desired smallLetter in the object 
            return L;  //return the largeLetter 
        }
    }
    return largeLetter();
}

void largeLetterDictionary::printDictionary() const{ //prints the whole dictionary
    // YOUR CODE HERE
    for(int i=0 ; i<numLetters ; i++){ //iterates through the whole dictionary 
        cout<<"--------------"<<endl;
        cout<<"| Letter ["<<letters[i].getSmallLetter()<<"] |"<<endl; 
        cout<<"--------------"<<endl; 
        letters[i].printLetter();
    }
}

/***********************************
 * Large Letter Word Definitions
***********************************/
// INIT THE Static VAR HERE
largeLetterDictionary largeLetterWord::dict("Letters.txt"); //static object to translate into the large font 

largeLetterWord::largeLetterWord(){ //initializes numLetters to 0
    // YOUR CODE HERE
    numLetters = 0; 
}

largeLetterWord::largeLetterWord(string w){ //initializes word & numLetter, & converts to largeLetters
    // YOUR CODE HERE
    word = w; //initializes the word 
    numLetters = word.length(); //gets the length of the word 
    for(int i=0 ; i<numLetters ; i++){
        largeLetter L = dict.getLargeLetter(word[i]); //get the large letter 
        letters[i] = L; //store it into letters array
    }
}

void largeLetterWord::printWord(ostream &out) const{ //Prints every letter of the word to the ostream
    // YOUR CODE HERE
    for(int i=0 ; i<largeLetter::letterHeight ; i++){ 
        for(int j=0 ; j<numLetters ; j++){
            out<<letters[j].getRow(i)<<"  "; //Prints out letter by letter, then row my row 
        }
        out<<endl; //Prints the next row on a new line
    }
    out<<endl;
    out<<endl; //Spaces out words 
    
}

void largeLetterWord::printWord() const{ //Prints every letter of the word to the screen
    // YOUR CODE HERE
    printWord(cout); //passes the cout ostream to printWord(ostream)
}