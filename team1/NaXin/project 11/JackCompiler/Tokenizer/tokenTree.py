# Created by NaXin

import xml.dom.minidom

ops = ('+','-','*','/','&','|','<','>','=')
unaryops = ('~','-')
statements = ('let','if','while','do','return')
classvardecs = ('static','field','var')

class tokenTree:
    def __init__(self, tokenList):
        self.tokenList = tokenList
        self.doc = xml.dom.minidom.Document()
        self.ind = 0
        self.classDec()

    def getTree(self):
        return self.doc

    def addnode(self,root):
        node = self.doc.createElement(self.tokenList[self.ind][0])
        node.appendChild(self.doc.createTextNode(self.tokenList[self.ind][1]))
        root.appendChild(node)
        self.ind = self.ind + 1

    def classDec(self):
        # 类声明
        while self.ind < len(self.tokenList):
            root = self.doc.createElement('class')
            self.doc.appendChild(root)
            for i in range(3):
                self.addnode(root)
            while self.tokenList[self.ind][1] != '}':
                if self.tokenList[self.ind][1] in classvardecs:
                   self.classVarDec(root)
                else: self.subroutineDec(root)
            self.addnode(root) # }

    def classVarDec(self,root):
        # 类变量声明
        node = self.doc.createElement('classVarDec')
        root.appendChild(node)
        # 输出变量声明 如 static int a,b,c,d;
        for i in range(3):
            self.addnode(node)
        while self.tokenList[self.ind][1] == ',':
            self.addnode(node)
            self.addnode(node)
        self.addnode(node)

    def subroutineDec(self,root):
        # 类方法声明
        node = self.doc.createElement('subroutineDec')
        root.appendChild(node)
        # 类似于 function void main {...}
        for i in range(4):
            self.addnode(node)
        self.parameterList(node)
        self.addnode(node)
        self.subroutineBody(node)

    def parameterList(self,root):
        # 参数列表声明
        node = self.doc.createElement('parameterList')
        root.appendChild(node)
        if self.tokenList[self.ind][1] != ')':
            self.addnode(node)
            self.addnode(node)
            while self.tokenList[self.ind][1] == ',':
                for i in range(3):
                    self.addnode(node)
        else:
            # 参数列表唯为空
            node.appendChild(self.doc.createTextNode(''))


    def subroutineBody(self,root):
        # 函数体
        node = self.doc.createElement('subroutineBody')
        root.appendChild(node)
        self.addnode(node) # 函数体第一个 {
        while self.tokenList[self.ind][1] != '}':
            if self.tokenList[self.ind][1] == 'var':
                self.varDec(node)
            else: self.statments(node)
        self.addnode(node) # 函数体 }

    def varDec(self,root):
        # 函数变量声明
        node = self.doc.createElement('varDec')
        root.appendChild(node)
        for i in range(3):
            self.addnode(node)
        while self.tokenList[self.ind][1] == ',':
            self.addnode(node)
            self.addnode(node)
        self.addnode(node) # 输出 ;

    def statments(self,root):
        # 声明
        node = self.doc.createElement('statements')
        root.appendChild(node)
        while self.tokenList[self.ind][1] in statements:
            if self.tokenList[self.ind][1] == 'let':
                self.letStatement(node)
            elif self.tokenList[self.ind][1] == 'if':
                self.ifStatement(node)
            elif self.tokenList[self.ind][1] == 'while':
                self.whileStatement(node)
            elif self.tokenList[self.ind][1] == 'do':
                self.doStatement(node)
            elif self.tokenList[self.ind][1] == 'return':
                self.returnStatement(node)

    # 以下是各种声明
    def letStatement(self,root):
        node = self.doc.createElement('letStatement')
        root.appendChild(node)
        self.addnode(node) # let
        self.addnode(node)  # var
        if self.tokenList[self.ind][1] == '[':
            self.addnode(node) # [
            self.expression(node)
            self.addnode(node) # ]
        self.addnode(node) # =
        self.expression(node)
        self.addnode(node) # ;

    def ifStatement(self,root):
        node = self.doc.createElement('ifStatement')
        root.appendChild(node)
        self.addnode(node) # if
        self.addnode(node) # (
        self.expression(node)
        self.addnode(node) # )
        self.addnode(node) # {
        self.statments(node)
        self.addnode(node) # }
        if self.tokenList[self.ind][1] == 'else':
            self.addnode(node) # else
            self.addnode(node) # {
            self.statments(node)
            self.addnode(node) # }

    def whileStatement(self,root):
        node = self.doc.createElement('whileStatement')
        root.appendChild(node)
        self.addnode(node) # while
        self.addnode(node) # (
        self.expression(node)
        self.addnode(node) # )
        self.addnode(node) # {
        self.statments(node)
        self.addnode(node) # }

    def doStatement(self,root):
        node = self.doc.createElement('doStatement')
        root.appendChild(node)
        self.addnode(node) # do
        self.subroutineCall(node)
        self.addnode(node) # ;

    def returnStatement(self,root):
        node = self.doc.createElement('returnStatement')
        root.appendChild(node)
        self.addnode(node) # return
        if self.tokenList[self.ind][1] != ';':
            self.expression(node)
        self.addnode(node) # ;

    # 以下是表达式
    def expression(self,root):
        node = self.doc.createElement('expression')
        root.appendChild(node)
        self.term(node)
        while self.tokenList[self.ind][1] in ops:
            self.addnode(node) # op
            self.term(node)

    def subroutineCall(self,root):
        # no mark
        node = root
        self.addnode(node) # name
        if self.tokenList[self.ind][1] == '.':
            self.addnode(node) # .
            self.addnode(node) # name
        self.addnode(node) # (
        self.expressionList(node)
        self.addnode(node) # )

    def term(self,root):
        node = self.doc.createElement('term')
        root.appendChild(node)
        if self.tokenList[self.ind][1] in unaryops:
            self.addnode(node) # op
            self.term(node)
        elif self.tokenList[self.ind][1] == '(':
            self.addnode(node) # (
            self.expression(node)
            self.addnode(node) # )
        elif self.tokenList[self.ind + 1][1] == '[':
            self.addnode(node) # var
            self.addnode(node) # [
            self.expression(node)
            self.addnode(node) # ]
        elif self.tokenList[self.ind + 1][1] == '.' or self.tokenList[self.ind + 1][1] == '(':
            self.subroutineCall(node)
        else: self.addnode(node) # other

    def expressionList(self,root):
        node = self.doc.createElement('expressionList')
        root.appendChild(node)
        if self.tokenList[self.ind][1] != ')':
            self.expression(node)
            while self.tokenList[self.ind][1] == ',':
                self.addnode(node) # ,
                self.expression(node)
        else:
            # 表达式列表为空
            node.appendChild(self.doc.createTextNode(''))