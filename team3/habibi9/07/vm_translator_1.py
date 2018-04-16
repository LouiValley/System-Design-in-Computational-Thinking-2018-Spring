path1 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/Software/projects/07/StackArithmetic/SimpleAdd/SimpleAdd.vm'

memseg = {'sp': 0, 'local': 1, 'argument': 2, 'this': 3, 'that': 4, 'constant': 9}

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
	if(addr != 'constant'):
		string = '@'+str(val)+'\nD=A\n@'+str(addr)+'\nA=A+D\nD=M\n@0\nA=M\nM=D\n@0\nM=M+1\n'

	else:
		string = '@'+str(val)+'\nD=A\n@0\nA=M\nM=D\n@0\nM=M+1'

	return string

def pop(mem, val):
	addr = memseg[mem]
	@val
	D=A
	@addr
	D=A+D

	@0
	A=M
	D=M

	

in_file = open(path1, 'r')
a = in_file.readline()
while a:
	if remove_comment_and_whitespace(a):
		a = remove_comment_and_whitespace(a)
		#print(a)
		if(' ' in a):
			c1 = a.split(' ')[0]
			c2 = a.split(' ')[1]
			c3 = a.split(' ')[2]
			print(push(c2, c3))
		else:
			c1 = a
			c2 = ''
			c3 = ''
		print(c1+','+c2+','+c3)

	a = in_file.readline()