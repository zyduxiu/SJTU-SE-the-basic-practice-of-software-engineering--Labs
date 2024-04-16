#ifndef COMMAND_H
#define COMMAND_H


class command
{
private:
    int commandtype;//操作类型
    int towhichline;//下一个line
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
