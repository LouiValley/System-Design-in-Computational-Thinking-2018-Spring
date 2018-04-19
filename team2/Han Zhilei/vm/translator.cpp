/*
    this is the vitual machine language translator for the implement of Hack Computer
    Arthor:HZL
*/
#include <iostream>
#include <cstring>
#include <string>

//#define SP 0
//#define LCL 1
//#define ARG 2
//#define POINTER 3
//#define 256 256
//#define HEAP 2048
//#define SCREEN 16384

//#define STATIC 16
//#define TEMP 5
static int LogicJumpLabelIndex=0;

enum commandtype
{
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
    C_IGNORE,
};

struct parsedcommand
{
    enum commandtype ctype;
    std::string command;
    std::string arg1;
    std::string arg2;
};

class Parser
{
    private:
        FILE* target;
        char buffer[2048];
        char arg1[100],arg2[100],command[100];
        char commentpart[100],commandpart[100];
        bool endoffile=false;
    public:
        //friend std::istream& operator>>(std::istream& in,Parser& dst);
        Parser(char* path);
        bool eof();
        void advance();
        void getc();
        enum commandtype ctype();
        std::string getcommand();
        std::string getarg1();
        std::string getarg2();
        struct parsedcommand getstruct();
};

Parser::Parser(char* path)
{
    target=fopen(path,"r");
}

bool Parser::eof()
{
    return feof(target);
}

void Parser::getc()
{
    fgetc(target);
}

void Parser::advance()
{
    strcpy(command,"");
    strcpy(commandpart,"");
    //strcpy(commentpart,"");
    strcpy(arg1,"");
    strcpy(arg2,"");
    strcpy(buffer,"");
    fgets(buffer,2048,target);
    sscanf(buffer,"%[^/]//%s",commandpart,commentpart);
    sscanf(commandpart,"%s %s %s",command,arg1,arg2);
}

bool checkarithemetic(char* command)
{
    std::string tmp(command);
    static std::string ari_operation[9]={"add","sub","neg","eq","gt","lt","and","or","not"};
    for(int i=0;i<9;i++)
    {
        if(ari_operation[i].compare(tmp)==0)
            return true;
    }
    return false;
}

commandtype Parser::ctype()
{
    if(strcmp(commandpart,"")==0)
    {
        return C_IGNORE;
    }
    else
    {
        if(checkarithemetic(command))
        {
            return C_ARITHMETIC;
        }
        if(strcmp(command,"push")==0)
        {
            return C_PUSH;
        }
        if(strcmp(command,"pop")==0)
        {
            return C_POP;
        }
        //TODO
        //more check and type
    }
}

std::string Parser::getcommand()
{
    std::string tmp(command);
    return tmp;
}

std::string Parser::getarg1()
{
    std::string tmp(arg1);
    return tmp;
}

std::string Parser::getarg2()
{
    std::string tmp(arg2);
    return tmp;
}

struct parsedcommand Parser::getstruct()
{
    struct parsedcommand s;
    s.ctype=ctype();
    s.arg1=getarg1();
    s.arg2=getarg2();
    s.command=getcommand();
    return s;
}

class Interpretor
{
    private:
        FILE* target;
        char tpath[200];
    public:
    void settarget( char* path);
    void write(struct parsedcommand);
    void writearithmetic(struct parsedcommand);
    void writepush(struct parsedcommand);
    void writepop(struct parsedcommand);
};

void Interpretor::settarget( char* path)
{
    if(target)
        fclose(target);
    strcpy(tpath,path);
    strcat(path,".asm");
    target=fopen(path,"w");
}

void Interpretor::write(struct parsedcommand command)
{
    switch(command.ctype)
    {
        case C_ARITHMETIC:
        {
            fprintf(target,"//C_ARITHEMETIC %s\n",command.command.c_str());
            writearithmetic(command);
            break;
        }
        case C_PUSH:
        {
            fprintf(target,"//C_PUSH %s %s %s\n",command.command.c_str(),command.arg1.c_str(),command.arg2.c_str());
            writepush(command);
            break;
        }
        case C_POP:
        {
            fprintf(target,"//C_POP %s %s %s\n",command.command.c_str(),command.arg1.c_str(),command.arg2.c_str());
            writepop(command);
            break;
        }
        default:
            break;
    }
}

