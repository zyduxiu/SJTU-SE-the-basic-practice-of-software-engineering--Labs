#ifndef COMMAND_H
#define COMMAND_H


class command
{
private:
    int commandtype;
    int towhichline;
public:
    command();
    int returntype(){
        return commandtype;
    }
    int returnwhichline(){
        return towhichline;
    }
    void getcommandtype(int a){
        commandtype=a;
    }
   // void gettowhichline(int a){

   // }
};

#endif // COMMAND_H
