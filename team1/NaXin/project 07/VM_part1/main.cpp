//
//  main.cpp
//  VM
//
//  Created by NaXin on 2018/4/9.
//  Copyright © 2018年 NaXin. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
#include <list>
#include <map>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]) {
	string vmFileName;
	string asmFileName;
	cout << "vm file name(without .vm)" << endl;
	cin >> vmFileName;
	cout << "asm file name(without .asm)" << endl;
	cin >> asmFileName;
	
	//open file
	ifstream vmFile;
	vmFile.open("inputVm/" + vmFileName + ".vm");
	ofstream asmFile;
	asmFile.open("outputAsm/" + asmFileName + ".asm");
		
	//variable
	Parser par;
	list<Triad> tris;
	
	//read commamds and process 1
	cout << "reading" << endl;
	while(!vmFile.eof()){
	    string temp;
	    getline(vmFile, temp);
	    par.removeComment(temp);
	    if (!temp.empty()){
			tris.push_back(par.readCommand(temp));
	    }
	}

	//process 2
	cout << "putting push and pop" << endl;
	for_each(tris.begin(), tris.end(), [](Triad &cmd) {
		if (cmd.fir == "push" || cmd.fir == "pop")
			cmd.fir = cmd.fir + "_" + cmd.sec;
	});

	int jumpNum = 0;
	for_each(tris.begin(), tris.end(), [&](Triad &cmd) {
		ifstream repTable;
		repTable.open("table/replaceTable.txt");
		Triad tr;
		while (!repTable.eof()) {
			string line;
			getline(repTable, line);
			tr = par.readCommand(line);
			if (tr.fir == cmd.fir) break;
		}
		if (tr.fir != cmd.fir) throw runtime_error("table not correct!");

		ifstream tem;
		tem.open("templates/" + tr.sec + ".txt");
		
		while (!tem.eof()) {
			string temp;
			getline(tem, temp);

			for (long long i = 0; i < temp.size(); i++){
				if (temp[i] == '^') {
					i++;
					while (i < temp.size() && temp[i] != '$') {
						switch (temp[i]) {
						case '+': asmFile << getNum(tr.thr) + getNum(cmd.thr); break;
						case '<': asmFile << cmd.sec; break;
						case '>': asmFile << cmd.thr; break;
						case '?': asmFile << jumpNum/4; jumpNum++; break;
						case '~': asmFile << asmFileName; break;
						case '#': asmFile << tr.thr; break;
						default:throw runtime_error("no such char"); break;
						}
						i++;
					}
				}
				else asmFile << temp[i];
			}
			asmFile << endl;
		}
	});
	//begin
	/*for_each(cmds.begin(), cmds.end(), [&](command &cmd) {
		auto s = cmdTab[cmd.type];
		string tem = tems[s.templateName];
		for (long long i = 0; i < tem.size(); i++) {
			if (tem[i] == '~')
				asmFile << s.replacement;
			else if (tem[i] == '?')
				asmFile << i;
			else if (tem[i] == '#') {
				i++;
				if (tem[i] == '1')
					asmFile << cmd.argu1;
				else if (tem[i] == '2')
					;
				else if (tem[i] == '3') {
					int a;
					stringstream stream(cmd.argu1);
					stream >> a;
					i++;
					if (tem[i] == '$')
				}
			}
			else cout << tem[i];
		}
	});*/

	/*for_each(cmds.begin(), cmds.end(), [](command &cmd) {
		cout << endl << cmd.type << endl << cmd.arguNum << endl << cmd.argu1 << cmd.argu2 << endl;
	});*/
	/*    string a;
	getline(cin, a);
	parser par;
	par.readcommand(a);
	cout << a << endl;
	cout << par.type << endl << par.cmd << endl << par.arg1 << endl << par.arg2 << endl << endl;*/

	return 0;
}