void Interpretor::writearithmetic(struct parsedcommand command)
{
    if(command.command.compare("add")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=D+M\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
    if(command.command.compare("sub")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M-D\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
    if(command.command.compare("neg")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=-M\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
    if(command.command.compare("eq")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M-D\n");

        fprintf(target,"@LogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"D;JEQ\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=0\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@ENDOFLogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"0;JMP\n");

        fprintf(target,"(LogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=-1\n");
        fprintf(target,"D=A\n");

        fprintf(target,"(ENDOFLogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"D=D+1\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        LogicJumpLabelIndex++;
        return;
    }
    if(command.command.compare("gt")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M-D\n");

        fprintf(target,"@LogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"D;JGT\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=0\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@ENDOFLogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"0;JMP\n");

        fprintf(target,"(LogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=-1\n");
        fprintf(target,"D=A\n");

        fprintf(target,"(ENDOFLogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"D=D+1\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        LogicJumpLabelIndex++;
        return;
    }
    if(command.command.compare("lt")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M-D\n");

        fprintf(target,"@LogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"D;JLT\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=0\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@ENDOFLogicJumpLabelIndex%d\n",LogicJumpLabelIndex);
        fprintf(target,"0;JMP\n");

        fprintf(target,"(LogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"M=-1\n");
        fprintf(target,"D=A\n");

        fprintf(target,"(ENDOFLogicJumpLabelIndex%d)\n",LogicJumpLabelIndex);
        fprintf(target,"D=D+1\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        LogicJumpLabelIndex++;
        return;
    }
    if(command.command.compare("and")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M&D\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
    if(command.command.compare("or")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M|D\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
    if(command.command.compare("not")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");

        fprintf(target,"A=A-1\n");
        fprintf(target,"D=!M\n");
        fprintf(target,"M=D\n");
        fprintf(target,"A=A+1\n");

        fprintf(target,"D=A\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=D-A\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=D\n");
        return;
    }
}

void Interpretor::writepush(struct parsedcommand command)
{
    if(command.arg1.compare("constant")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=A\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");
        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("local")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@LCL\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("argument")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@ARG\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("this")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@THIS\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("that")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@THAT\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("temp")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@5\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("pointer")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@3\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"A=D+A\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
        return;
    }
    if(command.arg1.compare("static")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"D=A+D\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@%s.%s\n",tpath,command.arg2.c_str());
        fprintf(target,"D=M\n");

        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M+1\n");
    }
    //TODO
    //more kinds of segment
}

void Interpretor::writepop(struct parsedcommand command)
{
    if(command.arg1.compare("local")==0)
    {
        fprintf(target,"@LCL\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("argument")==0)
    {
        fprintf(target,"@ARG\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("this")==0)
    {
        fprintf(target,"@THIS\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("that")==0)
    {
        fprintf(target,"@THAT\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("temp")==0)
    {
        fprintf(target,"@5\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("pointer")==0)
    {
        fprintf(target,"@3\n");
        fprintf(target,"D=A\n");
        fprintf(target,"@%s\n",command.arg2.c_str());
        fprintf(target,"D=D+A\n");
        fprintf(target,"@13\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@13\n");
        fprintf(target,"A=M\n");
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
        return;
    }
    if(command.arg1.compare("static")==0)
    {
        fprintf(target,"@SP\n");
        fprintf(target,"D=M\n");
        fprintf(target,"@256\n");
        fprintf(target,"A=A+D\n");
        fprintf(target,"A=A-1\n");
        fprintf(target,"D=M\n");

        fprintf(target,"@%s.%s\n",tpath,command.arg2.c_str());
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
    }
}

int main(int argc,char* argv[])
{
    Interpretor* interpretor=new Interpretor;
    Parser** parser=new Parser*[argc-1];
    char buffer[200];
    for(int i=0;i<argc-1;i++)
    {
        if(strstr(argv[i+1],".vm"))
        {
            parser[i]=new Parser(argv[i+1]);
            sscanf(argv[i+1],"%[^.].vm",buffer);
            interpretor->settarget(buffer);
            while(!parser[i]->eof())
            {
                parser[i]->advance();
                interpretor->write(parser[i]->getstruct());
            }
        }
        else
        {
            std::cout<<"error:pls pass vm files"<<std::endl;
            return 1;
        }
    }
    //for(int i=0;i<argc-1;i++)
    //{

    //}
    return 0;
}
