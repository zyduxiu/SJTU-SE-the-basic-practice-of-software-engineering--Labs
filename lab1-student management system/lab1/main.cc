#include <vector>
#include <iostream>
#include <fstream>
#include "Class.h"
#include "Student.h"
#include <iomanip>
using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();


public:
    AppX();
    ~AppX();
    int run();
};
AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (vector<Student *>::iterator it = studentVec.begin();
         it != studentVec.end();
         ++it) {
        if (*it) delete (*it);
    }
}
AppX::AppX()
{
    loadFiles();
}
void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st=NULL;
    Class *sw=NULL;
    string clsname;
    int point;
    ifstream stfile("../Students.txt");
    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;
        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';',pos1+1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            }
            else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }
        if (bufv[3] == "U")
        {st = new Undergraduate(bufv[0], bufv[1], bufv[2]);}
        else
        {st = new Graduate(bufv[0], bufv[1], bufv[2]);}
        studentVec.push_back(st);
    }
    stfile.close();
    ifstream otfile("../Classes.txt");
    while(getline(otfile, line)){
        if(line.empty())continue;
        if(line[0]=='#')continue;
        if(line.find(':')!=-1&&line[0]=='C') {
            pos2 = line.find(':');
            clsname = line.substr(pos2+1 , string::npos);
        }
        if(line.find(':')!=-1&&line[0]=='P') {
            pos2 = line.find(':');
            point = stoi(line.substr(pos2 + 1, string::npos).c_str());
            sw = new Class(clsname, point);
            classVec.push_back(sw);
        }
        if(line.find(':')==-1){
            for(int j=0;j<studentVec.size();j++){
                if(studentVec[j]->id==line){
                    sw->addStudent(*studentVec[j]);
                    studentVec[j]->addClass(sw);
                }
            }
        }
    }
    otfile.close();
}
// TODO: load data from ./Classes.txt and push objects to the vector.
// Hint: how is student information read?
void AppX::inputScore() {
    while (true) {
        bool flag1 = false;
        Class *classthis = NULL;
        string coursename;
        cout<<"Please input the class name (or input q to quit):"<<endl;
        cin >> coursename;
        if (coursename == "q") break;
        for (int i = 0; i < classVec.size(); i++) {
            if (classVec[i]->name == coursename) {
                flag1 = true;
                classthis = classVec[i];
            }
        }
        if (!flag1) { cout << "Wrong class!"<<endl; }
        else {
            while (true) {
                cout << "Please input the student id (or input q to quit):"<<endl;
                string studentid;
                Student *studentthis;
                bool flag2 = false;
                cin >> studentid;
                if (studentid[0] == 'q')break;
                for (int i = 0; i < studentVec.size(); i++) {
                    if (studentVec[i]->id== studentid) {
                        studentthis = studentVec[i];
                        flag2 = true;
                    }
                }
                if (!flag2) { cout << "Wrong student!"<<endl; }
                else {
                    cout << "please input the score:"<<endl;
                    try{studentthis->toString();
                        string score;
                        cin >> score;
                        classthis->getStudentWrapper(studentid).setScore(stoi(score.c_str()));}
                    catch(const char *a){cout<<"Wrong score!"<<endl;}
                }
            }
        }
    }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;
    while (true) {
        cout <<"Please input the class name (or input q to quit): "<<endl;
        cin >> sbuf;
        if (sbuf == "q")
            break;
        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }
        avg = cl->getAvgScore();
        cout <<"The average score is: " <<setiosflags(ios::fixed) << setprecision(2)<< avg << endl;
    }
}
void AppX::printGpa()
{
    bool flag=false;
    std::string id;
    while(true){
        cout<<"Please input the student id(or input q to quit):"<<endl;
        cin>>id;
        if(id=="q"){break;}
        for(vector<Student *>::iterator it = studentVec.begin();
            it != studentVec.end();
            ++it){
            if((*it)->id==id){
                cout<< setiosflags(ios::fixed) << setprecision(2)<<(*it)->getGrade()<<endl;
                flag=true;
            }
        }
        if(!flag){cout<<"No match student!"<<endl;}
    }
}
int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
             << "\ti: Input score\n"
             << "\ta: Compute average score of a class\n"
             << "\tg: Compute grade of a student\n"
             << "\tq: Quit\n"
             << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}
int main()
{
    AppX app;
    return app.run();
}
