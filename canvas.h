#include <iostream>
using namespace std; 

class student{ 
    friend ostream& operator<<(ostream& s,const student& student); 

    private:
        char *name; 
        int studentID; 
        char classification; 
        char *major;

    public:
        student(); 
        ~student(); 
        student(const char* _name, const char*_major, int _studentID, char _classification); 
        char *getName() const; 
        int getStudentID() const; 
        char getClassification() const; 
        char* getMajor() const; 
        void load();
        void setName (const char*); 
        void setMajor (const char *); 
        void setClassification (const char); 
        void setID (const int); 
        void operator=(const student& student); 
}; 

class course{
    friend ostream& operator<<(ostream& s,const course& course);

    private:
        char* courseName; 
        char courseCode[7]; 
        char location[10]; 
        student* roster; 
        int currentSize; 
        int maxSize; 
        void grow();

    public:
        course(); 
        course(const char* _courseName, char _courseCode[], char _location[]); 
        ~course(); 
        char *getCourseName() const; 
        const char *getCourseCode() const; 
        const char *getLocation() const; 
        student* getRoster(); 
        void addStudentsCourse(const student& student); 
        void lookup()const; 
        int findName(char* studentName, int studentID, char* aName) const; 
        int searchByName(char* name)const;
        int searchByID(int ID)const;
        void insertStudent(const student& student); 
        void removeStudent();  
        void load(); 
        void operator=(const course& course); 
        void setCourseName(const char* courseName); 
        void setCourseCode(const char* courseCode); 
        void setCourseLocation(const char* location); 
};

class courseList{
friend ostream& operator<< (ostream& c, const courseList& list); 
    public:
        courseList();
        ~courseList(){
            delete [] list;
        }

        void removeCourse();//remove course from course list
        void addCourse();//add course to course list
        //void show();
        void lookupCourse(); //searches a course
        int searchByCourseName(char* courseName)const;
        int searchByCourseNum(char *)const;  
        int searchByCourseLoc(char* courseLocation) const;  
        void update();
        void load(); 
        int searchByName(char*); //searches a name
        int searchByID(int);  //student ID
        void addStudent(); 
        void lookupStudent();  //searched a student
    private:
        void grow();
        int maxSize, currentSize;
        course * list;
};

