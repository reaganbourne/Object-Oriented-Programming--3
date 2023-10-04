#include <iostream>
#include <string> 
#include <fstream> 
#include <cstring> 
#include "canvas.h"
using namespace std; 

student::student() {
    name= new char[2];
    strcpy(name, " "); 
    studentID=0; 
    classification = 'u'; 
    major=new char[2];
    strcpy(major, " "); 
}

student::student(const char* _name, const char* _major, int _studentID, char _classification){
    studentID= _studentID; 
    classification = _classification; 
    name= new char[strlen(_name)+1]; 
    major = new char[strlen(_major)+1]; 

    strcpy(name, _name); 
    strcpy(major, _major); 
}

student::~student(){ 
    delete [] name; 
    delete [] major; 
}

void student::operator= (const student& student){
    setName(student.getName()); 
    setClassification(student.getClassification()); 
    setMajor(student.getMajor()); 
    setID(student.getStudentID()); 
}
ostream& operator<< (ostream& s, const student& student){
    s<< "student: "<< student.getName()<<endl; 
    s<<"classification: "<< student.getClassification()<<endl; 
    s<<"major: "<<student.getMajor()<<endl; 
    s<<"student ID: "<<student.getStudentID()<<endl; 
    return s; 
}

char* student::getName() const{
    return name; 
}

char* student::getMajor() const{
    return major; 
}

int student::getStudentID() const{
    return studentID; 
}
char student::getClassification() const{
    return classification; 
}

void student::setName (const char* _name) {
    delete [] name; 
    name= new char[strlen(_name)+1]; 
    strcpy(name, _name); 
} 

void student::setMajor (const char* _major) {
    delete [] major; 
    major= new char[strlen(_major)+1]; 
    strcpy(major, _major);
} 

void student::setClassification (const char _classification) {
    classification = _classification;
} 
void student::setID (const int _ID) {
    studentID = _ID;
} 

void student::load(){
    
    char NewName[20]; 
    cout<< "Enter students name "<<endl;
    cin.ignore();
    cin.getline(NewName, 20); 
    setName(NewName);

    cin.ignore(); 
    cout << "Enter student's ID " << endl;
    cin>>studentID; 

    cin.ignore();
    cout<< "Enter students classification "<<endl; 
    cin>>classification; 
    
    char NewMajor[20];  
    cin.ignore(); 
    cout<< "Enter students major "<<endl; 
    cin.getline(NewMajor,20); 
    setMajor(NewMajor); 
}



//START OF COURSE CLASS
course::course(){
    currentSize=0; 
    maxSize=2; 
    courseName= new char[20]; 
    roster= new student[maxSize]; 

}


course::course(const char* _courseName, char _courseCode[], char _location[]) {
    currentSize=0; 
    maxSize=2; 
    courseName= new char[strlen(_courseName)+1]; 
    strcpy(courseName, _courseName); 
    strcpy(courseCode, _courseCode); 
    strcpy(location, _location); 
    roster = new student [2]; 
}

course::~course(){ 
    delete [] courseName; 
    delete [] roster; 
}


ostream& operator<< (ostream& c, const course& course){
    c<< "course name: "<< course.getCourseName()<<endl; 
    c<< "course code: "<<course.getCourseCode()<<endl; 
    c<< "course location:"<<course.getLocation()<<endl;
    for (int i=0; i<course.currentSize; i++) {
        c<<course.roster[i]; 
    } 
    return c;
}

void course::operator= (const course& course){
    setCourseName(course.getCourseName()); 
    setCourseCode(course.getCourseCode()); 
    setCourseLocation(course.getLocation()); 
}

char* course::getCourseName() const {
    return courseName; 
}

const  char* course::getCourseCode() const {
    return courseCode; 
}

const char* course::getLocation() const {
    return location; 
}

student*course::getRoster(){
    return roster; 
}

void course::setCourseName (const char* _courseName) {
    delete [] courseName; 
    courseName= new char[strlen(courseName)+1]; 
    strcpy(courseName, _courseName); 
} 

void course::setCourseCode (const char* _courseCode) {
    strcpy(courseCode, _courseCode); 
} 

void course::setCourseLocation (const char* _location) { 
    strcpy(location, _location); 
} 


