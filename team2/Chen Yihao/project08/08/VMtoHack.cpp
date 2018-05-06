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
	ifstream input("Sys.vm"); 
	string buffer("");
	while(getline(input, buffer)){
		char key1[20]="", key2[20]="";int key3;
		sscanf(buffer.c_str(),"%[^ ] %[^ ] %d", key1, key2, &key3);
		
		//begin with push
		if(strcmp(key1,"push")==0){
			if(strcmp(key2, "constant")==0){
				stack.push(key3);
				cout<<"@SP\nA=M\nM="<<key3<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"argument")==0){
				stack.push(Heap[_argument+key3-2048]);
				cout<<"@ARG\nD=M\n@"<<key3<<"\nA=A+D\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"local")==0){
				stack.push(Heap[_local+key3-2048]);
				cout<<"@LCL\nD=M\n@"<<key3<<"\nA=A+D\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"static")==0){
				stack.push(Static[key3]);
				cout<<"@"<<key3+16<<"\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"pointer")==0){
				stack.push(_pointer[key3]);
				cout<<"@"<<(key3==0 ? "THIS" : "THAT")<<"\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"this")==0){
				stack.push(Heap[_pointer[0]+key3-2048]);
				cout<<"@THIS\nD=M\n@"<<key3<<"\nA=A+D\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
			if(strcmp(key2,"that")==0){
				stack.push(Heap[key3+_pointer[1]-2048]);
				cout<<"@THAT\nD=M\n@"<<key3<<"\nA=A+D\nD=M\n@SP\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
		}

		//begin with pop
		if(strcmp(key1,"pop")==0){
			if(strcmp(key2,"local")==0){
				Heap[_local+key3]=stack.pop();
				cout<<"@LCL\nD=M\n@"<<key3<<"\nD=A+D\n@13\M=D\n@SP\nA=M-1\nD=M\n@13\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M-1"<<endl;
			}
			if(strcmp(key2,"argument")==0){
				Heap[_argument+key3]=stack.pop();
				cout<<"@ARG\nD=M\n@"<<key3<<"\nD=A+D\n@13\M=D\n@SP\nA=M-1\nD=M\n@13\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M-1"<<endl;
			}
			if(strcmp(key2,"this")==0){
				Heap[_pointer[0]+key3-2048]=stack.pop();
				cout<<"@THIS\nD=M\n@"<<key3<<"\nD=A+D\n@13\M=D\n@SP\nA=M-1\nD=M\n@13\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M-1"<<endl;
			}
			if(strcmp(key2,"that")==0){
				Heap[_pointer[1]+key3-2048]=stack.pop();
				cout<<"@THAT\nD=M\n@"<<key3<<"\nD=A+D\n@13\M=D\n@SP\nA=M-1\nD=M\n@13\nA=M\nM=D"<<endl;
				cout<<"@SP\nM=M-1"<<endl;
			}
			if(strcmp(key2,"pointer")==0){
				_pointer[key3]=stack.pop();
				cout<<"@SP\nA=M-1\nD=M\n@"<<(key3==0 ? "THIS" : "THAT")<<"\nM=D"<<endl; 
				cout<<"@SP\nM=M-1"<<endl;
			}
		}
		
		//begin with arithmetic operands
		if(strcmp(key1,"add")==0){
			stack.add();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M+D\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"sub")==0){
			stack.sub();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M-D\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"neg")==0){
			stack.neg();
			cout<<"@SP\nA=M-1\nM=-M"<<endl;
		}
		if(strcmp(key1,"eq")==0){
			stack.eq();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M-D"<<endl;
			cout<<"A=-1@0\nD;JNQ\nD=A\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"gt")==0){
			stack.gt();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M-D"<<endl;
			cout<<"A=-1@0\nD;JLE\nD=A\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"lt")==0){
			stack.lt();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M-D"<<endl;
			cout<<"A=-1@0\nD;JGE\nD=A\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"and")==0){
			stack.bit_and();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M&D\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"or")==0){
			stack.bit_or();
			cout<<"@SP\nM=M-1"<<endl;
			cout<<"@SP\nA=M\nD=M\n@13\nM=D"<<endl;
			cout<<"@SP\nA=M-1\nD=M\n@13\nD=M|D\n@SP\nA=M-1\nM=D"<<endl;
		}
		if(strcmp(key1,"not")==0){
			stack.bit_not();
			cout<<"@SP\nA=M-1\nM=!M"<<endl;
		}

		//begin with label
		if(strcmp(key1,"label")==0){
			cout<<"("<<key2<<")"<<endl;
		}

		//begin with goto
		if(strcmp(key1,"goto")==0){
			cout<<"@"<<key2<<endl;
			cout<<"0;JMP"<<endl;
		}

		//begin with if-goto
		if(strcmp(key1,"if-goto")==0){
			cout<<"@SP\nA=M-1\nD=M\n@"<<key2<<"\nD+1;JEQ"<<endl;
		}

		//begin with function
		if(strcmp(key1,"function")==0){
			cout<<"("<<key2<<")"<<endl;//declare a label for the function entry
			for(int i=0;i<key3;i++){
				cout<<"@SP\nA=M\nM=0"<<endl;
				cout<<"@SP\nM=M+1"<<endl;
			}
		}

		//begin with call
		if(strcmp(key1,"call")==0){
			cout<<"@RETURN_ADDRESS_"<<key2<<"\nD=A\n@SP\nA=M\nM=D"<<endl;//push return-address
			cout<<"@SP\nM=M+1"<<endl;
			cout<<"@LCL\nD=M\n@SP\nA=M\nM=D"<<endl;//push LCL
			cout<<"@SP\nM=M+1"<<endl;
			cout<<"@ARG\nD=M\n@SP\nA=M\nM=D"<<endl;//push ARG
			cout<<"@SP\nM=M+1"<<endl;
			cout<<"@THIS\nD=M\n@SP\nA=M\nM=D"<<endl;//push THIS
			cout<<"@SP\nM=M+1"<<endl;
			cout<<"@THAT\nD=M\n@SP\nA=M\nM=D"<<endl;//push THAT
			cout<<"@SP\nM=M+1"<<endl;
			cout<<"@SP\nD=M\n@"<<key3+5<<"\nD=D-A\n@ARG\nM=D"<<endl;//ARG=SP-n-5
			cout<<"@SP\nD=M\n@LCL\nM=D"<<endl;//LCL=SP
			cout<<"@"<<key2<<"\n0;JMP"<<endl;//goto f
			cout<<"(RETURN_ADDRESS_"<<key2<<")"<<endl;//Declare return address label
		}

		//begin with return 
		if(strcmp(key1,"return")==0){
			cout<<"@LCL\n\D=M\n@13\nM=D"<<endl;//FRAME=LCL
			cout<<"@5\nD=A\n@13\nD=M-D\nA=D\nD=M\n@14\nM=D"<<endl;//RET=*(FRAME-5)
			cout<<"@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D"<<endl;//*ARG=pop()
			cout<<"@ARG\nD=M\n@SP\nM=D+1"<<endl;//SP=ARG+1
			cout<<"@13\nM=M-1\nA=M\nD=M\n@THAT\nM=D"<<endl;//THAT=*(FRAME-1)
			cout<<"@13\nM=M-1\nA=M\nD=M\n@THIS\nM=D"<<endl;//THIS=*(FRAME-2)
			cout<<"@13\nM=M-1\nA=M\nD=M\n@ARG\nM=D"<<endl;//ARG=*(FRAME-3)
			cout<<"@13\nM=M-1\nA=M\nD=M\n@LCL\nM=D"<<endl;//LCL=*(FRAME-4)
			cout<<"@14\nA=M\n0;JMP"<<endl;//goto RET
		}
	}

	return 0;
}

