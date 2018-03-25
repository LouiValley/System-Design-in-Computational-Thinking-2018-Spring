// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//	i = 1
//	loop{
//		if i > y end
//		x = x + y
//		i = i +1

@R0
D=M
@X
M=D	//X = R0

@R1
D=M
@Y
M=D	//Y = R1

@R2
M=0

@I
M=1	//I = 1

@SUM
M = 0	//SUM = 0

(LOOP)
@I
D=M
@Y
D=D-M
@WRITE
D;JGT	//IF I > Y END

@X
D=M
@SUM
M=M+D //SUM+=X

@I
M=M+1	//I+=1

@LOOP
0;JMP

(WRITE)
@SUM
D=M
@R2
M=D

(END)
@END
0;JMP
