(BEGIN)
@KBD       //���̻���ַ�Ƿ���ֵ��û�о���ת������
D = M
@CLEAN
D;JEQ
                  //�м�����
@SCREEN          //Ϳ�� 
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

(CLEAN)          //�޼��̰��� 

@SCREEN          //Ϳ�� 
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