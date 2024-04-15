#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>

class Class;
enum Degree {
    undergraduate,
    graduate
};
class Student {
    // TODO: implement class Student.
private:
protected:
    std::string name;//course name
    std::string year;//学历

public:
    enum Degree degree;
    std::vector<Class *> classes;
    std::string id;//学号
    void toString() const;

    virtual double getGrade() = 0;

    void addClass(Class *c) ;
    Student(std::string a,std::string b,std::string c){id = a;name = b;year = c;};
    ~Student(){};
};
class Undergraduate:public Student{
public:
    double getGrade();
    Undergraduate(std::string a,std::string b,std::string c):Student(a,b,c){};
    ~Undergraduate(){};
};
// TODO: implement class Graduate.
class Graduate:public Student{
public:
    double getGrade();
    Graduate(std::string a,std::string b,std::string c):Student(a,b,c){};
    ~Graduate(){};
};
// TODO: implement class Undergraduate.

class StudentWrapper {
private:
    const Student &student;
    double score=0.0;
public:
    std::string id;
    // TODO: fix error
    StudentWrapper(std::string x,const Student &a):id(x),student(a){};
    void setScore(int score)
    {
        if (score < 0 || score > 100)
            throw "Invalid score";
        else{this->score = score;}
    }

    double getScore() const
    {return this->score;}

};

#endif // STUDENT_H_
