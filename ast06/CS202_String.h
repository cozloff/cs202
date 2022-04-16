#include <iostream> 
using namespace std;

class CS202_String{
//friend operators:
friend istream& operator>>(istream&, CS202_String&); 
friend ostream& operator<<(ostream&, CS202_String);

private:
    char* charArr = nullptr;
    int size = 0; 
public: 
    // Default Constructor
    CS202_String();
    // Param Constructor 1
    CS202_String(const char*);
    // Copy Constructor
    CS202_String(const CS202_String&);
    // Destructor
    ~CS202_String();
    // Member Functions
    void PushBack(const char*); 
    void DeleteAt(int); 
    void PrintString() const;
    int GetSize() const;
    char At(int) const;
    int FindSubString(const CS202_String&) const; 
    static CS202_String Concatinate(const CS202_String&, const CS202_String&);

    //Member Operators:  
    void operator=(const CS202_String&); // Assingment Operator to prevent memory leaks
    char &operator[](int); //The bracket operator should return the character located at the index
    
    CS202_String operator+(CS202_String);
    CS202_String operator+(const char*);

    CS202_String operator++();
    CS202_String operator++(int);

    CS202_String operator-(CS202_String);
    CS202_String operator-(const char*);

    CS202_String operator*(unsigned int);

    bool operator<(const CS202_String &); 
    bool operator==(const CS202_String &);
    bool operator!=(const CS202_String &);
    bool operator>(const CS202_String &);
    bool operator<=(const CS202_String &);
    bool operator>=(const CS202_String &);
};

//Do == & < first: != : !(A==B) | > : !(A<B) && !(A==B)