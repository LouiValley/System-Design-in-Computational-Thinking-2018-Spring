// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.

(LOOP1)
	@KBD
	D=M
	@WHITE
	D;JEQ

(BLACK)
	@i
	M=0
(LOOP2)
	@8192
	D=A
	@i
	D=D-M
	@LOOP1
	D;JEQ

	@i
	D=M
	M=M+1
	@SCREEN
	A=A+D
	M=-1
	@LOOP2
	0;JMP

(WHITE)
	@i
	M=0
(LOOP4)
	@8192
	D=A
	@i
	D=D-M
	@LOOP1
	D;JEQ

@i
D=M
M=M+1
@SCREEN
A=A+D
M=0
@LOOP4
0;JMP
