/*
    this is the vitual machine language translator for the implement of Hack Computer
    Arthor:HZL
*/
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

#define FILENAME "main.asm"
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
        //bool endoffile=false;
    public:
        //friend std::istream& operator>>(std::istream& in,Parser& dst);
        Parser(char* path);
        bool eof();
        void advance();
        //void getc();
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

//void Parser::getc()
//{
    //fgetc(target);
//}

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
    if(strcmp(command,"")==0)
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
        if(strcmp(command,"label")==0)
        {
            return C_LABEL;
        }
        if(strcmp(command,"goto")==0)
        {
            return C_GOTO;
        }
        if(strcmp(command,"if-goto")==0)
        {
            return C_IF;
        }
        if(strcmp(command,"function")==0)
        {
            return C_FUNCTION;
        }
        if(strcmp(command,"call")==0)
        {
            return C_CALL;
        }
        if(strcmp(command,"return")==0)
        {
            return C_RETURN;
        }
    }
        printf("error:wrong command %s\n",command);
        exit(1);
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
        std::string currentfile;
        std::string currentfunction;
    public:
        void settarget(std::string path);
        void setfunction(std::string targetfunction);
        void setcurrentfile(char* path);
        void write(struct parsedcommand);
        void writeinit();
        void writearithmetic(struct parsedcommand);
        void writepush(struct parsedcommand);
        void writepop(struct parsedcommand);
        void writelabel(struct parsedcommand);
        void writegoto(struct parsedcommand);
        void writeifgoto(struct parsedcommand);
        void writefunction(struct parsedcommand);
        void writecall(struct parsedcommand);
        void writereturn(struct parsedcommand);
};

void Interpretor::settarget(std::string path)
{
    if(target)
        fclose(target);
    target=fopen(path.c_str(),"w");
}

void Interpretor::setcurrentfile(char* path)
{
    currentfile=path;
}

void Interpretor::setfunction(std::string targetfunction)
{
    currentfunction=targetfunction;
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
        case C_LABEL:
        {
            fprintf(target,"//C_LABEL %s %s\n",command.command.c_str(),command.arg1.c_str());
            writelabel(command);
            break;
        }
        case C_GOTO:
        {
            fprintf(target,"//C_GOTO %s %s\n",command.command.c_str(),command.arg1.c_str());
            writegoto(command);
            break;
        }
        case C_IF:
        {
            fprintf(target,"//C_IF %s %s\n",command.command.c_str(),command.arg1.c_str());
            writeifgoto(command);
            break;
        }
        case C_CALL:
        {
            fprintf(target,"//C_CALL %s %s\n",command.command.c_str(),command.arg1.c_str());
            writecall(command);
            break;
        }
        case C_FUNCTION:
        {
            fprintf(target,"//C_FUNCTION %s %s\n",command.command.c_str(),command.arg1.c_str());
            writefunction(command);
            break;
        }
        case C_RETURN:
        {
            fprintf(target,"//C_RETURN %s %s\n",command.command.c_str(),command.arg1.c_str());
            writereturn(command);
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

        fprintf(target,"@%s.%s\n",currentfile.c_str(),command.arg2.c_str());
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

        fprintf(target,"@%s.%s\n",currentfile.c_str(),command.arg2.c_str());
        fprintf(target,"M=D\n");

        fprintf(target,"@SP\n");
        fprintf(target,"M=M-1\n");
    }
}

void Interpretor::writelabel(struct parsedcommand command)
{
    fprintf(target,"(%s$%s)\n",currentfunction.c_str(),command.arg1.c_str());
}

void Interpretor::writegoto(struct parsedcommand command)
{
    fprintf(target,"@%s$%s\n",currentfunction.c_str(),command.arg1.c_str());
    fprintf(target,"0;JMP\n");
}

