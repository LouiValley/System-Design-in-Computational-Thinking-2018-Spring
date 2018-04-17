//
//  Process.h
//  Assembler
//
//  Created by NaXin on 2018/4/2.
//  Copyright © 2018年 NaXin. All rights reserved.
//

#ifndef Process_h
#define Process_h
#include <map>
#include <string>

using namespace std;

void pre_tab(map<string, int> &tab)
{
    tab.insert(pair<string, int>("SP",0));
    tab.insert(pair<string, int>("LCL",1));
    tab.insert(pair<string, int>("ARG",2));
    tab.insert(pair<string, int>("THIS",3));
    tab.insert(pair<string, int>("THAT",4));
    tab.insert(pair<string, int>("R0",0));
    tab.insert(pair<string, int>("R1",1));
    tab.insert(pair<string, int>("R2",2));
    tab.insert(pair<string, int>("R3",3));
    tab.insert(pair<string, int>("R4",4));
    tab.insert(pair<string, int>("R5",5));
    tab.insert(pair<string, int>("R6",6));
    tab.insert(pair<string, int>("R7",7));
    tab.insert(pair<string, int>("R8",8));
    tab.insert(pair<string, int>("R9",9));
    tab.insert(pair<string, int>("R10",10));
    tab.insert(pair<string, int>("R11",11));
    tab.insert(pair<string, int>("R12",12));
    tab.insert(pair<string, int>("R13",13));
    tab.insert(pair<string, int>("R14",14));
    tab.insert(pair<string, int>("R15",15));
    tab.insert(pair<string, int>("SCREEN",16384));
    tab.insert(pair<string, int>("KBD",24576));
    
    return;
}

string comp_match(string comp)
{
    if (comp == "0")
        return "0101010";
    else if (comp == "1")
        return "0111111";
    else if (comp == "-1")
        return "0111010";
    else if (comp == "D")
        return "0001100";
    else if (comp == "A")
        return "0110000";
    else if (comp == "!D")
        return "0001101";
    else if (comp == "!A")
        return "0110001";
    else if (comp == "-D")
        return "0001111";
    else if (comp == "-A")
        return "0110011";
    else if (comp == "D+1")
        return "0011111";
    else if (comp == "A+1")
        return "0110111";
    else if (comp == "D-1")
        return "0001110";
    else if (comp == "A-1")
        return "0110010";
    else if (comp == "D+A" || comp == "A+D")
        return "0000010";
    else if (comp == "D-A")
        return "0010011";
    else if (comp == "A-D")
        return "0000111";
    else if (comp == "D&A")
        return "0000000";
    else if (comp == "D|A")
        return "0010101";
    
    else if (comp == "M")
        return "1110000";
    else if (comp == "!M")
        return "1110001";
    else if (comp == "-M")
        return "1110011";
    else if (comp == "M+1")
        return "1110111";
    else if (comp == "M-1")
        return "1110010";
    else if (comp == "D+M" || comp == "M+D")
        return "1000010";
    else if (comp == "D-M")
        return "1010011";
    else if (comp == "M-D")
        return "1000111";
    else if (comp == "D&M")
        return "1000000";
    else if (comp == "D|M")
        return "1010101";
    
    else throw runtime_error("expersion invalid.");
}

string dest_match(string dest)
{
    if (dest.empty())
        return "000";
    else if (dest == "M")
        return "001";
    else if (dest == "D")
        return "010";
    else if (dest == "MD")
        return "011";
    else if (dest == "A")
        return "100";
    else if (dest == "AM")
        return "101";
    else if (dest == "AD")
        return "110";
    else if (dest == "AMD")
        return "111";
    else throw runtime_error("invalid dest.");
}

string jump_match(string jump)
{
    if (jump.empty())
        return "000";
    else if (jump == "JGT")
        return "001";
    else if (jump == "JEQ")
        return "010";
    else if (jump == "JGE")
        return "011";
    else if (jump == "JLT")
        return "100";
    else if (jump == "JNE")
        return "101";
    else if (jump == "JLE")
        return "110";
    else if (jump == "JMP")
        return "111";
    else throw runtime_error("invalid jump.");
}

#endif /* Process_h */
