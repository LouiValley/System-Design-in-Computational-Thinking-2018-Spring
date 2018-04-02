//
//  main.cpp
//  Assembler
//
//  Created by NaXin on 2018/4/1.
//  Copyright © 2018年 NaXin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <list>
#include <bitset>
#include "parser.h"
#include "Process.h"

using namespace std;

int main(int argc, const char * argv[]) {
    //preprocess
    int ROM_cnt = 0;
    int RAM_cnt = 16;
    map<string, int> sym_tab;
    list<string> instrs;
    pre_tab(sym_tab);
    
    //input file name and open.
    string in_name;
    cout << "asm file name(without the .asm part):" << endl;
    cin >> in_name;
    ifstream infile;
    infile.open(in_name+".asm");
    
    //input outfile name and open
    string out_name;
    cout << "out file name(without the .hack part):" << endl;
    cin >> out_name;
    ofstream outfile;
    outfile.open(out_name+".hack");
    
    //read file and process1
    while (!infile.eof()) {
        string temp;
        getline(infile,temp);
        
        //0=null,1=A,2=C,3=L
        Parser par(temp);
        if (par.get_type() == 0)
            continue;
        else if (par.get_type() == 3)
            sym_tab.insert(pair<string,int>(par.get_symbol(),ROM_cnt));
        else {
            instrs.push_back(temp);
            ROM_cnt++;
        }
    }
    
    //process2
    for (auto p = instrs.begin(); p != instrs.end(); p++)
    {
        Parser par(*p);
        if (par.get_type() == 1){
            //*p is a A instruction
            
            outfile << "0";
            string sy = par.get_symbol();
            
            if (regex_match(sy, regex("[0-9]+"))){
                //sy is a number
                int num;
                stringstream ss;
                ss << sy;
                ss >> num;
                outfile << bitset<15>(num) << endl;
            }
            else {
                //sy is a symbol
                if (sym_tab.count(sy) == 0){
                    //a new symbol
                    sym_tab.insert(pair<string, int>(sy,RAM_cnt));
                    outfile << bitset<15>(RAM_cnt) << endl;
                    RAM_cnt++;
                }
                //a old symbol
                else outfile << bitset<15>(sym_tab[sy]) << endl;
            }
            
        }
        else {
            //*p is a C instruction
            
            outfile << "111";
            string dest = par.get_dest();
            string comp = par.get_comp();
            string jump = par.get_jump();
            
            outfile << comp_match(comp);
            outfile << dest_match(dest);
            outfile << jump_match(jump);
            outfile << endl;
        }
    }
    
    return 0;
}
