@SP
M=0
@SP
D=M
@256
D=A+D
@13
M=D
@Sys.init&returnaddr
D=A
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@LCL
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THIS
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THAT
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@LCL
M=D
@0
D=D-A
@5
D=D-A
@ARG
M=D
@Sys.init
0;JMP
(Sys.init&returnaddr)
//C_FUNCTION function Class1.set
(Class1.set)
//C_PUSH push argument 0
@SP
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@0
A=D+A
D=M
@13
A=M
M=D
@SP
M=M+1
//C_POP pop static 0
@SP
D=M
@256
A=A+D
A=A-1
D=M
@Class1.0
M=D
@SP
M=M-1
//C_PUSH push argument 1
@SP
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@1
A=D+A
D=M
@13
A=M
M=D
@SP
M=M+1
//C_POP pop static 1
@SP
D=M
@256
A=A+D
A=A-1
D=M
@Class1.1
M=D
@SP
M=M-1
//C_PUSH push constant 0
@SP
D=M
@256
D=A+D
@13
M=D
@0
D=A
@13
A=M
M=D
@SP
M=M+1
//C_RETURN return 
@LCL
D=M
@14
M=D
@ARG
D=M
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
@ARG
D=M
D=D+1
@256
D=D-A
@SP
M=D
@14
D=M
D=D-1
A=D
D=M
@THAT
M=D
@14
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@14
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@14
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
D=M
@5
D=D-A
A=D
A=M
0;JMP
//C_FUNCTION function Class1.get
(Class1.get)
//C_PUSH push static 0
@SP
D=M
@256
D=A+D
@13
M=D
@Class1.0
D=M
@13
A=M
M=D
@SP
M=M+1
//C_PUSH push static 1
@SP
D=M
@256
D=A+D
@13
M=D
@Class1.1
D=M
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC sub
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_RETURN return 
@LCL
D=M
@14
M=D
@ARG
D=M
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
@ARG
D=M
D=D+1
@256
D=D-A
@SP
M=D
@14
D=M
D=D-1
A=D
D=M
@THAT
M=D
@14
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@14
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@14
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
D=M
@5
D=D-A
A=D
A=M
0;JMP
//C_FUNCTION function Class2.set
(Class2.set)
//C_PUSH push argument 0
@SP
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@0
A=D+A
D=M
@13
A=M
M=D
@SP
M=M+1
//C_POP pop static 0
@SP
D=M
@256
A=A+D
A=A-1
D=M
@Class2.0
M=D
@SP
M=M-1
//C_PUSH push argument 1
@SP
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@1
A=D+A
D=M
@13
A=M
M=D
@SP
M=M+1
//C_POP pop static 1
@SP
D=M
@256
A=A+D
A=A-1
D=M
@Class2.1
M=D
@SP
M=M-1
//C_PUSH push constant 0
@SP
D=M
@256
D=A+D
@13
M=D
@0
D=A
@13
A=M
M=D
@SP
M=M+1
//C_RETURN return 
@LCL
D=M
@14
M=D
@ARG
D=M
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
@ARG
D=M
D=D+1
@256
D=D-A
@SP
M=D
@14
D=M
D=D-1
A=D
D=M
@THAT
M=D
@14
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@14
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@14
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
D=M
@5
D=D-A
A=D
A=M
0;JMP
//C_FUNCTION function Class2.get
(Class2.get)
//C_PUSH push static 0
@SP
D=M
@256
D=A+D
@13
M=D
@Class2.0
D=M
@13
A=M
M=D
@SP
M=M+1
//C_PUSH push static 1
@SP
D=M
@256
D=A+D
@13
M=D
@Class2.1
D=M
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC sub
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_RETURN return 
@LCL
D=M
@14
M=D
@ARG
D=M
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
@ARG
D=M
D=D+1
@256
D=D-A
@SP
M=D
@14
D=M
D=D-1
A=D
D=M
@THAT
M=D
@14
D=M
@2
D=D-A
A=D
D=M
@THIS
M=D
@14
D=M
@3
D=D-A
A=D
D=M
@ARG
M=D
@14
D=M
@4
D=D-A
A=D
D=M
@LCL
M=D
@14
D=M
@5
D=D-A
A=D
A=M
0;JMP
//C_FUNCTION function Sys.init
(Sys.init)
//C_PUSH push constant 6
@SP
D=M
@256
D=A+D
@13
M=D
@6
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH push constant 8
@SP
D=M
@256
D=A+D
@13
M=D
@8
D=A
@13
A=M
M=D
@SP
M=M+1
//C_CALL call Class1.set
@SP
D=M
@256
D=A+D
@13
M=D
@Class1.set&returnaddr
D=A
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@LCL
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THIS
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THAT
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@LCL
M=D
@2
D=D-A
@5
D=D-A
@ARG
M=D
@Class1.set
0;JMP
(Class1.set&returnaddr)
//C_POP pop temp 0
@5
D=A
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
//C_PUSH push constant 23
@SP
D=M
@256
D=A+D
@13
M=D
@23
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH push constant 15
@SP
D=M
@256
D=A+D
@13
M=D
@15
D=A
@13
A=M
M=D
@SP
M=M+1
//C_CALL call Class2.set
@SP
D=M
@256
D=A+D
@13
M=D
@Class2.set&returnaddr
D=A
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@LCL
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THIS
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THAT
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@LCL
M=D
@2
D=D-A
@5
D=D-A
@ARG
M=D
@Class2.set
0;JMP
(Class2.set&returnaddr)
//C_POP pop temp 0
@5
D=A
@0
D=D+A
@13
M=D
@SP
D=M
@256
A=A+D
A=A-1
D=M
@13
A=M
M=D
@SP
M=M-1
//C_CALL call Class1.get
@SP
D=M
@256
D=A+D
@13
M=D
@Class1.get&returnaddr
D=A
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@LCL
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THIS
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THAT
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@LCL
M=D
@0
D=D-A
@5
D=D-A
@ARG
M=D
@Class1.get
0;JMP
(Class1.get&returnaddr)
//C_CALL call Class2.get
@SP
D=M
@256
D=A+D
@13
M=D
@Class2.get&returnaddr
D=A
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@LCL
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@ARG
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THIS
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@13
M=D
@THAT
D=M
@13
A=M
M=D
@SP
M=M+1
D=M
@256
D=A+D
@LCL
M=D
@0
D=D-A
@5
D=D-A
@ARG
M=D
@Class2.get
0;JMP
(Class2.get&returnaddr)
//C_LABEL label WHILE
(Class2.get$WHILE)
//C_GOTO goto WHILE
@Class2.get$WHILE
0;JMP