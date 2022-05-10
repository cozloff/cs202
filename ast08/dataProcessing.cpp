#include "dataProcessing.h"
using namespace std;

// ******************************
// * Global Helper Functions
// ********************************

// ---------------------
// isInteger
//    returns true if the string
//    parameter is an integer
//---------------------- **
bool isInteger(string s){
    // If length is 0
    if(s.length() == 0){ return false; }
    // If first char is not '-' or a digit
    if(s[0] != '-' && (s[0] < 48 || s[0] > 57)){ return false; }
    // For all chars
    for(unsigned int i = 1; i < s.length(); i++){
        // If not a digit
        if(s[i] < 48 || s[i] > 57){
            return false;
        }
    }
    // Succesfully made it through
    return true;
}

// ---------------------
// isChar
//    returns true if the string
//    parameter is a char
//---------------------- **
bool isChar(string s){
    // If length is 1
    if(s.length() == 1){
        // Return (is this a not digit?)
        return (s[0] < 48 || s[0] > 57);
    }
    return false;
}

// ---------------------
// isDouble
//    returns true if the string
//    parameter is a double
//---------------------- **
bool isDouble(string s){
    // If length is 0
    if(s.length() == 0){ return false; }
    // If first char is not '-' or a digit
    if(s[0] != '-' && (s[0] < 48 || s[0] > 57)){ return false; }
    
    bool foundDecimal = false;
    // For all chars
    for(unsigned int i = 1; i < s.length(); i++){
        // If not a digit or a decimal
        if((s[i] < 48 || s[i] > 57) && s[i] != '.'){
            return false;
        }
        // If a decimal
        if(s[i] == '.'){
            // If already found a decimal
            if(foundDecimal){
                return false;
            }
            foundDecimal = true;
        }
    }
    // Succesfully made it through
    return true;
}

// ---------------------
// isBool
//    returns true if the string
//    parameter is a bool
//---------------------- **
bool isBool(string s){
    return (s == string("true") || s == string("false")); 
}

// ---------------------
// stob
//   convert string to bool
//---------------------- **
bool stob(string s){
    if(s == string("true")){
        return true;
    }
    else if(s == string("false")){
        return false;
    }
    cout << "ERROR: Tried to convert something that is not a bool." << endl;
    exit(1);
    return false;
}

// ---------------------
// getDataType
//    Confidence10
//---------------------- **
unsigned int getDataType(string garbage){
    // YOUR CODE HERE 
    if(isInteger(garbage) == true){
        return INT;
    }
    else if(isChar(garbage) == true){
        return CHAR;
    }
    else if(isBool(garbage) == true){
        return BOOL;
    }
    else if(isDouble(garbage) == true){
        return DOUBLE;
    }
    else{
        return STRING; // Students may want to replace
    }
}

// ******************************
// * dataElementBase
// ********************************

// ---------------------
// param constructor dataElementBase
//    <your comments here>
//---------------------- **
dataElementBase::dataElementBase(unsigned short dt){
    // YOUR CODE HERE
    dataType = dt; 
}

// ---------------------
// copy constructor dataElementBase
//    <your comments here>
//---------------------- **
dataElementBase::dataElementBase(const dataElementBase& copy){
    // YOUR CODE HERE
    dataType = copy.dataType;
}

// ---------------------
// assignment operator overload dataElementBase
//    <your comments here>
//---------------------- **
void dataElementBase::operator=(const dataElementBase& copy){
    // YOURCODE HERE
    this -> dataType = copy.getDataType();
}

// ---------------------
// destructor dataElementBase
//    Virtual destructor that does nothing.

//    It must be here to call the dataElement
//    destructor, which in turn will deallocate
//    any data from a class (like string). 
//---------------------- **
dataElementBase::~dataElementBase(){}

// ---------------------
// getDataType
//    return dataType of dataElement
//---------------------- **
unsigned short dataElementBase::getDataType() const{
    return this->dataType;
}

// ---------------------
// getNext
//    return link to next dataElement
//---------------------- **
dataElementBase *dataElementBase::getNext() const{
    return next;
}

