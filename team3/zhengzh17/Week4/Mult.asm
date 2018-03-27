@R5  //R5=COUNTER
M=1
@R2
M=0  //R2=SUM
(LOOP)
@R5
D=M  //D=R5
@R0
D=D-M  //D=R5-R0
@END
D;JGT  //IF R5>0 (THAT IS R5>R0) GOTO END
@R1
D=M
@R2
M=D+M
@R5
M=M+1
@LOOP
0;JMP
(END)
@END
0;JMP