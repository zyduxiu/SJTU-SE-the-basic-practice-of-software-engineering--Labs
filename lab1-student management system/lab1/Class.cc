#include "Class.h"
#include <string>
#include "Student.h"
void Class::addStudent(Student &st)
{
    StudentWrapper s(st.id,st);
    students.push_back(s);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!";
}

double Class::getAvgScore()
{
    int i=0;
    double sum=0;
    for(std::vector<StudentWrapper>::iterator it=students.begin();
        it != students.end();
        ++it){
        sum+=it->getScore();
        i+=1;
    }
    return (sum/i);
}
