#include <iostream>
#include <sstream>
#include "Editor.h"
#include <string>
using namespace std;
class fileerr{
private:
public:
    const string what() const{return "Filename not specified";}
};
class delete_of_range_{
private:
public:
    const string what() const{return "Delete range error";}
};
class out_of_range_{
private:
public:
    const string what() const{return "Line number out of range";}
};
class range_error_{private:
public:
    const string what() const{return "Number range error";}
};
const out_of_range_ oor;
const range_error_ re;
const delete_of_range_ dre;
const fileerr fileerror;
Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    buffer->~Buffer();
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range_ &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error_ &re) {
            cout << "? " << re.what() << endl;
        } catch(const delete_of_range_ &dre){
            cout << "? " << dre.what() << endl;
        } catch(const fileerr &fileerror){
            cout<<"?"<<fileerror.what()<<endl;
        }
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    while (true)
    {   string text;
        getline(cin, text);
        if (text == ".")
            break;
        buffer->appendLine(text);
        currentline++;
        }
}

void Editor::cmdInsert() {
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    {
        string text;
        while(true){
            getline(cin, text);
            if (text == ".")
                break;
                buffer->insertLine(text);
            currentline++;
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
    currentline-=end-start+1;
}

void Editor::cmdNull(int line)
{
    cout << buffer->moveToLine(line) << endl;
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        string buf;
        for(int i=0;(cmd[i]);i++){
            buf[i]=cmd[2+i];
        }
        if(!buf[0]){throw fileerror;}
        else{cmdWrite(buf);}
        // TODO: call cmdWrite with proper arguments
        return;
    }
    // TODO: handle special case "1,$n".
    int start;
    char end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()) {
        if(start<0||start>currentline){throw oor;}
        cmdNull((start));
        return;
    }
    ss >> comma >> end >> type;
    if (ss.good()) {
        if (type == 'n') {
            if(end=='$'){
                if((start<0)){throw oor;}
                else{cmdNumber((start),currentline);}
            }
            else {
                if ((start) < 0 || (end - '0') > currentline) { throw oor; }
                if ((start) >= (end - '0')) { throw re; }
                cmdNumber((start), (end - '0'));
                return;
            }
        } else if (type == 'd') {
            if(end=='$'){
                if((start<0)){throw oor;}
                else{cmdDelete((start),currentline);}
            }
            if((start)<0||(end-'0')>currentline){throw oor;}
            if((start)>=(end-'0')){throw dre;}
            cmdDelete((start), (end-'0'));}
            return;
        }
    throw "Bad/Unknown command";
}