void course::load() {
    char newCourseName[20];  
    
    cout<< "Enter course name "<<endl;  
    cin.ignore();
    cin.getline (newCourseName,20); 
    setCourseName(newCourseName); 

   
    cout<< "Enter course code "<<endl;
    cin.ignore();     
    cin.getline (courseCode,7); 
    
    cin.ignore();
    cout << "Enter course location" << endl;
    cin.getline (location, 10); 


    cout<<"Would you like to add students? y or n." << endl;

    char choice;
    cin>>choice;

    
    while(choice == 'y' || choice == 'Y')
    {   
       if(currentSize == maxSize)
            grow();
        roster[currentSize++].load(); 
        cout<<"Would you like to add another student. y or n.";
        cin>>choice;
    }
}

void course::addStudentsCourse(const student& student)
{
   if (currentSize == maxSize) 
        grow();
   roster[currentSize++] = student; 
}

void course::grow() 
{
   maxSize = maxSize + 10;
   student* temp = roster; 
   roster = new student[maxSize]; 
   for (int i = 0; i < maxSize-10; i++) 
   {
        roster[i] = temp[i]; 
   }
        
   delete [] temp; 
}

void course::lookup() const 
{
    int choice;
    cout<<"How would you like to search? 1. Name 2. ID"<<endl;
    cin>>choice;
    if(choice == 1){
        char *aName= new char[20];
        cout << "Type the name to be looked up: ";
        cin.ignore(); 
        cin.getline(aName, 19);
        int thisCourse = searchByName(aName); 
        
        if (thisCourse == -1)
            cout << aName << "not found in current directory\n";
        else
        {
            cout << "Entry found: ";
            cout << roster[thisCourse] ; 
        }
        
    }
    else if(choice == 2){
        int aID;
        cout<<"Type the ID you'd like to seach for."<<endl;
        cin>>aID;
        int thisCourse = searchByID(aID);
        if (thisCourse == -1)
            cout << aID << " not found in current directory\n";
        else
        {
            cout << "\nEntry found: ";
            cout<< roster[thisCourse]; 
        }
    }
   
}

int course::searchByName(char* name) const //search roster by student name
{
    for (int i = 0; i < currentSize; i++) 
    {  
        if (roster[i].getName()==name) 
        {
            return i; 
        }
        
    }

    return -1; // Return -1 if never found.
}

int course::searchByID(int ID) const //search roster by student ID
{
    for (int i = 0; i < currentSize; i++)
    {   
        if (roster[i].getStudentID()==ID)
            return i; 
    }
    return -1; // Return -1 if never found.
}



void course::insertStudent(const student& student){ //adds student to roster
    if (currentSize==maxSize)
        grow(); 
    load(); 
        roster[currentSize++] = student; 
}

void course::removeStudent(){ 
    int choice;
    cout<<"How would you like to search to delete? 1. Name 2. ID"<<endl;
    cin>>choice;
    if(choice == 1){
        char aName[20];
        cout << "\tType the name to be removed: ";
        cin.getline(aName, 20);
        int thisCourse = searchByName(aName); 
        if (thisCourse == -1)
            cout << aName << " not found in current directory\n";
        else
        {
            cout << "\nEntry found: ";
            for (int i = thisCourse + 1; i < currentSize; i++){
                roster[i - 1] = roster[i];
                currentSize--;}
        }
    }
    else if(choice == 2){
        int aID;
        cout<<"Type the ID you'd like to seach for."<<endl;
        cin>>aID;
        int thisCourse = searchByID(aID);
        if (thisCourse == -1)
            cout << aID << " not found in current directory\n";
        else
        {
            cout << "\nEntry found: ";
            for (int i = thisCourse + 1; i < currentSize; i++){
                roster[i - 1] = roster[i];
                currentSize--;}
            
        }
    }
}


//START OF COURSE LIST CLASS
ostream& operator<< (ostream& c, const courseList& list){
    for (int i=0; i<list.currentSize; i++) {
        c<<list.list[i]; 
    } 
    return c; 
}

courseList::courseList(){
    maxSize = 2;
    currentSize = 0;
    list = new course[2];
}


void courseList::removeCourse() {
char CID [20];
cin.ignore(); 
cout<<"Type the number you'd like to remove: "<<endl;
cin.getline(CID,20); 
int thisCourse = searchByCourseNum(CID);
if (thisCourse == -1)
     cout << CID << " not found in current directory\n";
else
    {
    cout << "\nEntry found: ";
    for (int i = thisCourse + 1; i < currentSize; i++){
            list[i - 1] = list[i];
            currentSize--;
            cout<<list[i]; }
        }
    }


int courseList::searchByCourseName(char* courseName) const 
{
    for (int i = 0; i < currentSize; i++) 
    {   
        if (strcmp(list[i].getCourseName(), courseName) == 0)
            return i; 
    }
    return -1; 
}

