// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.
//
//by Han Zhilei
    
    @SCREEN
    D=A
    @screenaddr
    M=D
    @count
    M=0

(MAINLOOP)
    @KBD //1
    D=M
    @BLACK
    D;JNE

(WHITE)
    @count
    M=0

(WHITELOOP)
    @screenaddr
    D=M
    @count
    A=D+M
    M=0

    @count
    M=M+1
    D=M

    @8192
    D=D-A

    @WHITELOOP
    D;JLT

    @MAINLOOP
    0;JMP

(BLACK)
    //@8192  //7
    //D=A
    @count
    M=0

//    @SCREEN
//    D=A
//    @screenaddr
//    M=D

(BLACKLOOP)
    @screenaddr
    D=M
    @count
    A=D+M
    M=-1

    @count
    M=M+1
    D=M

    @8192
    D=D-A

    @BLACKLOOP
    D;JLT

    @MAINLOOP
    0;JMP
