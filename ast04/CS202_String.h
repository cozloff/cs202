#include <iostream> 
using namespace std;

class CS202_String{
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
    // Assingment Operator to prevent memory leaks 
    void operator=(const CS202_String&);
};
