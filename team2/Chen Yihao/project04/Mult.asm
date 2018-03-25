// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
(START)
	@R0
	D=M
	@i
	M=D
	@ZERO
	D;JEQ
	@NEGA0
	D;JLT
	@R1
	D=M
	@j
	M=D
	@ZERO
	D;JEQ
	@NEGA1
	D;JLT
	
(LOOP)
	@i
	D=M
	@SIGN
	D;JEQ
	@j
	D=M
	@R2
	M=M+D
	@i
	M=M-1
	@LOOP
	0;JMP

(ZERO)
	@R2
	M=0
	@END
	0;JMP

(NEGA0)
	@R0
	M=-M
	@t
	M=M+1
	@START
	0;JMP

(NEGA1)
	@R1
	M=-M
	@t
	M=M-1
	@START
	0;JMP

(SIGN)
	@t
	D=M
	@END
	D;JEQ
	@R2
	M=-M
	@END
	0;JMP

(END)
	@END
	0;JMP