// ---------------------
// getPrev
//    return link to previous dataElement
//---------------------- **
dataElementBase *dataElementBase::getPrev() const{
    return prev;
}

// ---------------------
// link
//    <your comments here>
//---------------------- **
void dataElementBase::link(dataElementBase *node){
    // YOUR CODE HERE
    if(node != nullptr){
        this->next = node; 
        node->prev = this;
    } 
}

// ---------------------
// compare
//    Function is used to compare 
//      2 dataElements. Must be called
//      like this: deb1->compare(deb2)
//
//      The pointer is required to call getData
//      the return pointer must be casted to
//      the correct type, then compared. 
//---------------------- **
short dataElementBase::compare(dataElementBase *deb){
    if(deb == nullptr){
        cout << "ERROR: Tried to compare nullptr." << endl;
    }
    // If the dataTypes are not equal
    if(dataType < deb->dataType){
        return LESSTHAN;
    }
    if(dataType > deb->dataType){
        return GREATERTHAN;
    }
    // Datatypes are equal 
    switch(dataType){
        case(INT):{
            if(*(static_cast<int*>(this->getData())) < *(static_cast<int*>(deb->getData()))){
                return LESSTHAN;
            }
            if(*(static_cast<int*>(this->getData())) > *(static_cast<int*>(deb->getData()))){
                return GREATERTHAN;
            }
            break;
        }
        case(CHAR):{
            if(*(static_cast<char*>(this->getData())) < *(static_cast<char*>(deb->getData()))){
                return LESSTHAN;
            }
            if(*(static_cast<char*>(this->getData())) > *(static_cast<char*>(deb->getData()))){
                return GREATERTHAN;
            }
            break;
        }
        case(DOUBLE):{
            if(*(static_cast<double*>(this->getData())) < *(static_cast<double*>(deb->getData()))){
                return LESSTHAN;
            }
            if(*(static_cast<double*>(this->getData())) > *(static_cast<double*>(deb->getData()))){
                return GREATERTHAN;
            }
            break;
        }
        case(BOOL):{
            if(*(static_cast<bool*>(this->getData())) < *(static_cast<bool*>(deb->getData()))){
                return LESSTHAN;
            }
            if(*(static_cast<bool*>(this->getData())) > *(static_cast<bool*>(deb->getData()))){
                return GREATERTHAN;
            }
            break;
        }
        case(STRING):{
            if(*(static_cast<string*>(this->getData())) < *(static_cast<string*>(deb->getData()))){
                return LESSTHAN;
            }
            if(*(static_cast<string*>(this->getData())) > *(static_cast<string*>(deb->getData()))){
                return GREATERTHAN;
            }
            break;
        }
    }
    return EQUAL;
}

// ---------------------
// getNewDataElement
//    <your comments here>
//---------------------- **
dataElementBase* dataElementBase::getNewDataElement(unsigned short dataType, string data){
    // YOUR CODE HERE

    if(dataType == INT){
        return new dataElement<int>(dataType , stoi(data));
    }
    else if(dataType == CHAR){
        return new dataElement<char>(dataType , data[0]);
    }
    else if(dataType == DOUBLE){
        return new dataElement<double>(dataType , stod(data));
    }
    else if(dataType == BOOL){
        if(data == "true"){
            return new dataElement<bool>(dataType , true);
        }
        else if(data == "false"){
            return new dataElement<bool>(dataType , false);
        }
    }
    else if(dataType == STRING){
        return new dataElement<string>(dataType , data);
    }
    return nullptr; // Students may want to replace
}

