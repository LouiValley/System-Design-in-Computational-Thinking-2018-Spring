class code:
    #def __init__(self):
    def dest(self,ins):
        if ins == '': return '000'
        if ins == 'M': return '001'
        if ins == 'D': return '010'
        if ins == 'MD': return '011'
        if ins == 'A': return '100'
        if ins == 'AM': return '101'
        if ins == 'AD': return '110'
        if ins == 'AMD': return '111'

    def comp(self,ins):
        if ins == '0': return '0101010'
        if ins == '1': return '0111111'
        if ins == '-1': return '0111010'
        if ins == 'D': return '0001100'
        if ins == 'A': return '0110000'
        if ins == '!D': return '0001101'
        if ins == '!A': return '0110001'
        if ins == '-D': return '0001111'
        if ins == '-A': return '0110011'
        if ins == 'D+1': return '0011111'
        if ins == 'A+1': return '0110111'
        if ins == 'D-1': return '0001110'
        if ins == 'A-1': return '0110010'
        if ins == 'D+A': return '0000010'
        if ins == 'D-A': return '0010011'
        if ins == 'A-D': return '0000111'
        if ins == 'D&A': return '0000000'
        if ins == 'D|A': return '0010101'
        if ins == 'M': return '1110000'
        if ins == '!M': return '1110001'
        if ins == '-M': return '1110011'
        if ins == 'M+1': return '1110111'
        if ins == 'M-1': return '1110010'
        if ins == 'D+M': return '1000010'
        if ins == 'D-M': return '1010011'
        if ins == 'M-D': return '1000111'
        if ins == 'D&M': return '1000000'
        if ins == 'D|M': return '1010101'

    def jump(self,ins):
        if ins == '': return '000'
        if ins == 'JGT': return '001'
        if ins == 'JEQ': return '010'
        if ins == 'JGE': return '011'
        if ins == 'JLT': return '100'
        if ins == 'JNE': return '101'
        if ins == 'JLE': return '110'
        if ins == 'JMP': return '111'

