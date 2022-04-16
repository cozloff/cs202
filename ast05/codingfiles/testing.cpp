#include <iostream> 
#include "digAdventureGame.h"
using namespace std;



int main(){
    entity *bPtr = new rock();
    unsigned int rslt = bPtr->destroy(); delete bPtr;
    bPtr = new carnivorous_silverfish();
    rslt = bPtr->destroy(); delete bPtr;
}