// ---------------------
// deepCopyDataElement
//    <your comments here>
//---------------------- **
dataElementBase* dataElementBase::deepCopyDataElement(dataElementBase *deb){
    // YOUR CODE HERE
	if(deb != nullptr) {
		unsigned short dt = deb -> dataType;
		if(dt == INT){
			void *ref = deb->getData();
			int result = *(static_cast <int*>(ref));
			return new dataElement<int>(dt,result);

		}
		else if(dt == CHAR){
			void *ref = deb->getData();
			char result = *(static_cast <char*>(ref));
			return new dataElement<char>(dt,result);
		}
		else if(dt == DOUBLE){
			void *ref = deb->getData();
			double result = *(static_cast <double*>(ref));
			return new dataElement<double>(dt,result);
		}
		else if(dt == BOOL){
			void *ref = deb->getData();
			bool result = *(static_cast <bool*>(ref));
			return new dataElement<bool>(dt,result);
		}
		else if(dt == STRING){
			void *ref = deb->getData();
			string result = *(static_cast <string*>(ref));
			return new dataElement<string>(dt,result);
		}
	}
    return nullptr; // Students may want to replace
}

// ---------------------
// swap
//    <your comments here>
//---------------------- **
void dataElementBase::swap(dataElementBase* A, dataElementBase* B){
    // YOUR CODE HERE
    //See if they're adjacent
    if(A->next == B){
        if(A -> prev != nullptr)
            A -> prev -> next = B; 
        A -> next = B -> next; 
        B -> next = A; 
        B -> prev = A -> prev;
        A -> prev = B;
        if(A -> next != nullptr)
            A -> next -> prev = A; //potential for segfault
    }
    else if(B->next == A){
        if(B -> prev != nullptr)
            B -> prev -> next = A; 
        B -> next = A -> next; 
        A -> next = B; 
        A -> prev = B -> prev;
        B -> prev = A;
        if(B -> next != nullptr)
            B -> next -> prev = B; //potential for segfault
    }
    else{ 

        dataElementBase *Aprev = A -> prev;
        dataElementBase *Bprev = B -> prev;
        dataElementBase *Anext = A -> next;
        dataElementBase *Bnext = B -> next; 
        B -> prev = Aprev; 
        B -> next = Anext; 
        A -> prev = Bprev; 
        A -> next = Bnext; 
        if(Aprev != nullptr)
            Aprev -> next = B; 
        if(Anext != nullptr)
            Anext -> prev = B;
        if(Bprev != nullptr)
            Bprev -> next = A;
        if(Bnext != nullptr)
            Bnext -> prev = A;     

    }
}

// ******************************
// * dataElement
// ********************************

// ---------------------
// param constructor dataElement
//    constructor to initliaze the data
//    must inline a call to the dataElementBase ctor.
//---------------------- **
template<typename t>
dataElement<t>::dataElement(unsigned short dt, t d) : dataElementBase(dt){
    data = d;
}

// ---------------------
// getData
//    return a void pointer 
//    to the data
//---------------------- **
template<typename t>
void* dataElement<t>::getData(){
    return static_cast<void*>(&data);
}

// ---------------------
// printElement
//    print out the data
//---------------------- **
template<typename t>
void dataElement<t>::printElement(ostream& out) const{
    out << data;
}

// ******************************
// * garbagePile
// ********************************

// ---------------------
// default constructor garbagePile
//    <your comments here>
//---------------------- **
garbagePile::garbagePile(){
    // YOUR CODE HERE
    head = nullptr;
    tail = nullptr; 
    size = 0;
}

// ---------------------
// copy constructor garbagePile
//    <your comments here>
//---------------------- **
garbagePile::garbagePile(const garbagePile &copy){
    // YOUR CODE HERE

    // Makes a deep copy of parameter head, and sets both currents to each head 
    head = dataElementBase::deepCopyDataElement(copy.head);
    dataElementBase *current = head; 
    dataElementBase *copyCurrent = copy.head; 

    //While the copy current is not at the last element
    while(copyCurrent != nullptr && copyCurrent->getNext() != nullptr) {
        //Gets the copie's next link, deepcopies, and links to current 
        copyCurrent = copyCurrent -> getNext();
        dataElementBase *nextCurrent = dataElementBase::deepCopyDataElement(copyCurrent);
        current -> link(nextCurrent);
        //Update tail and current
        current = current -> getNext();
        tail = current; 
    }
    //Update size
    size = copy.size; 
}

