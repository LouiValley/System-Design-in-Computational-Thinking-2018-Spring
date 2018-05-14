# Created by NaXin
from . import symbolTable
from . import VMwriter
from Tokenizer import fileAPI

func = dict()

def codeWriterApp(treeList, filenNameList):
    funcAPIadd()
    for tree in treeList:
        getFunc(tree)
    # for key in func:
    #     print(key)
    # print(func['Main.fillMemory'].reType)
    for i in range(len(treeList)):
        tree = treeList[i]
        VM = VMwriter.VMwriter(tree,func).getVM()
        fileAPI.writeVM(VM,filenNameList[i])

def getFunc(tree):
    root = tree.documentElement
    className = root.childNodes[1].firstChild.data

    # 记录所有的函数
    for child in root.childNodes:
        if child.nodeName == 'subroutineDec':
            childls = child.childNodes
            i = 0
            Kind = childls[i].firstChild.data
            ReType = childls[i + 1].firstChild.data
            i += 2
            subroutineName = childls[i].firstChild.data
            func[className + '.' + subroutineName] = symbolTable.func(Kind,ReType)

def funcAPIadd():
    func['Math.init'] = symbolTable.func('function', 'void')
    func['Math.abs'] = symbolTable.func('function', 'int')
    func['Math.multiply'] = symbolTable.func('function', 'int')
    func['Math.divide'] = symbolTable.func('function', 'int')
    func['Math.min'] = symbolTable.func('function', 'int')
    func['Math.max'] = symbolTable.func('function', 'int')
    func['Math.sqrt'] = symbolTable.func('function', 'int')
    func['String.new'] = symbolTable.func('constructor', 'String')
    func['String.dispose'] = symbolTable.func('method', 'int')
    func['String.length'] = symbolTable.func('method', 'int')
    func['String.charAt'] = symbolTable.func('method', 'char')
    func['String.setCharAt'] = symbolTable.func('method', 'void')
    func['String.appendChar'] = symbolTable.func('method', 'String')
    func['String.eraseLastChar'] = symbolTable.func('method', 'void')
    func['String.intValue'] = symbolTable.func('method', 'int')
    func['String.setInt'] = symbolTable.func('method', 'void')
    func['String.backSpace'] = symbolTable.func('function', 'char')
    func['String.doubleQuote'] = symbolTable.func('function', 'char')
    func['String.newLine'] = symbolTable.func('function', 'char')
    func['Array.new'] = symbolTable.func('function', 'Array')
    func['Array.dispose'] = symbolTable.func('method', 'void')
    func['Output.init'] = symbolTable.func('function', 'void')
    func['Output.moveCursor'] = symbolTable.func('function', 'void')
    func['Output.printChar'] = symbolTable.func('function', 'void')
    func['Output.printString'] = symbolTable.func('function', 'void')
    func['Output.printInt'] = symbolTable.func('function', 'void')
    func['Output.println'] = symbolTable.func('function', 'void')
    func['Output.backSpace'] = symbolTable.func('function', 'void')
    func['Screen.init'] = symbolTable.func('function', 'void')
    func['Screen.clearScreen'] = symbolTable.func('function', 'void')
    func['Screen.setColor'] = symbolTable.func('function', 'void')
    func['Screen.drawPixel'] = symbolTable.func('function', 'void')
    func['Screen.drawLine'] = symbolTable.func('function', 'void')
    func['Screen.drawRectangle'] = symbolTable.func('function', 'void')
    func['Screen.drawCircle'] = symbolTable.func('function', 'void')
    func['Keyboard.init'] = symbolTable.func('function', 'void')
    func['Keyboard.keyPressed'] = symbolTable.func('function', 'char')
    func['Keyboard.readChar'] = symbolTable.func('function', 'char')
    func['Keyboard.readLine'] = symbolTable.func('function', 'String')
    func['Keyboard.readInt'] = symbolTable.func('function', 'int')
    func['Memory.init'] = symbolTable.func('function', 'void')
    func['Memory.peek'] = symbolTable.func('function', 'int')
    func['Memory.poke'] = symbolTable.func('function', 'void')
    func['Memory.alloc'] = symbolTable.func('function', 'Array')
    func['Memory.deAlloc'] = symbolTable.func('function', 'void')
    func['Sys.init'] = symbolTable.func('function', 'void')
    func['Sys.halt'] = symbolTable.func('function', 'void')
    func['Sys.error'] = symbolTable.func('function', 'void')
    func['Sys.wait'] = symbolTable.func('function', 'void')