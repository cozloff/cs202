/*
 * Name: Dylan Cozloff, 2001668380, Assignment 02
 * Description: Program that converts ASCII characters to its ASCII art representation
 * Input: Input file name (small letters) and output file name
 * Output: Large letter representation of the small letter files 
 */

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

#ifndef LL_H
#define LL_H
#include "largeLetters.h"
#endif

using namespace std;

int main(int argc, char **argv){ //Argument counter, and pointer
    // YOUR CODE HERE
    if(argc < 2 || argc> 3){ //If more or less than 2 or 3 arguments 
        cout<<"Error, incorrect input"<<endl; 
        return 0;
    }

    if(argc == 2){ //prints to the terminal
        ifstream inFile; 
        inFile.open(argv[1]);//open file
        if(argv[1] == string ("Letters.txt")){ //if Letters.txt is the argument
            largeLetterDictionary temp(argv[1]); //create the dictionary
            temp.printDictionary(); //print the dictionary
            inFile.close();
            return 0;
        }
        string word = "";
        while(inFile>>word){ //while filing in words
            for(int i=0 ; i<word.length() ; i++){
                word[i] = toupper(word[i]); //change to uppercase letters
            }
                largeLetterWord temp(word); //create large letter words
                temp.printWord(); //print the large letter words
        }
        inFile.close();
        return 0; 
    }

    if(argc == 3){//prints to the out file 
        ifstream inFile; 
        inFile.open(argv[1]);
        //NOT SURE HOW TO PRINT THE DICTIONARY TO AN OUTFILE WITHOUT OSTREAM PARAMETER IN printDictionary();
        //DOESN'T SPECIFY AS A REQUIREMENT
        //if(argv[1] == string("Letters.txt")){
            //largeLetterDictionary temp(argv[1]);
            //ofstream outFile; //create out file stream
            //outFile.open(argv[2]); //open the chosen file
            //outFile<<temp.printDictionary();
            //outFile.close(); //close the file
            //inFile.close();
            //return 0;
        //}
        ofstream outFile; //create out file stream
        outFile.open(argv[2]); //open the chosen file
        string word = ""; 
        while(inFile>>word){
            for(int i=0 ; i<word.length() ; i++){
                word[i] = toupper(word[i]);
            }
            largeLetterWord temp(word); 
            temp.printWord(outFile); //print the large letter words to the outFile
        }
        outFile.close(); 
        inFile.close();
    }
    return 0;
}