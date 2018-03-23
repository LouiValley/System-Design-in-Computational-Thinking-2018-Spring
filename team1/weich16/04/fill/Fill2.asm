(BEGIN)  

@KBD  
D = M  
@CLEAN  
D;JEQ  

@SCREEN          //涂黑   
D = A  
@Bcount  
A = M + D  
M = -1  

@Bcount          //键盘按下  
M = M + 1  
D = M  
@8192            //8K  
D = D - A  
@Bcount  
M = D  
@END  
D;JGE  
@8192  
D = D + A  
@Bcount  
M = D  
@END  
0;JMP  

(CLEAN)          //无键盘按下   

@SCREEN          //涂白   
D = A  
@Wcount  
A = M + D  
M = 0  

@Wcount          //键盘按下  
M = M + 1  
D = M  
@8192            //8K  
D = D - A  
@Wcount  
M = D  
@END  
D;JGE  
@8192  
D = D + A  
@Wcount  
M = D  

(END)  
@BEGIN  
0;JMP  