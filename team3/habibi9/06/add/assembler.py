path1 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/06/add/Add.asm'
#path1 = 'Add.asm'
path2 = '/mnt/c/Users/Habib Derbyshire/Documents/Nand2Tetris/System-Design-in-Computational-Thinking-2018-Spring/team3/habibi9/06/add/Out.asm'
in_file = open(path1, 'r')
out_file = open(path2, 'w')
symbols = {'SP': 0, 'LCL': 1, 'ARG': 2, 'THIS': 3, 'THAT': 4, 'R0': 0, 'R1': 1, 'R2': 2, 'R3': 3, 'R4': 4, 'R5': 5, 'R6': 6, 'R7': 7, 'R8': 8, 'R9': 9,'R10': 10, 'R11': 11, 'R12': 12, 'R13': 13, 'R14': 14, 'R15': 15, 'SCREEN': 16384, 'KBD': 24576}

dict['SP'] = 0
dict['LCL'] = 1
dict['ARG'] = 2
dict['THIS'] = 3
dict['THAT'] = 4
dict['R0'] = 0
dict['R1'] = 1
dict['R2'] = 2
dict['R3'] = 3
dict['R4'] = 4
dict['R5'] = 5
dict['R6'] = 6
dict['R7'] = 7
dict['R8'] = 8
dict['R9'] = 9
dict['R10'] = 10
dict['R11'] = 11
dict['R12'] = 12
dict['R13'] = 13
dict['R14'] = 14
dict['R15'] = 15
dict['SCREEN'] = 16384
dict['KBD'] = 24576

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
def determine_dest(str):
	if(determine_command_type(str) == 'C_COMMAND'):
		if('=' in str):
			return str.split('=')[0]
		else:
			return ''

def determine_comp(str):
	if(determine_command_type(str) == 'C_COMMAND'):
		if('=' in str):
			return str.split('=')[1].split(';')[0]
		else:
			return str.split(';')[0]

def determine_jump(str):
	if(determine_command_type(str) == 'C_COMMAND'):
		if(';' in str):
			return str.split(';')[1]
		else:
			return ''


a = in_file.readline()
while a:
	if remove_comment_and_whitespace(a):
		print(determine_command_type(remove_comment_and_whitespace(a)))
		#print('\n')
	a = in_file.readline()

