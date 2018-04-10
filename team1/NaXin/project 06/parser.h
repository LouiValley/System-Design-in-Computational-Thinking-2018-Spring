//
//  parser.h
//  Assembler
//
//  Created by NaXin on 2018/4/2.
//  Copyright © 2018年 NaXin. All rights reserved.
//

#ifndef parser_h
#define parser_h
#include <string>
#include <regex>
using namespace std;

class Parser {
private:
    int cmd_type;//0=null,1=A,2=C,3=L
    string cmd;
    string symbol;
    string dest;
    string comp;
    string jump;
    
private:
    void put_type(){
        if (cmd.empty())
            cmd_type = 0;
        else if (regex_match(cmd, regex("//.*")))
            cmd_type = 0;
        else if (regex_match(cmd, regex("@.*")))
            cmd_type = 1;
        else if (regex_match(cmd, regex("\\(.*\\)")))
            cmd_type = 3;
        else {
            cmd_type = 2;
            if (cmd.find("//") != string::npos){
                cmd = cmd.substr(0,cmd.find("//"));
            }
        }
        return;
    }
    
    
    void put_sym(){
        if (cmd_type == 0 || cmd_type == 2) return;
        if (cmd_type == 1)
            symbol = cmd.substr(1);
        else symbol = cmd.substr(1,cmd.size()-2);
        return;
    }
    
    void put_rest(){
        if (cmd_type != 2) return;
        
        long long eq_pos = cmd.find('=');
        long long semi_pos = cmd.find(';');
        long long comp_st = 0;
        long long comp_len = cmd.size();
        
        if (eq_pos != string::npos){
            //there is a dest
            dest = cmd.substr(0,eq_pos);
            comp_st = eq_pos+1;
        }
        if (semi_pos != string::npos){
            //there is a jump
            jump = cmd.substr(semi_pos+1);
            comp_len = semi_pos - comp_st;
        }
        
        comp = cmd.substr(comp_st, comp_len);
        return;
    }
    
public:
    Parser(string a){
        for (int i = 0; i < a.size(); i++)
            if (a[i] != ' ' && a[i] != '\n' && a[i] != '\r') cmd.push_back(a[i]);
        put_type();
        put_sym();
        put_rest();
    }
    ~Parser(){}
    
    int get_type(){ return cmd_type; }
    string get_symbol(){ return symbol; }
    string get_dest(){ return dest; }
    string get_comp(){ return comp; }
    string get_jump(){ return jump; }
};


#endif /* parser_h */
