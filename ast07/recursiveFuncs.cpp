#include "recursiveFuncs.h"
using namespace std;

// * integerPow
unsigned int integerPow(unsigned int num, unsigned int pow){ //4 Lines 
    // YOUR CODE HERE
    if(pow==0){ //base case: when pow=0 it returns 1 
        return 1; 
    }
    return integerPow(num, pow-1) * num; //recursive formula creates an exponential number of calls and returns num * num
}

// * countChars
unsigned int countCharacter(char *str, char searchChar, unsigned int currentIndex, unsigned int strLength, bool left, bool right){ //11 Lines
    // YOUR CODE HERE 
    int charInstance = 0, leftChars = 0, rightChars = 0;
    if(currentIndex < 0 || currentIndex >= strLength) 
        return 0;
    
    if(str[currentIndex] == searchChar) 
        charInstance = 1;
    
    if(left == true) 
        leftChars = countCharacter(str, searchChar, currentIndex-1, strLength, left, false);
        
    if(right == true) 
        rightChars = countCharacter(str, searchChar, currentIndex+1, strLength, false, right);
        
    return leftChars + rightChars + charInstance;
}


// * popBalloons
void popBalloons(char **grid, unsigned int currentHeight, unsigned int currentWidth, unsigned int height, unsigned int width, char balloon){ //10 Lines
    // YOUR CODE HERE
    if(currentHeight<0 || currentHeight>=height || currentWidth<0 || currentWidth>=width)
        return;
    if(grid[currentHeight][currentWidth]!=balloon || grid[currentHeight][currentWidth]==' ')
        return;
    grid[currentHeight][currentWidth] = ' ';
    popBalloons(grid, currentHeight, currentWidth+1, height, width, balloon);
    popBalloons(grid, currentHeight+1, currentWidth, height, width, balloon);
    popBalloons(grid, currentHeight, currentWidth-1, height, width, balloon);
    popBalloons(grid, currentHeight-1, currentWidth, height, width, balloon);
}

// * countLettersInSentence
unsigned int countLettersInSentence(char **sentence, unsigned int currentWord, unsigned int currentLetter){ //7 Lines 
    // YOUR CODE HERE
    if(sentence[currentWord] == nullptr)
        return 0;

    if(sentence[currentWord][currentLetter] == '\0')
        return countLettersInSentence(sentence, currentWord + 1, 0);

    return 1 + countLettersInSentence(sentence, currentWord, currentLetter + 1);
}

// * alphaMerge
unsigned int alphaMerge(char *&destArray, unsigned int currentSize, const char *arr1, const char *arr2, unsigned int p1, unsigned int p2){ //28 Lines
    // YOUR CODE HERE

    if(arr1[p1] == '\0' && arr2[p2] == '\0')
        return 0;
    if(arr1[p1] != '\0' && arr2[p2] != '\0'){
        if(arr1[p1] < arr2[p2]){
            destArray[currentSize] = arr1[p1];
            return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1 + 1, p2);
        }
        else{
            destArray[currentSize] = arr2[p2];
            return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1, p2 + 1);
        }
    }
    else if(arr1[p1] != '\0'){
        destArray[currentSize] = arr1[p1];
        return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1 + 1, p2);
    }
    else if(arr2[p2] != '\0'){
        destArray[currentSize] = arr2[p2];
        return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1, p2 + 1);
    }

    
}
