//RAM addresses:
//0-15 Virtual registers
		//RAM[0]   SP
		//RAM[1]   LCL
		//RAM[2]   ARG
		//RAM[3]   THIS
		//RAM[4]   THAT
		//RAM[5-12]    temp segment
		//RAM[13-15]    general purpose
//16-255 Static variables
//256-2047 Stack
//2048-16483 Heap
//16384-24575 I/O

#include<string>
#include<fstream>
#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

//show as pointers{
	int _argument=0; //ARG
	int _local=0;            //LCL   
	int _pointer[2]={0,0};//this & that
//}

//show as part of RAM{
	int Heap[14436];//2048-16483
	int Static[240];     //16-255
//}

class Stack{
private:
	int* memory;
	int sp;
public:
	Stack(int capacity){
		sp=0;
		memory=new int[capacity];
	}
	~Stack(){
		delete [] memory;
	}
	int get_sp(){
		return sp;
	}
	int get_top(){
		if(sp>0) return memory[sp-1];
		return 0;
	}
	void push(int number){
		memory[sp]=number;
		sp+=1;
	}
	int pop(){
		if(sp>0) sp-=1;
		return memory[sp];
	}
	void add(){
		memory[sp-2]=memory[sp-1]+memory[sp-2];
		sp-=1;
	}
	void sub(){
		memory[sp-2]=memory[sp-2]-memory[sp-1];
		sp-=1;
	}
	void neg(){
		memory[sp-1]=0-memory[sp-1];
	}
	void eq(){
		if(memory[sp-1]==memory[sp-2]){
			memory[sp-2]=-1;
		}
		else memory[sp-2]=0;
		sp-=1;
	}
	void gt(){
		if(memory[sp-2]>memory[sp-1]){
			memory[sp-2]=-1;
		}
		else memory[sp-2]=0;
		sp-=1;
	}
	void lt(){
		if(memory[sp-2]<memory[sp-1]){
			memory[sp-2]=-1;
		}
		else memory[sp-2]=0;
		sp-=1;
	}
	void bit_and(){
		memory[sp-2]=memory[sp-2]&memory[sp-1];
		sp-=1;
	}
	void bit_or(){
		memory[sp-2]=memory[sp-2]|memory[sp-1];
		sp-=1;
	}
	void bit_not(){
		memory[sp-1]=~memory[sp-1];
	}
} stack(1792);//256-2047

int main(){
	//initializition
	for(int i=0;i<14436;i++){
		Heap[i]=0;
	}
	for(int i=0;i<240;i++){
		Static[i]=0; 
	}

	//input
	cout<<"@SP\nM=256\n";
	ifstream input("input.txt"); 
	string buffer("");
	while(getline(input, buffer)){
		char key1[20]="", key2[20]="";int key3;
		sscanf(buffer.c_str(),"%[^ ] %[^ ] %d", key1, key2, &key3);
		
		//begin with push
		if(strcmp(key1,"push")==0){
			if(strcmp(key2, "constant")==0){
				stack.push(key3);
				cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					     <<stack.get_sp()+255<<"\nM="<<key3<<"\n";
			}
			if(strcmp(key2,"argument")==0){
				stack.push(Heap[_argument+key3-2048]);
				cout<<"@"<<_argument+key3<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
			if(strcmp(key2,"local")==0){
				stack.push(Heap[_local+key3-2048]);
				cout<<"@"<<_local+key3<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
			if(strcmp(key2,"static")==0){
				stack.push(Static[key3]);
				cout<<"@"<<key3+16<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
			if(strcmp(key2,"pointer")==0){
				stack.push(_pointer[key3]);
				cout<<"@"<<(key3==0 ? "THIS" : "THAT")<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
			if(strcmp(key2,"this")==0){
				stack.push(Heap[_pointer[0]+key3-2048]);
				cout<<"@"<<key3+_pointer[0]<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
			if(strcmp(key2,"that")==0){
				stack.push(Heap[key3+_pointer[1]-2048]);
				cout<<"@"<<key3+_pointer[1]<<"\nD=M\n@"
						<<stack.get_sp()+255<<"\nM=D\n@SP\nM="
						<<stack.get_sp()+256<<"\n";
			}
		}

		//begin with pop
		if(strcmp(key1,"pop")==0){
			if(strcmp(key2,"local")==0){
				Heap[_local+key3]=stack.pop();
				cout<<"@"<<stack.get_sp()+256<<"\nD=M\n@SP\nM="
						<<stack.get_sp()+256<<"\n@"<<_local+key3<<"\nM=D\n";
			}
			if(strcmp(key2,"argument")==0){
				Heap[_argument+key3]=stack.pop();
				cout<<"@"<<stack.get_sp()+256<<"\nD=M\n@SP\nM="
						<<stack.get_sp()+256<<"\n@"<<_argument+key3<<"\nM=D\n";
			}
			if(strcmp(key2,"this")==0){
				Heap[_pointer[0]+key3-2048]=stack.pop();
				cout<<"@"<<stack.get_sp()+256<<"\nD=M\n@SP\nM="
						<<stack.get_sp()+256<<"\n@"<<_pointer[0]+key3<<"\nM=D\n";
			}
			if(strcmp(key2,"that")==0){
				Heap[_pointer[1]+key3-2048]=stack.pop();
				cout<<"@"<<stack.get_sp()+256<<"\nD=M\n@SP\nM="
						<<stack.get_sp()+256<<"\n@"<<_pointer[1]+key3<<"\nM=D\n";
			}
			if(strcmp(key2,"pointer")==0){
				_pointer[key3]=stack.pop();
				cout<<"@"<<stack.get_sp()+256<<"\nD=M\n@SP\nM="
						<<stack.get_sp()+256<<"\n@"<<(key3==0 ? "THIS" : "THAT")
						<<"\nM=D\n"; 
			}
		}
		
		//begin with arithmetic operands
		if(strcmp(key1,"add")==0){
			stack.add();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"sub")==0){
			stack.sub();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"neg")==0){
			stack.neg();
			cout<<"@SP\nM="<<stack.get_sp()+255<<"\n@SP\nM="<<stack.get_sp()+256
					<<"\n@"<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"eq")==0){
			stack.eq();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"gt")==0){
			stack.gt();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"lt")==0){
			stack.lt();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"and")==0){
			stack.bit_and();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"or")==0){
			stack.bit_or();
			cout<<"@SP\nM="<<stack.get_sp()+256<<"\n@"
					<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
		if(strcmp(key1,"not")==0){
			stack.bit_not();
			cout<<"@SP\nM="<<stack.get_sp()+255<<"\n@SP\nM="<<stack.get_sp()+256
					<<"\n@"<<stack.get_sp()+255<<"\nM="<<stack.get_top()<<"\n";
		}
	}
	return 0;
}

