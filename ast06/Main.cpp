/*
 * Name: Dylan Cozloff, 2001668380, Assignment 06
 * Description: Finds a substring in a char array 
 * Input: NA 
 * Output: Substring Index 
 */
#include <iostream>
#include <fstream>
#include "CS202_String.h"

using namespace std; 

int main(){
    CS202_String String1("I'm Mr. Meseeks! Look at me!"); 
    // Insertion Operator
    cout << String1 << endl;
    // Bracket
    cout << String1[1] << endl;
    ifstream inFile("StringFile.txt");
    if(inFile.is_open()){
        CS202_String String2;
        CS202_String String3;
        // Addition Operator with CHAR*
        String2 = String2 + "Wowwww.... ";
        // Extraction Operator
        while(inFile >> String1){
            CS202_String String4 = "But, if the last assignment could not hold me down";
            // Addition Operator with CS202_String
            String2 = String2 + " " + String1;
            // Insertion Operator
            cout << String2 << endl;
            // Assingment Operator
            String3 = String4;
        }
        String1 = CS202_String("Exiting!");
        // Insertion Operator
        cout << String3 << endl;
        // Pre op
        cout << ++String3 << endl;
        // Post op
        String3++;
        cout << String3 << endl; 
        // Subtraction with CHAR*
        String3 = String3 - "if ";
        cout << String3 << endl;
        // Subtraction with CS202_String
        String3 = String3 - "BBut, ";
        cout << String3 << endl;
        // DeleteAt from last assignment
        String3.DeleteAt(String3.GetSize() - 1);
        // Addition
        cout << CS202_String("Correction! ") + String3 << endl;
        // Multiplication 
        cout << CS202_String("Looking Good So Far!") * 3 << endl;
        cout << CS202_String("This should not print...") * 0 << endl;
        // Operators!
        String3 = CS202_String("It is the final string trial! BOOLEAN OPERATORS!");
        cout << String3 << endl;
        String2 = String3; 
        // Equality
        if(String2 == String2){
            cout << "If the == operator did not tell you already, these are the same strings." << endl;
        }
        if(String2 == String3){
            cout << "These have the same content." << endl;
        }
        // Inequality
        if(String2 != String1){
            cout << "And these are not equal at all!" << endl; 
        }
        // Less Than equal 
        if(String1 <= String3){
            cout << "String1 is LTE String3!" << endl;
        }
        // Greater than equal
        if(String1 >= String2){
            cout << "and String1 is GTE String2!" << endl;
        }

        int size = 5;
        CS202_String *myArr = new CS202_String[size];
        myArr[0] = CS202_String("Bandos");
        myArr[1] = CS202_String("Saradomin");
        myArr[2] = CS202_String("Zamorak");
        myArr[3] = CS202_String("Armadyl");
        myArr[4] = CS202_String("Saradomin");

        cout << "About to sort a list of Runescape gods. Less Than First..." << endl;
        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < size - i - 1; j++){
                // Less Than
                if(myArr[j] < myArr[j+1]){
                    CS202_String temp = myArr[j];
                    myArr[j] = myArr[j+1];
                    myArr[j+1] = temp; 
                }
            }
        }

        for(int i = 0; i < size; i++){
            cout << "[" << myArr[i] << "] ";
        }
        cout << endl;

        cout << "About to sort a list of Runescape gods. Greater Than..." << endl;
        for(int i = 0; i < size - 1; i++){
            for(int j = 0; j < size - i - 1; j++){
                // Less Than
                if(myArr[j] > myArr[j+1]){
                    CS202_String temp = myArr[j];
                    myArr[j] = myArr[j+1];
                    myArr[j+1] = temp; 
                }
            }
        }

        for(int i = 0; i < size; i++){
            cout << "[" << myArr[i] << "] ";
        }
        cout << endl;


        delete[] myArr;
        myArr = nullptr;

        cout << "Wow! That was hard. Nice job student!" << endl;
    }
    else{
        cout << "File Open failed. Exiting assignment." << endl;
    }

    return 0;
}