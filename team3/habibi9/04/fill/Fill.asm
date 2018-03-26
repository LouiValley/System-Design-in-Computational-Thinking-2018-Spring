// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.
(START)
@STATE	//STATE=0
M=0

@SCREEN
D=A
@SCNADDR
M=D	//SCREEN PTR

@KBD
D=M
@BLKINT
D;JGT	//JUMP TO BLKINT IF KEYBOARD
@BLK
0;JMP

(BLKINT)
@STATE
M=M-1

(BLK)
@STATE
D=M

@SCNADDR 
A=M
M=D
@SCNADDR
M=M+1
D=M
@SCREEN
D=D-A
@8191
D=D-A
@START
D;JGT
@BLK
0;JMP