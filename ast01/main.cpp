/*
 * Name: Dylan Cozloff, 2001668380, Assignment 01
 * Description: Program that allows nutrition data about cereals. 
 * Input: File name, cereal name, cereal specifications, 0-6 menu options.  
 * Output: Specific and or sorted data about the cereals in the file.
 */

#include <fstream> //fstream library
#include <iostream> //iostream library
#include <string> //string library

using namespace std; //Allows you to ignore std::

/*
 * stuct_identifier: cereal
 * constructors: n/a
 * public functions: no functions, but all members are public variables representing some specification about cereal
 * static members: n/a
 */
struct cereal{
  string name;
  char mfr, type;
  int calories, protein, fat, sodium, sugars, potass, vitamins, shelf;
  float weight, cups, rating, fiber, carbo;
};

const int maxSize = 100; //constant integer variable, used to extend beyond the length of the intended array

bool readFile(string fName, cereal cArr[],int &cSize); //reads in the file data, and stores it into an array
void printCereal(const cereal &c, ostream &out); //Used to print out data to the terminal or to another file
void printCerealArr(const cereal cArr[], const int &cSize, ostream &out); //Used to print every element of the cereal array
float getNumber(string fieldName, const cereal &c); //Function to extract a numeric field from cereal
char getChar(string fieldName, const cereal &c);   //Function to extract char field from cereal
string getName(const cereal &c); //Function to extract the name of cereal
int menu(); //Function to print the menu and get menu option input
void searchByName(string name, const cereal cArr[], const int &cSize, ostream &out); //Function to search cereal array by name
void swapCereal(cereal &c1, cereal &c2); //Function to swap two cereals in array (for sorting)
void sortGreatestToLeast(char fieldType, string fieldName, cereal cArr[], const int &cSize); //Function to sort the array on any field
cereal getMaxOrMin(string fieldName, const cereal cArr[], const int &cSize, bool max); //Function to get cereal with max or min value in a field

int main(int argc, char **argv){ //the argument count, and an array of pointers for each argument
  cereal cerealArr[maxSize];
  int cerealSize = 0;
  string fName = "";

  if(argc == 2){ //If there are 2 arguments in the command line
    fName = argv[1]; //set the second argument as the file name
  } 
  else{
    cout<<"Please Enter File Name"<<endl;
    cin>>fName; // enter file name
  }

  while(!readFile(fName, cerealArr, cerealSize)){ //while the file isn't read
    cout<<"Please Enter File Name"<< endl;
    cin>>fName; // Keep prompting the user
  }
  cout<<"File Opened!"<<endl;

  while(true){ //infinite while loop
    switch(menu()){ //create a switch case function with the menu options
    case 1:{ //search by name selection
      string cerealName = "";
      cout<<"Enter Cereal Name"<<endl; //Prompt the user to enter the cereal name
      cin.ignore(); //clear the input buffer
      getline(cin, cerealName); // enter cereal name, and get the whole line
      searchByName(cerealName, cerealArr, cerealSize, cout); //print the cereal by name selection
      break;
    }
    case 2:{ //sort cereal array selection
      char typechoice = 'a';
      string fieldchoice = "";
      cout<<"What is the type of field you are sorting on?"<<endl; //Prompt the user to select a field type
      cout<<"   (n)umber"<<endl;
      cout<<"   (c)haracter"<<endl;
      cout<<"   (s)tring"<<endl;
      cin>>typechoice; //get the users field type selection
      cout<<"What field are you sorting on?"<<endl; //Prompt the user to select a field
      cin>>fieldchoice; //get the users field selection
      sortGreatestToLeast(typechoice, fieldchoice, cerealArr, cerealSize); //Call the sort function with the selections
      cout<<"Sorting complete."<<endl;
      break;
    }
    case 3:{ //max or min selection
      int numchoice = 0; //declare a int variable to hold the min or max number selection
      bool minOrmax = false;   //declare a bool variable to hold the bool to determine min or max
      string minOrMax = ""; //declare a string variable to hold either min or max for the terminal display
      string numfieldchoice = ""; //declare a string variable to hold the field name
      cout<<"Do you want to find the max or the min value?"<<endl; //Prompt the user to select min or max
      cout<<"(0) min"<<endl;
      cout<<"(1) max"<<endl;
      cin >> numchoice; // get the number the user selects
      if(numchoice == 0){ //If the choice is 0 set to minimum
        minOrMax = "Min";
        minOrmax = false;
      } 
      else if(numchoice == 1){ // If the choice is 1 set to maximum
        minOrMax = "Max";
        minOrmax = true;
      }
      cout<<"What numeric field do you want to look for?"<<endl;
      cin>>numfieldchoice; //get the field from the user
      cout<<minOrMax<<"Found!"<<endl;
      cereal maxOrMinCereal = getMaxOrMin(numfieldchoice, cerealArr, cerealSize, minOrmax); //create an object to hold the max or min
      printCereal(maxOrMinCereal, cout); //print the cereal min or max
      break;
    }
    case 4:{ //write to file selection
      string chosenFileName = ""; //declare a string variable to hold the chosen file name
      cout<<"Enter the file name."<<endl;
      cin>>chosenFileName; //get chosen file name from user
      ofstream outFile; //create out file stream
      outFile.open(chosenFileName); //open the chosen file
      printCerealArr(cerealArr, cerealSize, outFile); //print the cereal to the out file
      outFile.close(); //close the file
      cout<<"Saved to "<<chosenFileName<<"."<<endl;
      break;
    }
    case 5:{ //print array selection
      printCerealArr(cerealArr, cerealSize, cout); //Prints the cereal array to the terminal
      break;
    }
    case 6:{ //quit the program selection
      return 0; //stops the program
    }
    }
  }
  return 0; //Exit code
}

