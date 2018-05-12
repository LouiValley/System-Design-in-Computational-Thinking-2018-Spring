# Created by NaXin
import xml.dom.minidom
from . import symbolTable

# nodeName 名字
# childNodes 子节点
# firstChild.data 值

class VMwriter:
    def __init__(self, xmlTree, func):
        self.doc = xmlTree
        self.resultVM = list()
        self.func = func
        self.classVar = dict()
        self.oper = dict()

        self.staticID = 0
        self.fieldID = 0
        self.countWhile = 0
        self.countIf = -1

        self.oper["+"] = "add"
        self.oper["-"] = "sub"
        self.oper["*"] = "call Math.multiply 2"
        self.oper["/"] = "call Math.divide 2"
        self.oper["&"] = "and"
        self.oper["|"] = "or"
        self.oper["<"] = "lt"
        self.oper[">"] = 'gt'
        self.oper["="] = 'eq'

        # 开始编译
        self.compileClass()

    def getVM(self):
        return self.resultVM

    def compileClass(self):
        root = self.doc.documentElement
        self.className = root.childNodes[1].firstChild.data

        # 编译一个类
        # 即两个部分

        # 编译变量部分
        for child in root.childNodes:
            if child.nodeName == 'classVarDec':
                self.handleClassVar(child)

        for child in root.childNodes:
            if child.nodeName == 'subroutineDec':
                self.handleSubroutine(child)

    # 编译类变量部分
    def handleClassVar(self,root):
        childls = root.childNodes
        i = 0
        Scope = childls[i].firstChild.data
        Type = childls[i+1].firstChild.data
        i+=2
        while True:
            if Scope == 'static':
                self.classVar[childls[i].firstChild.data] = symbolTable.VarInfo(Scope,Type,self.staticID)
                self.staticID += 1
            elif Scope == 'field':
                self.classVar[childls[i].firstChild.data] = symbolTable.VarInfo(Scope,Type,self.fieldID)
                self.fieldID += 1
            else: print('error, Scope is ' + Scope)
            if childls[i+1].firstChild.data == ';':
                i += 2
                break
            i += 2

    # 编译子程序部分
    def handleSubroutine(self,root):
        childls = root.childNodes
        i = 0
        Kind = childls[i].firstChild.data
        ReType = childls[i+1].firstChild.data
        i += 2
        subroutineName = self.className + '.' + childls[i].firstChild.data
        i += 2

        # 到参数列表节点
        # 加入参数
        methodVar = dict()
        if Kind == 'method':
            self.handleParaList(childls[i], methodVar, 1)
        else: self.handleParaList(childls[i], methodVar, 0)
        # print(methodVar)
        i += 2

        # 到函数体部分
        # 函数体的变量声明
        varID = 0
        for node in childls[i].childNodes:
            if node.nodeName == 'varDec':
                varID = self.handleSubVar(node, methodVar, varID)

        # 写出函数名部分的VM代码
        self.resultVM.append('function ' + subroutineName + ' %d'% (varID))
        if Kind == 'method':
            self.resultVM.append('push argument 0')
            self.resultVM.append('pop pointer 0')
        elif Kind == 'constructor':
            self.resultVM.append('push constant %d' % (self.staticID + self.fieldID))
            self.resultVM.append('call Memory.alloc 1')
            self.resultVM.append('pop pointer 0')

        # 函数体声明部分
        currentVar = dict()
        currentVar.update(self.classVar)
        currentVar.update(methodVar)
        for node in childls[i].childNodes:
            if node.nodeName == 'statements':
                self.handleStatements(node,currentVar)

    def handleParaList(self, root, methodVar, arguBegin):
        j = 0
        arguId = arguBegin
        ls = root.childNodes
        if len(ls) < 2: return
        while j < len(ls):
            Type = ls[j].firstChild.data
            methodVar[ls[j+1].firstChild.data] = symbolTable.VarInfo('argument', Type, arguId)
            arguId += 1
            j += 3

    def handleSubVar(self, root, methodVar, currID):
        ls = root.childNodes
        Kind = ls[0].firstChild.data
        Type = ls[1].firstChild.data
        j = 2
        while j < len(ls):
            methodVar[ls[j].firstChild.data] = symbolTable.VarInfo(Kind, Type, currID)
            currID += 1
            j += 2
        return currID

    def handleStatements(self, root, currentVar):
        for node in root.childNodes:
            if node.nodeName == 'letStatement':
                self.handleLetStatement(node,currentVar)
            elif node.nodeName == 'ifStatement':
                self.handleIfStatement(node,currentVar)
            elif node.nodeName == 'whileStatement':
                self.handleWhileStatement(node,currentVar)
            elif node.nodeName == 'doStatement':
                self.handleDoStatement(node,currentVar)
            elif node.nodeName == 'returnStatement':
                self.handleReturnStatement(node,currentVar)
            else: print('error in statement, it is ' + node.nodeName)

    def handleLetStatement(self, root, currentVar):
        childls = root.childNodes
        varName = childls[1].firstChild.data
        varInfo = currentVar[varName]
        if childls[2].firstChild.data == '[':
            self.handleVar(varInfo, 'push')
            self.expression(childls[3],currentVar)
            self.resultVM.append('add')
            self.expression(childls[6], currentVar)

            # 将最终结果放到 name[index] 中去
            self.resultVM.append('pop temp 0')
            self.resultVM.append('pop pointer 1')
            self.resultVM.append('push temp 0')
            self.resultVM.append('pop that 0')
        else:
            self.expression(childls[3], currentVar)
            self.handleVar(varInfo, 'pop')

    def handleIfStatement(self, root, currentVar):
        self.countIf += 1
        tempCountIf = self.countIf
        childls = root.childNodes
        self.expression(childls[2],currentVar)
        if len(childls) >= 10:
            self.resultVM.append('if-goto IF_TRUE%d' % (tempCountIf))
            self.resultVM.append('goto IF_FALSE%d' % (tempCountIf))
            self.resultVM.append('label IF_TRUE%d' % (tempCountIf))
            self.handleStatements(childls[5], currentVar)
            self.resultVM.append('goto IF_END%d' % (tempCountIf))
            self.resultVM.append('label IF_FALSE%d' % (tempCountIf))
            # else 段
            self.handleStatements(childls[9], currentVar)
            self.resultVM.append('label IF_END%d' % (tempCountIf))
        else:
            self.resultVM.append('if-goto IF_TRUE%d' % (tempCountIf))
            self.resultVM.append('goto IF_FALSE%d' % (tempCountIf))
            self.resultVM.append('label IF_TRUE%d' % (tempCountIf))
            self.handleStatements(childls[5], currentVar)
            self.resultVM.append('label IF_FALSE%d' % (tempCountIf))

    def handleWhileStatement(self, root, currentVar):
        self.countWhile += 1
        tempCountWhlie = self.countWhile
        self.resultVM.append('label WHILE_EXP%d' % (tempCountWhlie))
        childls = root.childNodes
        self.expression(childls[2],currentVar)
        self.resultVM.append('not')
        self.resultVM.append('if-goto WHILE_END%d' % (tempCountWhlie))
        self.handleStatements(childls[5],currentVar)
        self.resultVM.append('goto WHILE_EXP%d' % (tempCountWhlie))
        self.resultVM.append('label WHILE_END%d' % (tempCountWhlie))

    def handleDoStatement(self, root, currentVar):
        childls = root.childNodes
        argumentNum = 0
        if childls[2].firstChild.data != '.':
            subroutineName = self.className + '.' + childls[1].firstChild.data
            funInfo = self.func[subroutineName]
            if self.func[subroutineName].kind == 'method':
                self.resultVM.append('push pointer 0')
                argumentNum += 1
            argumentNum += self.expressionList(childls[3], currentVar)
        else:
            varName = childls[1].firstChild.data
            if currentVar.__contains__(varName):
                # 是一个变量
                varInfo = currentVar[varName]
                subroutineName = varInfo.type + '.' + childls[3].firstChild.data
                funInfo = self.func[subroutineName]
                if funInfo.kind == 'method':
                    self.handleVar(varInfo,'push')
                    argumentNum += 1
            else:
                subroutineName = varName + '.' + childls[3].firstChild.data
                funInfo = self.func[subroutineName]
            argumentNum += self.expressionList(childls[5], currentVar)

        self.resultVM.append('call ' + subroutineName + ' %d' % (argumentNum))
        if funInfo.reType == 'void':
            self.resultVM.append('pop temp 0')

    def handleReturnStatement(self, root, currentVar):
        childls = root.childNodes
        if childls[1].nodeName == 'expression':
            self.expression(childls[1], currentVar)
        else:
            self.resultVM.append('push constant 0')
        self.resultVM.append('return')

    def expressionList(self, root, currentVar):
        childls = root.childNodes
        expNum = 0
        for child in childls:
            if child.nodeName == 'expression':
                expNum += 1
                self.expression(child,currentVar)
        return expNum

    def expression(self, root, currentVar):
        childls = root.childNodes
        i = 0
        while i < len(childls):
            if childls[i].nodeName == 'term':
                self.term(childls[i], currentVar)
                i += 1
            elif childls[i].nodeName == 'symbol':
                self.term(childls[i+1], currentVar)
                self.resultVM.append(self.oper[childls[i].firstChild.data])
                i += 2
            else: print('error in expression, it is ' + childls[i].nodeName)

    def term(self,root, currentVar):
        childls = root.childNodes
        node = childls[0]
        if node.nodeName == 'integerConstant':
            self.resultVM.append('push constant %d' % (int(node.firstChild.data)))
        elif node.nodeName == 'stringConstant':
            str = node.firstChild.data
            self.resultVM.append('push constant %d'%(len(str)))
            self.resultVM.append('call String.new 1')
            for i in str:
                self.resultVM.append('push constant %d'%(ord(i)))
                self.resultVM.append('call String.appendChar 2')
        elif node.nodeName == 'keyword':
            if node.firstChild.data == 'this':
                self.resultVM.append('push pointer 0')
            elif node.firstChild.data == 'true':
                self.resultVM.append('push constant 0')
                self.resultVM.append('not')
            elif node.firstChild.data == 'false' or node.firstChild.data == 'null':
                self.resultVM.append('push constant 0')
            else:
                print('error in term-keyword, it is ' + node.firstChild.data)
        elif node.nodeName == 'identifier':
            if len(childls) == 1:
                varName = node.firstChild.data
                varInfo = currentVar[varName]
                self.handleVar(varInfo, 'push')
            elif childls[1].firstChild.data == '[':
                varName = node.firstChild.data
                varInfo = currentVar[varName]
                self.handleVar(varInfo, 'push')
                self.expression(childls[2],currentVar)
                self.resultVM.append('add')
                self.resultVM.append('pop pointer 1')
                self.resultVM.append('push that 0')
            elif len(childls) > 1:
                self.subtoutineCall(root, currentVar)
        elif node.nodeName == 'symbol':
            if node.firstChild.data == '-':
                self.term(childls[1],currentVar)
                self.resultVM.append('neg')
            elif node.firstChild.data == '~':
                self.term(childls[1],currentVar)
                self.resultVM.append('not')
            elif node.firstChild.data == '(':
                self.expression(childls[1],currentVar)
        else:
            print('error in term, name is ' + node.nodeName)

    def subtoutineCall(self, root, currentVar):
        childls = root.childNodes
        argumentNum = 0
        if childls[1].firstChild.data != '.':
            subroutineName = self.className + '.' + childls[0].firstChild.data
            funInfo = self.func[subroutineName]
            if funInfo.kind == 'method':
                self.resultVM.append('push pointer 0')
                argumentNum += 1
            argumentNum += self.expressionList(childls[2], currentVar)
        else:
            varName = childls[0].firstChild.data
            if currentVar.__contains__(varName):
                # 是一个变量
                varInfo = currentVar[varName]
                subroutineName = varInfo.type + '.' + childls[2].firstChild.data
                funInfo = self.func[subroutineName]
                if funInfo.kind == 'method':
                    self.handleVar(varInfo, 'push')
                    argumentNum += 1
            else:
                subroutineName = varName + '.' + childls[2].firstChild.data
                funInfo = self.func[subroutineName]
            argumentNum += self.expressionList(childls[4], currentVar)

        self.resultVM.append('call ' + subroutineName + ' %d' % (argumentNum))
        if funInfo.reType == 'void':
            self.resultVM.append('pop temp 0')

    # dist can be push or pop
    def handleVar(self, varInfo, dist):
        if varInfo.scope == 'static':
            self.resultVM.append(dist + ' static %d' % (varInfo.id))
        elif varInfo.scope == 'field':
            self.resultVM.append(dist + ' this %d' % (varInfo.id))
        elif varInfo.scope == 'var':
            self.resultVM.append(dist + ' local %d' % (varInfo.id))
        elif varInfo.scope == 'argument':
            self.resultVM.append(dist + ' argument %d' % (varInfo.id))
        else:
            print('error in let, it is ' + varInfo.scope)