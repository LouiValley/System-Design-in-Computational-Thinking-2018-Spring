class parser:
    def __init__(self,file):
        self.fp = open(file, 'r')
        self.filename = file.strip().split('.')[0]
        self.fw = open(self.filename + '.hack', 'w')
        self.flag = True
        self.count = 0

    def hasMoreCommands(self):
        self.line = self.fp.readline()
        if self.line :return True
        else:
            self.flag = False
            return False

    def advance(self):
        if self.hasMoreCommands():
            self.cur = self.line.strip().split('/')[0].strip()
            while len(self.cur)== 0 or self.cur[0] == '/': self.advance()

    def commandType(self):
        if self.cur[0] == '@':return 'A_COMMAND'
        if self.cur[0] == '(':return 'L_COMMAND'
        if ('=' in self.cur) or (';' in self.cur):return 'C_COMMAND'

    def symbol(self):
        if self.commandType() == 'A_COMMAND':return self.cur[1:]
        if self.commandType() == 'L_COMMAND':return self.cur[1:-1]

    def dest(self):
        if self.commandType() == 'C_COMMAND':
            if '=' in self.cur: return self.cur.split('=')[0]
            else:return ''

    def comp(self):
        if self.commandType() == 'C_COMMAND':
            if '=' in self.cur: return self.cur.split('=')[1].split(';')[0]
            else:return self.cur.split(';')[0]

    def jump(self):
        if self.commandType() == 'C_COMMAND':
            if ';' in self.cur: return self.cur.split(';')[1]
            else:return ''