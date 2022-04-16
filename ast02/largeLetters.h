#ifndef IOS_H 
#define IOS_H //If library not defined, define it
#include <iostream> 
#endif //end if define

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef FILES_H
#define FILES_H
#include <fstream>
#endif

using namespace std; //Allows us to ignore std::
/******************************
 Class Large Letter
******************************/
/*
* class_identifier: represents largeLetters as 2D arrays 
* constructors: largeLetter, largeLetter(char l, const string s[])
* static members: const int letterWidth, const int letterWidth
*/
class largeLetter{
public:
    // Dimensions of the Letter
    static const int letterHeight = 6; //Large letter grid height of 6
    static const int letterWidth = 8; //Large letter grid width of 8 
    // Constructors
    largeLetter(); //default constructor, used to intialize an empty large letter 
    largeLetter(char l, const string s[]); //initializes letter, and each string of rows array 
    // Getter Functions 
    string getRow(int r) const; //returns the string in rows array at the index paramater 
    void printLetter() const; //prints a single letter to the screen
    void printLetter(ostream &out) const; //prints a single largeLetter to the ostream 
    char getSmallLetter() const; //returns a copy of letter 
private:
    char letter = '\0'; //actual ASCII char is stored here
    string rows[letterHeight]; //where the ASCII art is stored for each largeLetter
};

/******************************
 Class Large Letter Dict
******************************/
/*
* class_identifier: holds a map of the ASCII character to its ASCII art, 
*                   used to look up a character to get larger version.
* constructors: largeLetterDictionary();
* static members: const int maxDictSize = 100; 
*/
class largeLetterDictionary{
private:
    static const int maxDictSize = 100; //max size of possible characters, made to exceed actual amount 
    int numLetters; //total number of characters in the dictionary 
    largeLetter letters[maxDictSize]; //object array of the large letters 
public:
    largeLetterDictionary(); //default constructor for the dictionary, sets numLetters to 0
    largeLetterDictionary(string fName); //fName constructor that reads "Letters.txt" or similar file 
    largeLetter getLargeLetter(char letter) const; //returns a copy of a largeLetter object
    void printDictionary() const; //prints the whole dictionary 
};

/******************************
 Class largeLetterWord
******************************/
/*
* class_identifier: holds an array of largeLetters that spell out a word
* constructors: largeLetterWord(), largeLetterWord(string)
* static members: const int maxLetterSize, largeLetterDictionary dict
*/
class largeLetterWord{
private:
    static const int maxLetterSize = 20; //max length of a word 
    static largeLetterDictionary dict; //static object to translate into the large font 
    int numLetters; //Number of letters in a word 
    largeLetter letters[maxLetterSize]; //array to hold the large letters that make up the word
    string word; //Holds the ASCII font 
public:
    largeLetterWord(); //initializes numLetters to 0 
    largeLetterWord(string); //initializes word & numLetter, & converts to largeLetters
    void printWord() const; //Prints every letter of the word to the ostream
    void printWord(ostream &out) const; //Prints every letter of the word to the screen
};