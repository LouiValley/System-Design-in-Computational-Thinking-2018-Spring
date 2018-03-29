import Parser
import Code
import SymbolTable

def binary(num,N):
    return bin(num)[2:].zfill(N)

def main():
    file = input('Please input your filename:')
    mypsr = Parser.parser(file)
    mytab = SymbolTable.symboltable()
    mycode = Code.code()

    lc_list = []
    while mypsr.flag:
        mypsr.advance()
        if mypsr.flag:
            if mypsr.commandType() == 'L_COMMAND':
                lc_list.append(mypsr.symbol())

    mypsr.fp = open(file,'r')
    mypsr.flag = True
    while mypsr.flag:
        mypsr.advance()
        if mypsr.flag:
            if mypsr.commandType() != 'L_COMMAND': mypsr.count += 1
            if (mypsr.commandType() == 'A_COMMAND') and (mypsr.symbol() not in lc_list) \
                    and (not mypsr.symbol().isdigit()) and (mypsr.symbol() not in mytab.symbols()):
                    mytab.addEntry_A(mypsr.symbol())
            if (mypsr.commandType() == 'L_COMMAND'):
                mytab.addEntry_L(mypsr.symbol(),mypsr.count)

    mypsr.fp = open(file,'r')
    mypsr.flag = True
    while mypsr.flag:
        mypsr.advance()
        if mypsr.flag:
            if mypsr.commandType() == 'A_COMMAND':
                if mypsr.symbol().isdigit(): add = int(mypsr.symbol())
                else:add = mytab.dict[mypsr.symbol()]
                ins = '0'+binary(add,15)
                mypsr.fw.write(ins+'\n')
            elif mypsr.commandType() == 'C_COMMAND':
                ins = '111' + \
                      mycode.comp(mypsr.comp()) \
                      + mycode.dest(mypsr.dest()) \
                      + mycode.jump(mypsr.jump())
                mypsr.fw.write(ins+'\n')
            else: continue

    mypsr.fp.close()
    mypsr.fw.close()
    return 0

if __name__ == '__main__':
    main()