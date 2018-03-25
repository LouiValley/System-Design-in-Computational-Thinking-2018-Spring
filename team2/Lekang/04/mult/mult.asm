// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//loop in

@2
M=0
@1
D=M
@i
M=D
// SET R2 TO 0 AND I TO R1

(ADD)
@R1
D=M
@END
D;JEQ

@0
D=M
@2
M=D+M
//ADD ONCE

@1
M=M-1

@ADD
0;JMP
//ADD R0 R2 TIMES
(END)
@END
0;JMP
