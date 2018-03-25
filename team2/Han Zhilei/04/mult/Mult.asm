// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//innitialize    
    @sum
    M=0
    @i
    M=0
    
    @R1
    D=M
    @LOOP
    D;JNE
    @R2
    M=0
    @END
    0;JMP

(LOOP)
    @R0
    D=M
    @sum
    M=D+M
    
    @i
    M=M+1
    D=M

    @R1
    D=D-M
    @LOOP
    D;JLT

    @sum
    D=M
    @R2
    M=D

(END)
    @END
    0;JMP
