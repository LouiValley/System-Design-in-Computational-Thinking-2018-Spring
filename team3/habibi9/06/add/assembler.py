path1 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/06/add/Add.asm'
#path1 = 'Add.asm'
path2 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/06/add/Out.asm'
in_file = open(path1, 'r')
out_file = open(path2, 'w')

def remove_comment_and_whitespace(str):
	if a:
		s = str.strip().split('/')[0].strip()
		if s:
			return s
		else:
			return False
	else:
		return False;


def determine_command_type(str):
	if str[0] == '@':
		return 'A_COMMAND'
	if str[0] =='(':
		return 'L_COMMAND'
	if ('=' in str):
		return 'C_COMMAND'



a = in_file.readline()
while a:
	if remove_comment_and_whitespace(a):
		print(determine_command_type(remove_comment_and_whitespace(a)))
		#print('\n')
	a = in_file.readline()

