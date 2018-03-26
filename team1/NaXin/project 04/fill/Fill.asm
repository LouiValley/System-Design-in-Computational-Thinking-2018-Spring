// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.
	//main enter
	@CHE
	0;JMP
(CHE)
	//init i
	@16384
	D=A
	@i
	M=D
	
	//judge the keyboard
	@24576
	D=M
	
	//decide
	@WHI
	D;JEQ
	@BLA
	D;JNE
	@CHE
	0;JMP
(WHI)
	//check if key changes
	@24576
	D=M
	@CHE
	D;JNE
	
	//jump if ends
	@i
	D=M
	@24576
	D=D-A
	@CHE
	D;JEQ
	
	//put ran[i] to 0
	@i
	A=M
	M=0
	
	//i++
	@i
	M=M+1
	@WHI
	0;JMP
	
(BLA)
	//check if key changes
	@24576
	D=M
	@CHE
	D;JEQ
	
	//jump if ends
	@i
	D=M
	@24576
	D=D-A
	@CHE
	D;JEQ
	
	//put ran[i] to -1
	@i
	A=M
	M=-1
	
	//i++
	@i
	M=M+1
	@BLA
	0;JMP