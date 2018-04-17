//
//  Parser.h
//  VM
//
//  Created by NaXin on 2018/4/16.
//  Copyright © 2018年 NaXin. All rights reserved.
//

#ifndef Parser_h
#define Parser_h
#include <string>
#include <regex>
#include <sstream>

using namespace std;

struct Triad
{
	string fir;
	string sec;
	string thr;
};

int getNum(string s)
{
	int a;
	stringstream ss(s);
	ss >> a;
	return a;
}

string littleReplacer(string temp, string filename, Triad &cmd)
{
	string result;
	for (long long i = 0; i < temp.size(); i++) {
		if (temp[i] == '^')
			while (i < temp.size() && temp[i] != '$')
				switch (temp[i]) {
				case '<': result += cmd.sec; break;
				case '>': result += cmd.thr; break;
				case '~': result += filename; break;
				default:throw runtime_error("no such char"); break;
				}
		else result.push_back(temp[i]);
	}
	return result;
}

class Parser {

public:
	void removeComment(string &cmd) {
		if (cmd.find("//") != string::npos)
			cmd = cmd.substr(0, cmd.find("//"));
		return;
	}

	Triad readCommand(string s) {
		int currentSeg = 0;
		Triad tri;

		for (long long i = 0; i < s.size();)
		{
			if (s[i] != ' ' && s[i] != '\t') {
				switch (currentSeg) {
				case 0:
					tri.fir.push_back(s[i]);
					break;
				case 1:
					tri.sec.push_back(s[i]);
					break;
				case 2:
					tri.thr.push_back(s[i]);
					break;
				default:
					throw runtime_error("the Triad only accpets 3 inputs.");
					break;
				}
				i++;
			}
			else {
				while ((s[i] == ' ' || s[i] == '\t') && i < s.size()) i++;
				if (i != s.size())
					currentSeg++;
			}
		}
		return tri;
	}
};

#endif /* Parser_h */
