#include <iostream>
using namespace std; 

//Template to handle all data types
template<typename Type> 
//Class to do operations with dynamic arrays 
class dynamicArray{
//Outstream operator overload
friend ostream& operator<<(ostream& LHS, dynamicArray<Type> RHS){
    LHS<<"[ ";
//Print out array values inside of brackets 
    for(int i = 0 ; i<RHS.getSize() ; i++){
        //Load the ostream parameter with array values 
        LHS<<RHS.at(i);
        if(i < RHS.getSize() - 1)
            cout<<" , ";
    }
    
    LHS<<" ] "<<endl;
    //return the ostream parameter 
    return LHS;
}

//Insertion operator overload 
friend istream& operator>>(istream& LHS, dynamicArray<Type>& RHS){
    
    int tempSize = RHS.currentSize;
    if(RHS.arr != nullptr){ // Avoid Memory leaks
        delete[] RHS.arr;
        RHS.arr = nullptr; // Avoid dangling ptr
    }
    RHS.currentSize = 0; // Reset Size
    //Allocate memory for a temp array
    Type *newArr = new Type[tempSize];
    //Insert N values into the temp array
    for(int i = 0 ; i < tempSize ; i++){
        LHS>>newArr[i];
    }
    //Set array pointer to the temp array 
    RHS.arr = newArr; 
    //Set array size to the temp size 
    RHS.currentSize = tempSize; 
    //Return istream parameter 
    return LHS;
    
}

private:
//Dynamic template array, handles all data types
    Type* arr;
//Size attribute
    unsigned int currentSize; 
public: 
//Default constructor 
    dynamicArray(); 
//Parameter constructor, passes type of array, and array size
    dynamicArray(Type*, unsigned int);
//Copy constructor for any type of array
    dynamicArray(const dynamicArray<Type>&);
//Destructor 
    ~dynamicArray(); 
//Returns array index
    Type at(unsigned int) const; 
//Gets size of array
    unsigned int getSize() const; 
//Inserts array element in the back
    void pushBack(Type);
//Inserts array element in the front 
    void pushFront(Type);
//Inserts array element at index 
    void insert(Type, unsigned int);
//Clears the array
    void clearArray();
//Deletes array element at index
    void deleteAt(unsigned int);
//Sorts the array in ascending order (selection sort)
    void sort(); 
//Assignment operator overload for all data types 
    void operator=(const dynamicArray<Type>&);
//Bracket operator overload for all data types
    Type& operator[](unsigned int);
};

template<typename Type>
dynamicArray<Type>::dynamicArray(){
    //Base array attributes 
    currentSize = 0; 
    arr = nullptr; 
}

template<typename Type>
dynamicArray<Type>::dynamicArray(Type* array, unsigned int size){
    //Allocate new array 
    arr = new Type[size]; 
    //Load array 
    for(int i = 0 ; i<size ; i++){
        arr[i] = array[i]; 
    }
    //Set size 
    currentSize = size;
}

template<typename Type>
dynamicArray<Type>::dynamicArray(const dynamicArray<Type>& copy){
    //Set size with copy
    currentSize = copy.currentSize; 
    //Allocate array
    arr = new Type[copy.currentSize];
    //Deep copy
    for(int i = 0 ; i<copy.currentSize ; i++){
        arr[i] = copy.arr[i];
    }
}

template<typename Type>
dynamicArray<Type>::~dynamicArray(){
    //Deallocate array and reset attributes 
    delete [] arr; 
    currentSize = 0; 
}

template<typename Type>
void dynamicArray<Type>::clearArray(){
    //Deallocate array and reset attributes
    delete [] arr; 
    currentSize = 0; 
    //Allocate brand new array 
    arr = new Type [currentSize];
}

template<typename Type>
void dynamicArray<Type>::operator=(const dynamicArray<Type>& copy){
    //Deallocate array and set attribues to RHS
    delete [] arr; 
    currentSize = copy.currentSize; 
    //Allocate new array
    arr = new Type[currentSize];
    //Deep copy
    for(int i = 0 ; i<currentSize ; i++){
        arr[i] = copy.arr[i];
    }
}

template<typename Type>
unsigned int dynamicArray<Type>::getSize() const{
    //Return the size
    return currentSize; 
}

template<typename Type>
void dynamicArray<Type>::pushBack(Type x){
    //Allocate array of one more 
    Type *temp = new Type[currentSize + 1];
    //Deep copy
    for(int i = 0 ; i<currentSize ; i++){
        temp[i] = arr[i]; 
    }
    //Set last element to the new element 
    temp[currentSize] = x; 
    //Deallocate array
    delete [] arr; 
    //Set array pointer to the temp
    arr = temp; 
    //Set array size to plus one 
    currentSize = currentSize + 1; 
}

template<typename Type>
void dynamicArray<Type>::pushFront(Type x){
    //Allocate array of one more 
    Type *temp = new Type[currentSize + 1];
    //Set first element to new element 
    temp[0] = x;
    //Deep copy
    for(int i = 1 ; i<currentSize ; i++){
        temp[i] = arr[i]; 
    } 
    //Deallocate array
    delete [] arr; 
    //Set array pointer to temp 
    arr = temp; 
    //Set array size to plus one
    currentSize = currentSize + 1; 
}

template<typename Type>
void dynamicArray<Type>::insert(Type x, unsigned int index){
    //Allocate new array of one more
    Type *temp = new Type[currentSize + 1];
    //Deep copy up to the index
    for(int i = 0 ; i<index ; i++){
        temp[i] = arr[i];
    }
    //Insert new element at index
    temp[index] = x;
    //Deep copy after index one array position over 
    for(int i = index + 1 ; i<currentSize + 1 ; i++){
        temp[i] = arr[i - 1];
    }
    //Deallocate array and set array element to temp values 
    delete [] arr; 
    arr = temp; 
    currentSize = currentSize + 1; 
}

template<typename Type>
void dynamicArray<Type>::deleteAt(unsigned int index){
    //Is index in bounds
    if(index<0 || index >= currentSize){
        return;
    }
    //Allocate new array one less 
    Type *temp = new Type[currentSize - 1];
    //Deep copy till index
    for(int i = 0 ; i<index ; i++){
        temp[i] = arr[i];
    }
    //Skip index and deep copy the rest one array position to the left 
    for(int i = index + 1 ; i<currentSize ; i++){
        temp[i - 1] = arr[i];
    }
    //Deallocate array pointer and set it to temp pointer and values 
    delete [] arr; 
    arr = temp; 

    currentSize = currentSize - 1; 
}

template<typename Type>
Type& dynamicArray<Type>::operator[](unsigned int index){
    //Check index is in bounds
    if(0 <= index && index < (*this).currentSize){
        //Return array at index
        return arr[index];
    }
    else{
        exit(1);
    }
}

template<typename Type>
Type dynamicArray<Type>::at(unsigned int index) const{
    if(index < 0 || index >= currentSize){ //if invalid index
        exit(1);
    }
    return arr[index]; //return the element 
}

template<typename Type>
void dynamicArray<Type>::sort(){
    //Initialize sort variables 
    int i, j, min_idx; 
    //Temp object
    Type temp;
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < (*this).getSize()-1; i++){ 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < (*this).getSize(); j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
  
        // Swap the found minimum element with the first element 
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    } 
}

