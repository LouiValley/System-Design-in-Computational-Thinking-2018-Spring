//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@17
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@17
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex0
D;JEQ
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex0
0;JMP
(LogicJumpLabelIndex0)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex0)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@17
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@16
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex1
D;JEQ
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex1
0;JMP
(LogicJumpLabelIndex1)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex1)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@16
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@17
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex2
D;JEQ
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex2
0;JMP
(LogicJumpLabelIndex2)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex2)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@892
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@891
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex3
D;JLT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex3
0;JMP
(LogicJumpLabelIndex3)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex3)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@891
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@892
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex4
D;JLT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex4
0;JMP
(LogicJumpLabelIndex4)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex4)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@891
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@891
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex5
D;JLT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex5
0;JMP
(LogicJumpLabelIndex5)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex5)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32767
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32766
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex6
D;JGT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex6
0;JMP
(LogicJumpLabelIndex6)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex6)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32766
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32767
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex7
D;JGT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex7
0;JMP
(LogicJumpLabelIndex7)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex7)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32766
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@32766
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M-D
@LogicJumpLabelIndex8
D;JGT
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=0
D=A
@ENDOFLogicJumpLabelIndex8
0;JMP
(LogicJumpLabelIndex8)
@SP
D=M
@256
A=A+D
A=A-1
A=A-1
M=-1
D=A
(ENDOFLogicJumpLabelIndex8)
D=D+1
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@57
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@31
D=A
@13
A=M
M=D
@SP
M=M+1
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@53
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=D+M
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@112
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
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
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=-M
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M&D
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_PUSH
@SP
D=M
@256
D=A+D
@13
M=D
@82
D=A
@13
A=M
M=D
@SP
M=M+1
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=M
A=A-1
D=M|D
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
//C_ARITHEMETIC
@SP
D=M
@256
A=A+D
A=A-1
D=!M
M=D
A=A+1
D=A
@256
D=D-A
@SP
M=D
