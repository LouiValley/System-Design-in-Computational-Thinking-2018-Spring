#!/usr/bin/env wolframscript
(* ::Package:: *)

(*This script will tokenize the file whose location is pre-loaded in the variable: address

 and form a list in xml form *)
 (*<token> and </token> will be added in the beginning and the end*)
 
 
 (*Function 1*)(*Delete all the notes and remove empty strings*)
MakeItClean[x_] := 
 StringDelete[x, {"//" ~~ __, "/*" ~~ __ ~~ "*/", "/**" ~~ __ ~~ "*/"}]

ACleanTable[x_] := 
 DeleteCases[
  Table[StringTrim[MakeItClean[Import[x, "Lines"][[i]]]], {i, 
    Length[Import[x, "Lines"]]}], ""]
    
    (*Function 2*)
(*Saparate all the strings by tokens given*)

Keywords = {"class", "constructor", "function", "method", "field", 
  "static", "var", "int", "char", "boolean", "void", "true", "false", 
  "null", "this", "let", "do", "if", "else", "while", "return"}

Symbols = {"{", "}", "(", ")", "[", "]", ".", ",", ";", "+", "-", "*",
   "/", "&", "|", "<", ">", "=", "~"}

(*Codes below divides one sring by our tokens using specific \
StringSplit function*)

SplitOneString[x_] := 
 DeleteCases[
  If[StringContainsQ[x, "\""], SpecialOperation[x], 
   StringSplit[x, {" ", y : Symbols :> y}]], ""]
   
   SpecialOperation[x_] := 
 Catenate[{StringSplit[
    StringExtract[x, "\"" -> All][[1]], {" ", 
     y : Symbols :> y}], {StringJoin["\"", 
     StringExtract[x, "\"" -> All][[2]], "\""]}, 
   StringSplit[
    StringExtract[x, "\"" -> All][[-1]], {" ", y : Symbols :> y}]}]

(*Form a standard list of every word*)

Tokenizer[x_] := 
 Catenate[Table[
   SplitOneString[x[[i]]], {i, Length[x]}]]
   
   
(*Above gives us a tokenizer which enables us to tokenize all the imports*)
(*Below gives us a Analyzer to read, define and write*)

(*Remark*)

(*
Only keywords decide non-terminals
Others are all terminals
*)

(*This part is for terminals except keywords*)

Analyzer[x_]:=Which[
StringContainsQ[x,Keywords],StringJoin["<keyword> ",x," </keyword>"],
StringContainsQ[x,Symbols],StringJoin["<symbol> ",StringTake[x,{2,-2}]," </symbol>"],
StringContainsQ[x,"\""],StringJoin["<stringConstant> ",x," </stringConstant>"],
StringMatchQ[x,Table[ToString[j],{j,0,32767}]],StringJoin["<integerConstant> ",x," </integerConstant>"],
StringMatchQ[x, RegularExpression["\\w+"]],
	If[StringStartsQ[x,RegularExpression["\\ d"]],"Grammar Fault",StringJoin["<identifier> ",x," </identifier>"]]
]

(*This is for the keywords and non-terminals*)
   

(*address is given in the main program*)


table=ACleanTable[address]
listone=Tokenizer[table]
listtwo=Table[Analyzer[listone[[i]]],{i,Length[listone]}]
finallist0=PrependTo[listtwo,"<token>"]
finallist=AppendTo[finallist0,"</token>"]

