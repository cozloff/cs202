#include "recursiveFuncs.h"
using namespace std;

// * integerPow
unsigned int integerPow(unsigned int num, unsigned int pow){ //4 Lines 
    // YOUR CODE HERE
    if(pow==0){ //base case: when pow=0 it returns 1 
        return 1; //2^0 is equivalent to one
    }
    return integerPow(num, pow-1) * num; //recursive formula creates an exponential number of calls and returns num * num
}

// * countChars
unsigned int countCharacter(char *str, char searchChar, unsigned int currentIndex, unsigned int strLength, bool left, bool right){ //11 Lines
    // YOUR CODE HERE 
    int charInstance = 0, leftChars = 0, rightChars = 0; //initialize the variables to hold the number of instances to 0 so that it doesn't compound 
    if(currentIndex < 0 || currentIndex >= strLength){ //If the currentIndex is beyond the bounds of the array return 0
        return 0; //exits for the following index direction
    }

    if(str[currentIndex] == searchChar){ //if the current index contains the search char
        charInstance = 1; //return 1
    }

    if(left == true){ //count in the left direction of the initial index
        leftChars = countCharacter(str, searchChar, currentIndex-1, strLength, left, false); //go down the index (right direction doesn't activate)
    }    
    
    if(right == true){ //count in the right direction of the initial index
        rightChars = countCharacter(str, searchChar, currentIndex+1, strLength, false, right); //go up the index (left direction doesn't activate)
    }

    return leftChars + rightChars + charInstance; //return the sum of all the instances 
}


// * popBalloons
void popBalloons(char **grid, unsigned int currentHeight, unsigned int currentWidth, unsigned int height, unsigned int width, char balloon){ //10 Lines
    // YOUR CODE HERE
    if(currentHeight<0 || currentHeight>=height || currentWidth<0 || currentWidth>=width){ //If the current height or width is out of bounds, exit
        return;
    }
    if(grid[currentHeight][currentWidth]!=balloon || grid[currentHeight][currentWidth]==' '){ //If there is not a balloon or a space at the current coordinate, exit
        return;
    }
    grid[currentHeight][currentWidth] = ' '; //place a space if the last two conditions aren't met
    popBalloons(grid, currentHeight, currentWidth+1, height, width, balloon); //check to the right
    popBalloons(grid, currentHeight+1, currentWidth, height, width, balloon); //check up
    popBalloons(grid, currentHeight, currentWidth-1, height, width, balloon); //check to the left 
    popBalloons(grid, currentHeight-1, currentWidth, height, width, balloon); //check down
}

// * countLettersInSentence
unsigned int countLettersInSentence(char **sentence, unsigned int currentWord, unsigned int currentLetter){ //7 Lines 
    // YOUR CODE HERE
    if(sentence[currentWord] == nullptr){ //if the word array is finished 
        return 0; //exit 
    }

    if(sentence[currentWord][currentLetter] == '\0'){ //if the current word is complete 
        return countLettersInSentence(sentence, currentWord + 1, 0); //start the next word 
    }

    return 1 + countLettersInSentence(sentence, currentWord, currentLetter + 1); //count the number of letters in a word 
}

// * alphaMerge
unsigned int alphaMerge(char *&destArray, unsigned int currentSize, const char *arr1, const char *arr2, unsigned int p1, unsigned int p2){ //28 Lines
    // YOUR CODE HERE

    if(currentSize == 0){ //If the function just started 
          destArray = new char[100]; //allocate an array for the destArray 
    }

    if(arr1[p1] == '\0' && arr2[p2] == '\0'){ //if both the arrays are complete, exit
        return 0;
    }
    if(arr1[p1] != '\0' && arr2[p2] != '\0'){ //if both the arrays aren't complete 
        if(arr1[p1] < arr2[p2]){ //compare the given elements 
            destArray[currentSize] = arr1[p1]; //if array 1 is smaller place it in currentSize element
            return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1 + 1, p2); //increment the currentSize, the function return, and the element in array 1 
        }
        else{ 
            destArray[currentSize] = arr2[p2]; //if array 2 is smaller place it in currentSize element
            return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1, p2 + 1); //increment the currentSize, the function return, and the element in array 2
        }
    }
    else if(arr1[p1] != '\0'){ //if only array 1 isn't finished 
        destArray[currentSize] = arr1[p1]; //place the p1 element in currentSize 
        return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1 + 1, p2); //continue to do so until it is complete 
    }
    else if(arr2[p2] != '\0'){ //if only array 2 isn't finished
        destArray[currentSize] = arr2[p2]; //place the p2 element in currentSize 
        return 1 + alphaMerge(destArray, currentSize + 1, arr1, arr2, p1, p2 + 1); //continue to do so until it is complete 
    } 
    return 0;
}