bool readFile(string fName, cereal cArr[], int &cSize){
  ifstream inFile; //in file stream
  inFile.open(fName); //open the file fName
  if(!inFile.is_open()){ //if the file doesn't open
    cout<<"Error: File failed to open."<< endl; 
    return false; //return false so main knows it was unsuccessful
  }
  cSize = 0; //Initiallize cSize to zero first
  string temp = ""; //Store strings read from file
  getline(inFile, temp); //Reads in the Header
  while(cSize < maxSize){ //while the cereal array is less than a 100
    if(!getline(inFile, temp, '\t')){ //if I didn't read something after the new line
      inFile.close(); //Close the file, because there are no remaining cereals
      return true; //return true so that main knows the file has been read completely
    }
    cArr[cSize].name = temp; //Sets the name of this element as the temp which is the first item in the line to the tab
    getline(inFile, temp, '\t'); //Reads everything up to the next tab
    cArr[cSize].mfr = temp[0]; //Sets the MFR of this element as a char of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].type = temp[0]; //Sets the type of this element and stores it as a char of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].calories = stoi(temp); //Sets the calories of this element and stores it as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].protein = stoi(temp); //Sets the protein of this element as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].fat = stoi(temp); //Sets the fat of this element as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].sodium = stoi(temp); //Sets the sodium of this element as an int of the temp
    getline(inFile, temp, '\t');          
    cArr[cSize].fiber = stof(temp); //Sets the fiber of this element as a float of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].carbo = stof(temp); //Sets the carbo of this element as a float of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].sugars = stoi(temp); //Sets the sugar of this element as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].potass = stoi(temp); //Sets the potassium of this element as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].vitamins = stoi(temp); //Sets the vitamins of this element as an int of the temp
    getline(inFile, temp, '\t'); 
    cArr[cSize].shelf = stoi(temp); //Sets the shelf of this element as an int of the temp
    getline(inFile, temp, '\t');          
    cArr[cSize].weight = stof(temp); //Sets the weight of this element as a float of the temp
    getline(inFile, temp, '\t');          
    cArr[cSize].cups = stof(temp); //Sets the cups of this element as a float of the temp
    getline(inFile, temp, '\n'); //Reads the rest to the endline and stores it in temp 
    cArr[cSize].rating = stof(temp); //Sets the rating of this element as a float of the temp
    cSize++; //records the increased size of the array
  }
  inFile.close(); //Close the file
  return true; //return true so that main knows the file has successfully been read
}

void printCereal(const cereal &c, ostream &out){
  out<<"Cereal:"<<endl; //prints the basic framework of the cereal text
  out<<"*******************"<<endl;
  out<<"* "<<c.name<<endl; //prints the specific cereal field by accessing the object
  out<<"*******************"<<endl;
  out<<"* MFR: "<<c.mfr<<endl;
  out<<"* TYPE: "<<c.type<<endl;
  out<<"* CALORIES: "<<c.calories<<endl;
  out<<"* PROTEIN: "<<c.protein<<endl;
  out<<"* FAT: "<<c.fat<<endl;
  out<<"* SODIUM: "<<c.sodium<<endl;
  out<<"* FIBER: "<<c.fiber<<endl;
  out<<"* CARBO: "<<c.carbo<<endl;
  out<<"* SUGARS: "<<c.sugars<<endl;
  out<<"* POTASS: "<<c.potass<<endl;
  out<<"* VITAMINS: "<<c.vitamins<<endl;
  out<<"* SHELF: "<<c.shelf<<endl;
  out<<"* WEIGHT: "<<c.weight<<endl;
  out<<"* CUPS: "<<c.cups<<endl;
  out<<"* RATING: "<<c.rating<<endl;
  out<<"*******************"<<endl;
  out<<endl; //spaces out the different cereals
}

void printCerealArr(const cereal cArr[], const int &cSize, ostream &out){
  for(int i=0; i < cSize; i++){ //Goes through every element of the cereal file array 
    printCereal(cArr[i], out); //And passes it to print the cereal, to print every individual cereal
  }
}

