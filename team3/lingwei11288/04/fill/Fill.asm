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
@24576

D=A

@MXSCREEN

M=D

@SCREEN

D=A

@POINTER

M=D

(LOOP)

@KBD

  D=M

  @FILL

  D; JGT

  @UNFILL

  0; JMP

  @SCREEN

  D=A

  @POINTER

  D=D-M

  @LOOP

  D; JEQ

  D=0

  @POINTER

  A=M

  M=D

  D=1

  @POINTER

  D=M-D

  @POINTER

  M=D

  @LOOP

  0; JMP
(FILL)

  @MXSCREEN

  D=M

  @POINTER

  D=D-M

  @LOOP

  D; JEQ

  D=-1

  @POINTER

  A=M

  M=D

   D=1

  @POINTER

  D=D+M

  @POINTER

  M=D

   @LOOP

  0; JMP