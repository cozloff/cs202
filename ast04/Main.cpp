#include <iostream>
#include "CS202_String.h"

using namespace std; 

int main(){
    // Parameter Constructor
    CS202_String String1("Inializing CS202 Program - Strings...");
    // PrintString
    String1.PrintString(); 
    // Default Constructor
    CS202_String String2;
    // PrintString
    String2.PrintString(); 
    // PushBack()
    String2.PushBack("Whoops. I did not mean to print that!");
    // PrintString 
    String2.PrintString(); 
    /* Copy Constructor
        - Concatination 
            - Concatination
                - Parameter Constructor
                - Parameter Constructor
            - Parameter Constructor 
    */
    CS202_String String3 = 
        CS202_String::Concatinate(
            CS202_String::Concatinate(
                CS202_String("")
                ,CS202_String("This is a program that just uses string?")
            )
            ,CS202_String("... How exciting...")
        );
    // PrintString
    String3.PrintString(); 
    // Parameter Constructor
    CS202_String String4("You made it through that?? Wow! Nice job. Hopefully Valgrind says no memory leaks...");
    if(true){
        CS202_String scopeString(String4);
        // Assignment Operator
        String2 = scopeString;
    }
    // PrintString
    String2.PrintString();
    // GetSize() and DeleteAt()
    while(String2.GetSize() > 0){
        String2.DeleteAt(0);
    }
    String2.DeleteAt(3);
    // Parameter Constructor
    CS202_String String5("ValGrind");
    cout << "MAIN(): - About to search for the following substring in the above string:" << endl;
    // PrintString()
    String5.PrintString();
    // Find SubString 
    int ind = String4.FindSubString(String5);
    if(ind == -1){
        CS202_String("Whoops! I misspelled it.").PrintString();
    }
    else{
        cout << "MAIN(): - CS202 Student! Your FindSubString() function is not correct! Please fix it." << endl;
        return 0;
    }
    // DeleteAt() and FindSubString() and Parameter Constructor
    String5.DeleteAt(String5.FindSubString(CS202_String("G")));
    String5.DeleteAt(String5.FindSubString(CS202_String("r")));
    String5.DeleteAt(String5.FindSubString(CS202_String("i")));
    String5.DeleteAt(String5.FindSubString(CS202_String("n")));
    String5.DeleteAt(String5.FindSubString(CS202_String("d")));
    //PrintString()
    String5.PrintString();
    //PushBack()
    String5.PushBack("g");
    String5.PushBack("rind");
    cout << "MAIN(): - About to search for the following substring AGAIN:" << endl;
    // PrintString()
    String5.PrintString();
    // Find SubString 
    ind = String4.FindSubString(String5);
    if(ind == -1){
        cout << "MAIN(): - CS202 Student! Your FindSubString() function is not correct! Please fix it." << endl;
        return 0;
    }
    else{
        cout << "MAIN(): - CS202 Student! Your FindSubString() function worked!" << endl;
    }
    cout << "MAIN(): - That is it. You survived the string trials. Hopefully there are no memory leaks..." << endl;
    cout << "MAIN(): - Please keep your code for the Operator Overload assignment." << endl;
    return 0;
}

