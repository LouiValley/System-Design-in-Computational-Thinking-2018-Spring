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

def determine_symbol(str):
	if determine_command_type(str) == 'A_COMMAND':
		return str[1:]
	if determine_command_type(str) == 'L_COMMAND':
		return str[1:-1]


def dest_code(inst):
	if inst == '': return '000'
	if inst == 'M': return '001'
	if inst == 'D': return '010'
	if inst == 'MD': return '011'
	if inst == 'A': return '100'
	if inst == 'AM': return '101'
	if inst == 'AD': return '110'
	if inst == 'AMD': return '111'

def comp_code(self,inst):
	if inst == '0': return '0101010'
	if inst == '1': return '0111111'
	if inst == '-1': return '0111010'
	if inst == 'D': return '0001100'
	if inst == 'A': return '0110000'
	if inst == '!D': return '0001101'
	if inst == '!A': return '0110001'
	if inst == '-D': return '0001111'
	if inst == '-A': return '0110011'
	if inst == 'D+1': return '0011111'
	if inst == 'A+1': return '0110111'
	if inst == 'D-1': return '0001110'
	if inst == 'A-1': return '0110010'
	if inst == 'D+A': return '0000010'
	if inst == 'D-A': return '0010011'
	if inst == 'A-D': return '0000111'
	if inst == 'D&A': return '0000000'
	if inst == 'D|A': return '0010101'
	if inst == 'M': return '1110000'
	if inst == '!M': return '1110001'
	if inst == '-M': return '1110011'
	if inst == 'M+1': return '1110111'
	if inst == 'M-1': return '1110010'
	if inst == 'D+M': return '1000010'
	if inst == 'D-M': return '1010011'
	if inst == 'M-D': return '1000111'
	if inst == 'D&M': return '1000000'
	if inst == 'D|M': return '1010101'

def jump_code(self,inst):
	if inst == '': return '000'
	if inst == 'JGT': return '001'
	if inst == 'JEQ': return '010'
	if inst == 'JGE': return '011'
	if inst == 'JLT': return '100'
	if inst == 'JNE': return '101'
	if inst == 'JLE': return '110'
	if inst == 'JMP': return '111'


location_list = []


a = in_file.readline()
while a:
	if remove_comment_and_whitespace(a):
		print(determine_command_type(remove_comment_and_whitespace(a)))
		#print('\n')
	a = in_file.readline()

