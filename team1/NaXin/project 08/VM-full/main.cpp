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
int jumpNum = 0;

void writeFile(list<Triad> &tris, Parser &par, ofstream &asmFile, string vmFileName)
{
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

			for (long long i = 0; i < temp.size(); i++) {
				if (temp[i] == '^') {
					i++;
					while (i < temp.size() && temp[i] != '$') {
						switch (temp[i]) {
						case '+': asmFile << getNum(tr.thr) + getNum(cmd.thr); break;
						case '<': asmFile << cmd.sec; break;
						case '>': asmFile << cmd.thr; break;
						case '?': asmFile << jumpNum; break;
						case '~': asmFile << vmFileName; break;
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

		jumpNum++;
	});
}

int main(int argc, const char * argv[]) {
	int fileNum;
	bool needLink = false;
	list<string> vmFileNames;
	string asmFileName;
	
	cout << "input file number" << endl;
	cin >> fileNum;
	if (fileNum > 1) needLink = true;
	for (int i = 0; i < fileNum; i++) {
		string name;
		cout << "vm file name(without .vm)" << endl;
		cin >> name;
		vmFileNames.push_back(name);
	}
	cout << "asm file name(without .asm)" << endl;
	cin >> asmFileName;
	ofstream asmFile;
	asmFile.open("outputAsm/" + asmFileName + ".asm");
	
	if (needLink) {
		Parser par;
		list<Triad> tris;
		tris.push_back(par.readCommand("initalSP"));
		tris.push_back(par.readCommand("call Sys.init 0"));
		writeFile(tris, par, asmFile, "");
	}

	//open file
	for each (string vmFileName in vmFileNames)
	{
		ifstream vmFile;
		vmFile.open("inputVm/" + vmFileName + ".vm");

		//variable
		Parser par;
		list<Triad> tris;

		//read commamds and process 1
		cout << "reading" << endl;
		while (!vmFile.eof()) {
			string temp;
			getline(vmFile, temp);
			par.removeComment(temp);
			if (!temp.empty()) {
				tris.push_back(par.readCommand(temp));
			}
		}

		//process 2
		cout << "putting push and pop" << endl;
		for_each(tris.begin(), tris.end(), [](Triad &cmd) {
			if (cmd.fir == "push" || cmd.fir == "pop")
				cmd.fir = cmd.fir + "_" + cmd.sec;
		});

		writeFile(tris, par, asmFile, vmFileName);
	}
	
	return 0;
}