// ---------------------
// operator assignment overload
//    <your comments here>
//---------------------- **
void garbagePile::operator=(const garbagePile &copy){
    // YOUR CODE HERE
    if(head != nullptr){
        clearGarbagePile();
        head = nullptr; 
        tail = nullptr; 
        size = 0;
    }

    // Makes a deep copy of parameter head, and sets both currents to each head 
    head = dataElementBase::deepCopyDataElement(copy.head);
    dataElementBase *current = head; 
    dataElementBase *copyCurrent = copy.head; 

    //While the copy current is not at the last element
    while(copyCurrent -> getNext() != nullptr){

        //Gets the copie's next link, deepcopies, and links to current 
        copyCurrent = copyCurrent -> getNext();
        dataElementBase *nextCurrent = dataElementBase::deepCopyDataElement(copyCurrent);
        current -> link(nextCurrent);

        //Update tail and current
        current = current -> getNext();
        tail = current; 
    }
    //Update size
    size = copy.size; 
}

// ---------------------
// destructor for garbagePile
//    <your comments here>
//---------------------- **
garbagePile::~garbagePile(){
    // YOUR CODE HERE
    clearGarbagePile();
}

// ---------------------
// addItem
//    <your comments here>
//---------------------- **
void garbagePile::addItem(string garbage){
    // YOUR CODE HERE
    size++;
    unsigned short dt = getDataType(garbage); //works
    dataElementBase *newElement = dataElementBase::getNewDataElement(dt, garbage);

    if(tail==nullptr || head ==nullptr){
        tail = newElement; 
        head = tail;
        return; 
    }

    tail -> link(newElement);

    tail = tail -> getNext();
}


// ---------------------
// operator[]
//    <your comments here>
//---------------------- **
dataElementBase *garbagePile::operator[](unsigned int index){
    // YOUR CODE HERE
    dataElementBase *current = head;
    for(size_t i = 0 ; i < index ; i++){
        current = current -> getNext(); 
    }
    return current; 
}

// ---------------------
// clearGarbagePile
//    <your comments here>
//---------------------- **
void garbagePile::clearGarbagePile(){
    // YOUR CODE HERE

    if(head != tail){
        head = head -> getNext(); 
        delete head -> getPrev(); 
        clearGarbagePile(); 
    }    
    delete tail; 
    head = nullptr; 
    tail = nullptr; 
    size = 0;

}

// ---------------------
// sort
//    <your comments here>
//---------------------- **
void garbagePile::sort(){
    // YOUR CODE HERE

    for(size_t i = 0 ; i < size ; i++){
    	dataElementBase * outer = (*this)[i];
        for(size_t j = i + 1 ; j < size; j++){
        	dataElementBase * inner = (*this)[j];
            if(outer->compare((* this)[j]) == GREATERTHAN){
                dataElementBase::swap(outer, inner);
                if(inner->getPrev() == nullptr) {
                	// we are swapping out the head
                	this->head = inner;
                }
                if(outer->getPrev() == nullptr) {
                	this->head = inner;
                }
                if(inner->getNext() == nullptr) {
                	this->tail = inner;
                }
                if(outer->getNext() == nullptr) {
                	this->tail = outer;
                }
                outer = inner;
            }
        }
    }
}

// ---------------------
// operator<<
//    <your comments here>
//---------------------- **
ostream& operator<<(ostream& out, garbagePile gp){
    // YOUR CODE HERE
  
    if(gp.head == nullptr){
        return out;
    }


    for(size_t i = 0 ; i < gp.size ;) {
    	gp[i]->printElement(out);
    	if(i < gp.size -1) {
    		out << " ,";
    	}
    	i++;
    	if(i % 3 == 0) {
    	  	cout << endl;
    	}
    	else {
    		cout << ' ';
    	}
    }
    return out;
 
}

// ---------------------I'm a coder oooo look at me, u need any assistance me lady?? I'll give you a good debuggin and plugin
// operator>>
//    <your comments here>
//---------------------- **
istream& operator>>(istream& in, garbagePile &gp){
    // YOUR CODE HERE
    string temp; // Temp character to read into
    getline(in, temp);
    gp.addItem(temp);

    return in;
}
