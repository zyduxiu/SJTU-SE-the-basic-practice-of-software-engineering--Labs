#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

void Student::toString() const
{
    std::ostringstream oss;
    oss << "Student Information:";
    oss << "\n\tid: " << id;
    oss << "\n\tname: " << name;
    oss << "\n\tenrollment year: " << year;
    oss << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate");
    oss << std::endl;
}
double Undergraduate:: getGrade() {
    int pointsum = 0;
    double scoresum = 0.0;
    for (int i=0;i<classes.size();i++) {
        pointsum += classes[i]->point;
        scoresum += ((classes[i]->getStudentWrapper(id).getScore())*classes[i]->point)/20;
        //这一步比较复杂，首先调用student类内部的vector类型的classes，指向class类里的getStudentwrapper函数，得到studentwrapper类里面的score值。
    }
    return (scoresum/pointsum);
}
double Graduate:: getGrade(){
    double pointsum = 0;
    double scoresum = 0.0;
    for (int i=0;i<classes.size();i++) {
        pointsum += classes[i]->point;
        if(classes[i]->getStudentWrapper(id).getScore()<=100&&classes[i]->getStudentWrapper(id).getScore()>=90){scoresum+=4.0*classes[i]->point;}
        if(classes[i]->getStudentWrapper(id).getScore()<=89&&classes[i]->getStudentWrapper(id).getScore()>=80){scoresum+=3.5*classes[i]->point;}
        if(classes[i]->getStudentWrapper(id).getScore()<=79&&classes[i]->getStudentWrapper(id).getScore()>=70){scoresum+=3.0*classes[i]->point;}
        if(classes[i]->getStudentWrapper(id).getScore()<=69&&classes[i]->getStudentWrapper(id).getScore()>=60){scoresum+=2.5*classes[i]->point;}
        if(classes[i]->getStudentWrapper(id).getScore()<60){scoresum+=2.0*classes[i]->point;}
    }
    pointsum=scoresum/pointsum;
    return (pointsum);
}

void Student::addClass(Class* c){
    classes.push_back(c);
}


// TODO: implement functions which are declared in Student.h.
