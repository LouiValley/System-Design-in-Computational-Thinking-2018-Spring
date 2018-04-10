#!/usr/bin/env wolframscript
(* ::Package:: *)

a=ReadList["C:\\Users\\\:8c6a\:732aAndrew\\Desktop\\file\\course\\Nand2Tetris\\Nand2Tetris\\Software\\projects\\06\\pong\\Pong.asm",String]

label={{0,"SP"},{1,"LCL"},{2,"ARG"},{3,"THIS"},{4,"THAT"},{16384,"SCREEN"},{24576,"KBD"},{0,"R0"},{1,"R1"},{2,"R2"},
{3,"R3"},{4,"R4"},{5,"R5"},{6,"R6"},{7,"R7"},{8,"R8"},{9,"R9"},{10,"R10"},{11,"R11"},{12,"R12"},{13,"R13"},{14,"R14"},{15,"R15"}}

computation={"D+1"->"0011111","A+1"->"0110111","D-1"->"0001110","A-1"->"0110010","D+A"->"0000010","D-A"->"0010011","A-D"->"0000111",
"D&A"->"0000000","D|A"->"0010101","M+1"->"1110111","M-1"->"1110010","D+M"->"1000010","D-M"->"1010011","M-D"->"1000111","D&M"->"1000000",
"D|M"->"1010101","1+D"->"0011111","1+A"->"0110111","A+D"->"0000010","A&D"->"0000000","A|D"->"0010101","1+M"->"1110111","M+D"->"1000010",
"M&D"->"1000000","M|D"->"1010101","!D"->"0001101","-D"->"0001111","-A"->"0110011","-1"->"0111010","!A"->"0110001","!M"->"1110001",
"-M"->"1110011","M"->"1110000","D"->"0001100","A"->"0110000","0"->"0101010","1"->"0111111"}

destination={"AMD"->"111","AM"->"101","AD"->"110","MD"->"011","M"->"001","D"->"010","A"->"100"}

jumptable={"JGT"->"001","JEQ"->"010","JGE"->"011","JLT"->"100","JNE"->"101","JLE"->"110","JMP"->"111"}

addr=0
variable=16
output={}

For[i=1,i<=Length[a],i++,
	a[[i]]=StringDelete[a[[i]],"//"~~__];
	a[[i]]=StringDelete[a[[i]]," "];
	If[StringLength[a[[i]]]>0,
		If[StringContainsQ[a[[i]],"("~~__~~")"],
			tmp=StringDelete[a[[i]],{"(",")"}];
			a[[i]]=StringDelete[a[[i]],"("~~__~~")"];
			AppendTo[label,{addr,tmp}];
			Continue[]
		];
		addr+=1
	];
]

For[i=1,i<=Length[a],i++,
	If[StringLength[a[[i]]]>0,
		If[StringContainsQ[a[[i]],"@"],
			tmp=StringDelete[a[[i]],"@"];
			check=True;
			If[StringMatchQ[tmp,DigitCharacter ..],check=False];
			For[k=1,k<=Length[label],k++,
				If[StringMatchQ[ToString[tmp],Part[label[[k]],2]],tmp=Part[label[[k]],1];check=False;Break]
				];
			If[check,AppendTo[label,{variable,tmp}];tmp=variable;variable+=1];
			tmp=ToExpression[tmp];
			tmp=IntegerString[tmp,2,16];
			AppendTo[output,tmp],
			
			head="111";
			comp="0000000";
			dest="000";
			jump="000";
			If[StringContainsQ[a[[i]],"="],
				If[StringContainsQ[a[[i]],";"],
					comp=StringReplace[StringDelete[a[[i]],{";"~~__,__~~"="}],computation];
					dest=StringReplace[StringDelete[a[[i]],"="~~__],destination];
					jump=StringReplace[StringDelete[a[[i]],__~~";"],jumptable],
					comp=StringReplace[StringDelete[a[[i]],__~~"="],computation];
					dest=StringReplace[StringDelete[a[[i]],"="~~__],destination];
				],
				comp=StringReplace[StringDelete[a[[i]],";"~~__],computation];
				jump=StringReplace[StringDelete[a[[i]],__~~";"],jumptable]
			];
			tmp=head<>comp<>dest<>jump;
			AppendTo[output,tmp]
		]	
	]
]
Export["C:\\Users\\\:8c6a\:732aAndrew\\Desktop\\file\\course\\Nand2Tetris\\Nand2Tetris\\Software\\projects\\06\\pong\\Pong.txt",output]


(* ::InheritFromParent:: *)
(*"C:\\Users\\\:8c6a\:732aAndrew\\Desktop\\file\\course\\Nand2Tetris\\Nand2Tetris\\Software\\projects\\06\\max\\Max.txt"*)
