(BEGIN)
@KBD       //键盘基地址是否有值，没有就跳转到清屏
D = M
@CLEAN
D;JEQ
                  //有键按下
@SCREEN          //涂黑 
D = A
M = 1
@1
D=D+A
A=D
M=1
@2
D=D+A
A=D
M=1

@END
0;JMP

(CLEAN)          //无键盘按下 

@SCREEN          //涂白 
D = A
M = 0
@1
D=D+A
A=D
M=0
@2
D=D+A
A=D
M=0
(END)
@BEGIN
0;JMP