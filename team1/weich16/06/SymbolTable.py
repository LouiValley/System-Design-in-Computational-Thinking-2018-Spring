class symboltable:
    def __init__(self):
        self.count = 16
        self.dict = {}
        self.dict['SP'] = 0
        self.dict['LCL'] = 1
        self.dict['ARG'] = 2
        self.dict['THIS'] = 3
        self.dict['THAT'] = 4
        self.dict['R0'] = 0
        self.dict['R1'] = 1
        self.dict['R2'] = 2
        self.dict['R3'] = 3
        self.dict['R4'] = 4
        self.dict['R5'] = 5
        self.dict['R6'] = 6
        self.dict['R7'] = 7
        self.dict['R8'] = 8
        self.dict['R9'] = 9
        self.dict['R10'] = 10
        self.dict['R11'] = 11
        self.dict['R12'] = 12
        self.dict['R13'] = 13
        self.dict['R14'] = 14
        self.dict['R15'] = 15
        self.dict['SCREEN'] = 16384
        self.dict['KBD'] = 24576

    def addEntry_A(self,syb):
        self.dict[syb] = self.count
        self.count += 1

    def addEntry_L(self,syb,count):
        self.dict[syb] = count

    def contains(self,cmp):
        if cmp in list(self.dict.keys()): return True
        else: return False

    def GetAddress(self,syb):
        return self.dict[syb]

    def symbols(self):
        return list(self.dict.keys())
