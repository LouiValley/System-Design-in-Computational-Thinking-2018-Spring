path1 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/07/StackArithmetic/StackTest/StackTest.vm'
path2 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/07/StackArithmetic/StackTest/StackTest.asm'

memseg = {'sp': 0, 'local': 1, 'argument': 2, 'this': 3, 'that': 4, 'constant': 9}

end_counter = 0

def remove_comment_and_whitespace(str):
	if a:
		s = str.strip().split('/')[0].strip()
		if s:
			return s
		else:
			return False
	else:
		return False;

def push(mem, val):
	addr = memseg[mem]
	string = '//push ' + str(mem) + ' ' + str(val) + '\n'
	if(addr != 9):
		string += '@'+str(val)+'\nD=A\n@'+str(addr)+'\nA=A+D\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n'

	else:
		string += '@'+str(val)+'\nD=A\n@0\nA=M\nM=D\n@0\nM=M+1\n'

	return string

def pop(mem, val):
	addr = memseg[mem]
	string = '//pop ' + str(mem) + ' ' + str(val) + '\n'
	string +='@0\nA=M-1\nD=M\n@'+addr+'\n@A=M\n'+('A=A+1\n')*val+'M=D\n'
	return string

def add():
	string = '//add\n'
	string += '@0\nA=M-1\nD=M\nA=A-1\nM=M+D\n@0\nM=M-1\nA=M\nM=0\n'
	return string

def sub():
	string = '//sub\n'
	string += '@0\nA=M-1\nD=M\nA=A-1\nM=M-D\n@0\nM=M-1\nA=M\nM=0\n'
	return string

def gt():
	global end_counter
	string = '//gt\n'
	string += '@0\nA=M-1\nD=M\nM=0\nA=A-1\nD=M-D\n@gt'+str(end_counter)+'\nD; JGT\nM=-1\n@end'+str(end_counter)+'\n0; JMP\n(gt'+str(end_counter)+')\nM=1\n@end'+str(end_counter)+'\n'
	end_counter = end_counter+1
	return string

def lt():
	global end_counter
	string = '//lt\n'
	string += '@0\nA=M-1\nD=M\nM=0\nA=A-1\nD=M-D\n@gt'+str(end_counter)+'\nD; JLT\nM=-1\n@end'+str(end_counter)+'\n0; JMP\n(gt'+str(end_counter)+')\nM=1\n(end'+str(end_counter)+')\n'
	end_counter = end_counter+1
	return string

def eq():
	global end_counter
	string = '//eq\n'
	string += '@0\nA=M-1\nD=M\nM=0\nA=A-1\nD=M-D\n@gt'+str(end_counter)+'\nD; JEQ\nM=-1\n@end'+str(end_counter)+'\n0; JMP\n(gt'+str(end_counter)+')\nM=1\n(end'+str(end_counter)+')\n'
	end_counter = end_counter+1
	return string

def neg():
	string = '//neg\n'
	string += '@0\nA=M-1\nM=-M\n'
	return string

def andop():
	string = '//and\n'
	string += '@0\nA=M-1\nD=M\nA=A-1\nM=M&D\n@0\nM=M-1\nA=M\nM=0\n'
	return string

def orop():
	string = '//or\n'
	string += '@0\nA=M-1\nD=M\nA=A-1\nM=M|D\n@0\nM=M-1\nA=M\nM=0\n'
	return string




in_file = open(path1, 'r')
out_file = open(path2, 'w')
a = in_file.readline()
while a:
	if remove_comment_and_whitespace(a):
		a = remove_comment_and_whitespace(a)
		#print(a)
		if(' ' in a):
			c1 = a.split(' ')[0]
			c2 = a.split(' ')[1]
			c3 = a.split(' ')[2]
			if c1 == 'push':
				out_file.write(push(c2, c3))
			elif c1 == 'pop':
				out_file.write(pop(c2, c3))
		elif a == 'add':
			out_file.write(add())

		elif a == 'sub':
			out_file.write(sub())

		elif a == 'neg':
			out_file.write(neg())

		elif a == 'and':
			out_file.write(andop())

		elif a == 'or':
			out_file.write(orop())

		elif a =='gt':
			out_file.write(gt())

		elif a == 'lt':
			out_file.write(lt())

		elif a =='eq':
			out_file.write(eq())

	a = in_file.readline()