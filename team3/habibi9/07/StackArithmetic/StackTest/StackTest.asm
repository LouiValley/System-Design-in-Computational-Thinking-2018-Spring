//push constant 17
@17
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 17
@17
D=A
@0
A=M
M=D
@0
M=M+1
//eq
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt0
D; JEQ
M=-1
@end0
0; JMP
(gt0)
M=1
(end0)
//push constant 17
@17
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 16
@16
D=A
@0
A=M
M=D
@0
M=M+1
//eq
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt1
D; JEQ
M=-1
@end1
0; JMP
(gt1)
M=1
(end1)
//push constant 16
@16
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 17
@17
D=A
@0
A=M
M=D
@0
M=M+1
//eq
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt2
D; JEQ
M=-1
@end2
0; JMP
(gt2)
M=1
(end2)
//push constant 892
@892
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 891
@891
D=A
@0
A=M
M=D
@0
M=M+1
//lt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt3
D; JLT
M=-1
@end3
0; JMP
(gt3)
M=1
(end3)
//push constant 891
@891
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 892
@892
D=A
@0
A=M
M=D
@0
M=M+1
//lt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt4
D; JLT
M=-1
@end4
0; JMP
(gt4)
M=1
(end4)
//push constant 891
@891
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 891
@891
D=A
@0
A=M
M=D
@0
M=M+1
//lt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt5
D; JLT
M=-1
@end5
0; JMP
(gt5)
M=1
(end5)
//push constant 32767
@32767
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 32766
@32766
D=A
@0
A=M
M=D
@0
M=M+1
//gt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt6
D; JGT
M=-1
@end6
0; JMP
(gt6)
M=1
@end6
//push constant 32766
@32766
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 32767
@32767
D=A
@0
A=M
M=D
@0
M=M+1
//gt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt7
D; JGT
M=-1
@end7
0; JMP
(gt7)
M=1
@end7
//push constant 32766
@32766
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 32766
@32766
D=A
@0
A=M
M=D
@0
M=M+1
//gt
@0
A=M-1
D=M
M=0
A=A-1
D=M-D
@gt8
D; JGT
M=-1
@end8
0; JMP
(gt8)
M=1
@end8
//push constant 57
@57
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 31
@31
D=A
@0
A=M
M=D
@0
M=M+1
//push constant 53
@53
D=A
@0
A=M
M=D
@0
M=M+1
//add
@0
A=M-1
D=M
A=A-1
M=M+D
@0
M=M-1
A=M
M=0
//push constant 112
@112
D=A
@0
A=M
M=D
@0
M=M+1
//sub
@0
A=M-1
D=M
A=A-1
M=M-D
@0
M=M-1
A=M
M=0
//neg
@0
A=M-1
M=-M
//and
@0
A=M-1
D=M
A=A-1
M=M&D
@0
M=M-1
A=M
M=0
//push constant 82
@82
D=A
@0
A=M
M=D
@0
M=M+1
//or
@0
A=M-1
D=M
A=A-1
M=M|D
@0
M=M-1
A=M
M=0
