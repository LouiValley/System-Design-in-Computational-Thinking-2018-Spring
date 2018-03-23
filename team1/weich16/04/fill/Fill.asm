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

(BEGIN)

@24576
D=M
@PRESS
D;JGT
@UNPRESS
D;JEQ

(UNPRESS)
@16384
D=A
@count
M=D

(BEGIN_WHITE)
@24608
D=A
@count
D=M-D
@END_WHITE
D;JGT
@count
A=M
M=0
@count
M=M+1
@BEGIN_WHITE
0;JMP
(END_WHITE)

@END
0;JMP

(PRESS)
@16384
D=A
@count
M=D

(BEGIN_BLACK)
@24608
D=A
@count
D=M-D
@END_BLACK
D;JGT
@count
A=M
M=1
@count
M=M+1
@BEGIN_BLACK
0;JMP
(END_BLACK)

@END
0;JMP

(END)
@BEGIN
0;JMP