void Interpretor::writeifgoto(struct parsedcommand command)
{
    fprintf(target,"@SP\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"A=A+D\n");
    fprintf(target,"A=A-1\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@%s$%s\n",currentfunction.c_str(),command.arg1.c_str());
    fprintf(target,"D;JNE\n");
}

void Interpretor::writefunction(struct parsedcommand command)
{
    int local_number=std::stoi(command.arg2);
    fprintf(target,"(%s)\n",command.arg1.c_str());
    for(int i=0;i<local_number;i++)
    {
        writepush({C_PUSH,"push","constant","0"});
    }
}

void Interpretor::writecall(struct parsedcommand command)
{
    currentfunction=command.arg1;
    //push return addr,manually
    fprintf(target,"@SP\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@13\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@%s&returnaddr\n",command.arg1.c_str());
    fprintf(target,"D=A\n");
    fprintf(target,"@13\n");
    fprintf(target,"A=M\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=M+1\n");
    //push LCL value
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@13\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@LCL\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@13\n");
    fprintf(target,"A=M\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=M+1\n");
    //push ARG
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@13\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@ARG\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@13\n");
    fprintf(target,"A=M\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=M+1\n");
    //THIS
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@13\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@THIS\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@13\n");
    fprintf(target,"A=M\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=M+1\n");
    //THAT
    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@13\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@THAT\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@13\n");
    fprintf(target,"A=M\n");
    fprintf(target,"M=D\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=M+1\n");

    fprintf(target,"D=M\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=A+D\n");
    fprintf(target,"@LCL\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@%d\n",std::stoi(command.arg2));
    fprintf(target,"D=D-A\n");
    fprintf(target,"@5\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"@ARG\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@%s\n",command.arg1.c_str());
    fprintf(target,"0;JMP\n");

    fprintf(target,"(%s&returnaddr)\n",command.arg1.c_str());
}

void Interpretor::writereturn(struct parsedcommand command)
{
    //frame<=LCL
    fprintf(target,"@LCL\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@14\n");
    fprintf(target,"M=D\n");

    //return type put in arg 0
    writepop({C_POP,"pop","argument","0"});

    //SP+256<=ARG+1
    fprintf(target,"@ARG\n");
    fprintf(target,"D=M\n");
    fprintf(target,"D=D+1\n");
    fprintf(target,"@256\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"@SP\n");
    fprintf(target,"M=D\n");

    //THAT=frame-1
    fprintf(target,"@14\n");
    fprintf(target,"D=M\n");
    fprintf(target,"D=D-1\n");
    fprintf(target,"A=D\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@THAT\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@14\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@2\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"A=D\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@THIS\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@14\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@3\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"A=D\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@ARG\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@14\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@4\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"A=D\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@LCL\n");
    fprintf(target,"M=D\n");

    fprintf(target,"@14\n");
    fprintf(target,"D=M\n");
    fprintf(target,"@5\n");
    fprintf(target,"D=D-A\n");
    fprintf(target,"A=D\n");
    fprintf(target,"A=M\n");
    fprintf(target,"0;JMP\n");
}

void Interpretor::writeinit()
{
    fprintf(target,"@SP\n");
    fprintf(target,"M=0\n");
    struct parsedcommand tmp;
    tmp.ctype=C_CALL;
    tmp.command="call";
    tmp.arg1="Sys.init";
    tmp.arg2="0";
    writecall(tmp);
}

int main(int argc,char* argv[])
{
    //TODO
    //the interpretor should only produce one asm file
    //DONE
    Interpretor* interpretor=new Interpretor;
    Parser** parser=new Parser*[argc-1];
    interpretor->settarget(FILENAME);
    interpretor->writeinit();
    char buffer[200];
    for(int i=0;i<argc-1;i++)
    {
        if(strstr(argv[i+1],".vm"))
        {
            parser[i]=new Parser(argv[i+1]);
            sscanf(argv[i+1],"%[^.].vm",buffer);
            interpretor->setcurrentfile(buffer);
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
