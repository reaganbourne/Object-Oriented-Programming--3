#include <iostream>
#include <cstring>
#include "canvas.h"
using namespace std; 

int main(){
    student student; 
    course course;
    courseList courseList;

    char choice; // menu command entered by user
    cout<< "1-add course, 2-add student, 3-update a course, 4-list courses, 5-search student, 6-search course, 7-remove a course, 8-terminates program"<<endl; 
    cin>>choice; 
do
{
    switch (choice)
        {
            case '1': courseList.addCourse(); break;
            case '2': courseList.addStudent(); break; 
            case '3': courseList.update(); break; 
            case '4': cout << courseList; break;
            case '5': courseList.lookupStudent(); break;
            case '6': courseList.lookupCourse(); break;
            case '7': courseList.removeCourse(); break; 
            case '8': break; 
        }
    cout<< "1-add course, 2-add student, 3-update a course, 4-list courses, 5-search student, 6-search course, 7-remove a course, 8-terminates program"<<endl; 
    cin>>choice; 
} 
while (choice != '8');
    return 0;

    
    
}
