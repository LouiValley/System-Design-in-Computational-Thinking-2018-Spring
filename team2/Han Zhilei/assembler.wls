#!/usr/bin/env wolframscript
(* ::Package:: *)

#parse
#deletecomments
inputlist=ReadList[$ScriptCommandLine[[2]],Record,RecordSeparators->{"\n","\r\n","\r"}]
inputlist=StringDelete[inputlist,"//"~~___]
inputlist=StringReplace[inputlist,(StartOfString~~Whitespace)|(Whitespace~~EndOfString):>""]


#deletewhitespace
inputnumber=Length[inputlist]
commandlist={}
deletewhitespace:=Module[{i=1},
		For[i,i<=inputnumber,i++,
				If[StringLength[inputlist[[i]]]==0,Null,AppendTo[commandlist,inputlist[[i]]]]]]

deletewhitespace
#Print[commandlist]

commandnumber=Length[commandlist]
#dictionary
symboltable={
	"R0"->"0",
	"R1"->"1",
	"R2"->"2",
	"R3"->"3",
	"R4"->"4",
	"R5"->"5",
	"R6"->"6",
	"R7"->"7",
	"R8"->"8",
	"R9"->"9",
	"R10"->"10",
	"R11"->"11",
	"R12"->"12",
	"R13"->"13",
	"R14"->"14",
	"R15"->"15",
	"SCREEN"->"16384",
	"KBD"->"24576",
	"SP"->"0",
	"LCL"->"1",
	"ARG"->"2",
	"THIS"->"3",
	"THAT"->"4"
}
tobedeleted={}
replacelabel:=Module[{i,countinstruction=0},
	For[i=1,i<=commandnumber,i++,
		If[StringMatchQ[commandlist[[i]],"("~~__~~")"],
		    AppendTo[tobedeleted,i];
            AppendTo[symboltable,"@"<>StringSplit[commandlist[[i]],{"(",")"}][[1]]~~EndOfString->"@"<>ToString[countinstruction]],
            countinstruction++
        ]
	]
]
replacelabel

deletelabel:=Module[{i},
    For[i=-1,i>=-Length[tobedeleted],i--,
        commandlist=Delete[commandlist,tobedeleted[[i]]]
    ]
] 
deletelabel

#update
commandnumber=Length[commandlist]

#replaceallthesymbols
freespace=16
commandlist=StringReplace[commandlist,symboltable]
replacesymbol:=Module[{i,tmp},
    For[i=1,i<=commandnumber,i++,
        If[StringContainsQ[commandlist[[i]],StartOfString~~"@"~~WordCharacter..~~LetterCharacter..],
            tmp="@"<>StringSplit[commandlist[[i]],"@"][[1]]~~EndOfString->"@"<>ToString[freespace];
            AppendTo[symboltable,tmp];
            commandlist=StringReplace[commandlist,tmp];
            freespace++
        ]
    ]
]
replacesymbol

#Print[commandlist]
#Print[symboltable]


#\:7ffb\:8bd1\:90e8\:5206\:ff1a
#
#


machinecode={}

tabledest={
    StartOfString~~"null"~~EndOfString->"000",
    StartOfString~~"M"~~EndOfString->"001",
    StartOfString~~"D"~~EndOfString->"010",
    StartOfString~~"MD"~~EndOfString->"011",
    StartOfString~~"A"~~EndOfString->"100",
    StartOfString~~"AM"~~EndOfString->"101",
    StartOfString~~"AD"~~EndOfString->"110",
    StartOfString~~"AMD"~~EndOfString->"111"
}

tablejump={
    StartOfString~~"null"~~EndOfString->"000",
    StartOfString~~"JGT"~~EndOfString->"001",
    StartOfString~~"JEQ"~~EndOfString->"010",
    StartOfString~~"JGE"~~EndOfString->"011",
    StartOfString~~"JLT"~~EndOfString->"100",
    StartOfString~~"JNE"~~EndOfString->"101",
    StartOfString~~"JLE"~~EndOfString->"110",
    StartOfString~~"JMP"~~EndOfString->"111"
}

comptablewithA={
    StartOfString~~"0"~~EndOfString->"101010",
    StartOfString~~"1"~~EndOfString->"111111",
    StartOfString~~"-1"~~EndOfString->"111010",
    StartOfString~~"D"~~EndOfString->"001100",
    StartOfString~~"A"~~EndOfString->"110000",
    StartOfString~~"!D"~~EndOfString->"001101",
    StartOfString~~"!A"~~EndOfString->"110001",
    StartOfString~~"-D"~~EndOfString->"001111",
    StartOfString~~"-A"~~EndOfString->"110011",
    StartOfString~~"D+1"~~EndOfString->"011111",
    StartOfString~~"A+1"~~EndOfString->"110111",
    StartOfString~~"D-1"~~EndOfString->"001110",
    StartOfString~~"A-1"~~EndOfString->"110010",
    StartOfString~~"D+A"~~EndOfString->"000010",
    StartOfString~~"D-A"~~EndOfString->"010011",
    StartOfString~~"A-D"~~EndOfString->"000111",
    StartOfString~~"D&A"~~EndOfString->"000000",
    StartOfString~~"D|A"~~EndOfString->"010101"
}

For[i=1,i<=commandnumber,i++,
    If[StringMatchQ[commandlist[[i]],RegularExpression["^@\\d+$"]],
        base10=StringSplit[commandlist[[i]],"@"][[1]];
        base2=IntegerString[ToExpression[base10],2];
        base2length=StringLength[base2];
        AppendTo[machinecode,Nest["0"<># &,"0",16-base2length-1]<>base2],
        tmp1=StringSplit[commandlist[[i]],"="];
        #Print[tmp1];
        If[StringContainsQ[tmp1[[1]],";"],
            dest="null";tmp2=tmp1[[1]],
            dest=tmp1[[1]];tmp2=tmp1[[2]]
        ];
        If[Not[StringContainsQ[tmp2,"J"]],
            jump="null";
            comp=tmp2,
            comp=StringSplit[tmp2,";"][[1]];
            jump=StringSplit[tmp2,";"][[2]]
        ];
        #Print[dest];
        #Print[comp];
        #Print[jump];
        If[StringContainsQ[comp,"M"],
            comp=StringReplace[comp,"M"->"A"];
            AppendTo[machinecode,"1111"<>StringReplace[comp,comptablewithA]<>StringReplace[dest,tabledest]<>StringReplace[jump,tablejump]],
            AppendTo[machinecode,"1110"<>StringReplace[comp,comptablewithA]<>StringReplace[dest,tabledest]<>StringReplace[jump,tablejump]]
        ]
    ]
]
#Print[machinecode]

#Print[Length[machinecode]]
#Print[Length[commandlist]]

For[j=1,j<=commandnumber,j++,
    Print[machinecode[[j]]]
]