int courseList::searchByCourseNum(char * courseCode) const 
{
    for (int i = 0; i < currentSize; i++) 
    {  
        if (strcmp(list[i].getCourseCode(), courseCode) == 0)
            return i; 
    }
    return -1; 
}

int courseList::searchByCourseLoc (char * courseLocation) const {
    bool foundLocation = false; 
    for ( int i=0; i<currentSize; i++) {
        if (strcmp(list[i].getLocation(), courseLocation)==0) {
            foundLocation = true; 
            cout<<"Course found: "<<endl; 
            cout<< list[i]; 
        }
    }
    if (foundLocation == false)
        return -1; 
    if (foundLocation == true)
        return 1; 
    return -1;
}

void courseList::addCourse() {
    if (currentSize==maxSize)
        grow(); 
    list[currentSize++].load(); 
}


void courseList::update(){
    cout<< "What course would you like to update? "<<endl; 
    char aName[20]; 
    cin.ignore(); 
    cin.getline(aName,20); 
    int thisAnswer= searchByCourseName(aName); 
    if (thisAnswer ==-1)
        cout<<aName<< "Course was not found:("<<endl; 
    else {
        cout<< "Your current course is : "<<endl; 
        cout<<list[thisAnswer]; 
        cout<< "Replace with new information "<<endl; 
        list[thisAnswer].load(); 
    }
}

void courseList::grow(){
    maxSize = maxSize + 1; 
    course* temp = new course [maxSize+1]; 
    for (int i = 0; i < maxSize-10; i++) 
        temp[i] = list[i]; 
    delete [] list; 
    list=temp; 
   
}

void courseList::lookupCourse(){ 
    int choice;
        cout<<"How would you like to search?  \n 1. Name  \n 2. ID  \n 3. Location"<<endl;
        cin>>choice;
        if(choice == 1){
            char aName[20];
            cout << "Type the name to be looked up: ";
            cin.ignore(); 
            cin.getline(aName, 20);
            int thisCourse = searchByCourseName(aName); 
        if (thisCourse == -1)
            cout << aName << " not found in current directory";
        else
        {
            cout << "Entry found: ";
            cout<<list[thisCourse]; 
        }
        }
        else if(choice == 2){
            char courseCode[20];
            cout<<"Type the ID you'd like to seach for."<<endl;
            cin.ignore(); 
            cin.getline(courseCode,20); 
            int thisCourse = searchByCourseNum(courseCode);
        if (thisCourse == -1)
            cout << courseCode << "not found in current directory\n";
        else
        {
            cout << "Entry found: ";
            cout<< list[thisCourse]; 
        }
    }
    else if(choice == 3){
            char location[20];
            cout<<"Type the location you'd like to seach for."<<endl;
            cin.ignore(); 
            cin.getline(location,20); 
            int thisCourse = searchByCourseLoc(location);
            if (thisCourse==-1) 
                cout<< location << "was not found in the directory"<<endl; 
    }
}

void courseList:: lookupStudent(){
    cout<<"Would you like to 1. search by name or 2. search by student ID: "<<endl; 
    int choice; 
    cin>>choice; 

    if (choice==1){
        char name[20]; 
        cout<< "Enter the students name "<<endl; 
        cin>>name; 
        cin.ignore(); 
        cin.getline(name,20); 
        int l= searchByName(name); 
        if (l==-1)
            cout<< "student name " << name << "could not be found " <<endl; 
        if (l!=-1)
            cout<< list[l]; 
    }

    else if (choice==2) {
        int ID; 
        cout<< "enter student ID: "; 
        cin>>ID; 

        int l = searchByID(ID); 
        if (l==-1)
            cout<< "student id " << ID << "could not be found "<<endl; 
        if (l !=-1)
            cout<< list[l]; 
    }



}
int courseList:: searchByName(char* name) {
    for(int i=0; i<currentSize; i++){
        int a= list[i].searchByName(name); 
    if (a!=-1) {
        cout<< "student found: "; 
        cout<< list[a]; 
        return 1; 
    }
}

return 0; 
}

int courseList:: searchByID (int AID) {
    for (int i=0; i<currentSize ; i++) {
        int l = list[i].searchByID(AID); 
    if (l!=-1) {
        cout<< "student was found: "; 
        cout<< list[l]; 
        return 1; 
    }
    }
    return 0; 
}

void courseList:: addStudent() {
    cout<< "which course would you like to add a student to? "<<endl; 
    char name[20]; 
    cin.ignore(); 
    cin.getline(name,20); 
    int z= searchByCourseName(name); 
    if(z == -1)
        return;
    student newStudent; 
    newStudent.load(); 
    list[z].addStudentsCourse(newStudent); 

}