float getNumber(string fieldName, const cereal &c){
  if(fieldName == "calories") //If the selected field is chosen 
    return c.calories; //return the specific field by accessing the cereal object 
  if(fieldName == "protein")
    return c.protein;
  if(fieldName == "fat")
    return c.fat;
  if(fieldName == "sodium")
    return c.sodium;
  if(fieldName == "fiber")
    return c.fiber;
  if(fieldName == "carbo")
    return c.carbo;
  if(fieldName == "sugars")
    return c.sugars;
  if(fieldName == "potass")
    return c.potass;
  if(fieldName == "vitamins")
    return c.vitamins;
  if(fieldName == "shelf")
    return c.shelf;
  if(fieldName == "weight")
    return c.weight;
  if(fieldName == "cups")
    return c.cups;
  if(fieldName == "rating"){
    return c.rating;
  }
  return 0; 
  
}

char getChar(string fieldName, const cereal &c){
  if(fieldName == "mfr") //If the selected field is chosen 
    return c.mfr; //return the specific field by accessing the cereal object
  if(fieldName == "type"){
    return c.type;
}
  return 0; 
}

string getName(const cereal &c){ 
  return c.name; //return the name by accessing the cereal object
}

int menu(){
  string x = ""; //declare a string variable for the option input
  cout<< "--------------------------"<<endl; //Display the menu options to the terminal
  cout<< "|          Menu          |"<<endl;
  cout<< "--------------------------"<<endl;
  cout<< " (1) Search by Name"<<endl;
  cout<< " (2) Sort Cereal Array"<<endl;
  cout<< " (3) Find Max or Min Cereal"<<endl;
  cout<< " (4) Write Cereal Array to File"<<endl;
  cout<< " (5) Print the Whole Array"<<endl;
  cout<< " (6) Quit"<<endl;
  cout<< "--------------------------"<<endl;
  cin>>x; //take the input from the user
  while(x != "1" && x != "2" && x != "3" && x != "4" && x != "5" && x != "6"){ //If none of the menu options are selected 
    cout<<"Error: Invalid Entry."<< endl; //Display an error message
    cout<<"--------------------------"<<endl; 
    cout<<"|          Menu          |"<<endl;
    cout<<"--------------------------"<<endl;
    cout<<" (1) Search by Name"<<endl;
    cout<<" (2) Sort Cereal Array"<<endl;
    cout<<" (3) Find Max or Min Cereal"<<endl;
    cout<<" (4) Write Cereal Array to File"<<endl;
    cout<<" (5) Print the Whole Array"<<endl;
    cout<<" (6) Quit"<<endl;
    cout<<"--------------------------"<<endl;
    cin>>x; //take in the new input from the user
  }
  return stoi(x); //convert the string input into an int and return it 
}

void searchByName(string name, const cereal cArr[], const int &cSize, ostream &out){
  for(int i=0; i<cSize; i++){ //go through every element of the cereal array
    if(cArr[i].name == name){ //access the name of the objects, and if it equals the selected name 
      printCereal(cArr[i], out); //pass the selected cereal object to be printed 
      return; //exit the function
    }
  }
  out<<"Error: Did not find that cereal."<<endl;
}

void swapCereal(cereal &c1, cereal &c2){
  cereal temp; //create a temporary object
  temp = c1; //make temp the first object
  c1 = c2; //make the first object the second object
  c2 = temp; //then make the second object the temp, which stored the original first object
}

void sortGreatestToLeast(char fieldType, string fieldName, cereal cArr[], const int &cSize){
  for(int i = 0; i < cSize - 1; i++){ //Create a double for loop to compare all elements to one other element
    for(int j = 0; j < cSize - i - 1; j++){
      bool lt = false; //set a bool variable to false in order to test the two elements
      if(fieldType == 'n'){ //if the field type is a number
        lt = (getNumber(fieldName, cArr[j])) < getNumber(fieldName, cArr[j + 1]); //compare the 2 elements using getNumber, setting the bool
      } 
      else if(fieldType == 'c'){ //if the field type is a char
        lt = (getChar(fieldName, cArr[j])) < getChar(fieldName, cArr[j + 1]); //compare the 2 elements using getChar, setting the bool
      } 
      else if(fieldType == 's'){ //if the field type is a string
        lt = (getName(cArr[j])) < getName(cArr[j + 1]); //compare the 2 elements using getName, setting the bool
      }
      if(lt == true){ //if the element is larger than the other
        swap(cArr[j], cArr[j + 1]); //swap them in the array order
      }
    }
  }
}

cereal getMaxOrMin(string fieldName, const cereal cArr[], const int &cSize, bool max){
  char typechoice = 'n'; //set the type choice to numbers
  cereal copyArr[maxSize]; //create a copy array so it doesn't alter the original
  for(int i = 0; i < cSize; i++){ //use a for loop to copy each element
    copyArr[i] = cArr[i];
  }
  sortGreatestToLeast(typechoice, fieldName, copyArr, cSize); //first order the field
  if(max){ //If the bool is true 
    return copyArr[0]; //return the first element of the array aka the max
  }
  return copyArr[cSize - 1]; //return the last element of the array aka the min
}