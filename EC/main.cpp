
#include "dynamicArray.h"
using namespace std;

int main() {
    //////////// Ints //////////////////////
    dynamicArray<int> I; // Default Constructor
    // PushBack
    I.pushBack(3);
    I.pushBack(7);
    I.pushBack(23);
    cout << I << endl; // Insertion Operator
    if (true) {
        // Copy Constructor
        dynamicArray<int> I2 = I;
        I2.pushBack(17);
        I2.pushBack(32);
        // Assignment Operator
        I = I2;
    }
    I[2] = 12;
    I.insert(947, 4);
    cout << I << endl;
    I.insert(-1, 0);
    cout << I << endl;
    I.insert(66, 3);
    cout << I << endl;
    // GetSize
    for (unsigned int i = 0; i < I.getSize(); i++) {
        // Bracket
        cout << I.at(i) << endl;
    }
    I.deleteAt(2);
    cout << I << endl;
    I.deleteAt(0);
    cout << I << endl;
    I.deleteAt(5);
    cout << I << endl;

    //////////// Ints //////////////////////
    dynamicArray<string> S; // Default Constructor
    // PushBack
    S.pushBack("Loaf");
    cout << S << endl;
    S.pushBack("Willa");
    cout << S << endl;
    S.pushBack("Diva");
    cout << S << endl;
    S.pushBack("Pita");
    cout << S << endl;
    S.pushBack("Patty");
    cout << S << endl;
    S.pushBack("MaryAnne");
    cout << S << endl; // Insertion Operator
    // GetSize
    for (unsigned int i = 0; i < S.getSize(); i++) {
        // Bracket
        cout << S.at(i) << endl;
    }
    S.deleteAt(S.getSize() - 1);
    cout << S << endl;

    //////////// Ints //////////////////////
    dynamicArray<char> c; // Default Constructor
    // PushBack
    c.pushBack('U');
    c.pushBack('D');
    c.pushBack('i');
    c.pushBack('d');
    c.pushBack('I');
    c.pushBack('t');
    c.pushBack('!');
    cout << c << endl; // Insertion Operator
    
    while(c.getSize() > 0){
        c.deleteAt(0);
        cout << c << endl;
    }
    c.clearArray();
    cout << c << endl; 
    c.pushFront('3');
    
    cout << c << endl;
    c.clearArray(); 

    c.pushBack('y');
    cout << c << endl;
    c.pushBack('a');
    cout << c << endl;
    c.pushBack('y');
    cout << c << endl;
    c.pushBack('!');
    cout << c << endl;

    c.sort();

    cout << c << endl;

    cin >> c;
    cout << c << endl;


    // GetSize
    for (unsigned int i = 0; i < c.getSize(); i++) {
        // Bracket
        cout << c[i] << endl;
    }

    float arr[5] = {3.1,3.2,-5.44,43,12};
    dynamicArray<float> f(arr,5);
    f.sort(); 
    cout << f << endl;

    for(unsigned int i = 0; i < 10000; i++ ){
        f.pushBack(i);
    }

    if(true){
        dynamicArray<float> f1 = f;
        f1.insert(3,4);
        f1.insert(5,7);
        f = f1;
    }
    for(unsigned int i = 0; i < 100; i++ ){
        cout << f.at(i) << endl;
    }
    return 0;
}