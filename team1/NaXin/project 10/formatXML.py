# Created by Naxin
# This file is the last part for nand2tetris pro10
import os
import re
import xml.dom.minidom

ops = set(['+','-','*','/','&','|','<','>','='])
unaryops = set(['~','-'])
statements = set(['let','if','while','do','return'])
classvardecs = set(['static','field','var'])

def formatApp(ls,fname):
    formatXml(ls,fname)
    (prefix, fe) = os.path.splitext(fname)

    # read
    xml = open(prefix + '_my.xml', 'r')

    lines = list()
    m1 = re.compile(r'<\?.*')
    m2 = re.compile(r'\s*<\w*List></\w*List>')
    m3 = re.compile(r'(<\w*List>)')
    for line in xml.readlines():
        temp = line.rstrip('\n')
        if m1.match(temp):
            continue
        elif m2.match(temp):
            t = m3.split(temp)
            lines.append(t[0] + t[1])
            lines.append(t[0] + t[2])
        else:lines.append(temp)

    xml.close()

    # write
    xml = open(prefix + '_my.xml', 'w')
    for line in lines:
        xml.write(line + '\n')
    xml.close()

class formatXml:
    def __init__(self, ls, fname):
        (prefix, fe) = os.path.splitext(fname)
        self.xml = open(prefix + '_my.xml', 'w')
        self.ls = ls
        self.doc = xml.dom.minidom.Document()
        self.ind = 0
        self.classDec()

    def __del__(self):
        self.doc.writexml(self.xml, indent='', addindent='  ', newl='\n', encoding='utf-8')
        self.xml.close()

    def addnode(self,root):
        node = self.doc.createElement(self.ls[self.ind][0])
        node.appendChild(self.doc.createTextNode(' ' + self.ls[self.ind][1] + ' '))
        root.appendChild(node)
        self.ind = self.ind + 1

    def classDec(self):
        # 类声明
        while self.ind < len(self.ls):
            root = self.doc.createElement('class')
            self.doc.appendChild(root)
            for i in range(3):
                self.addnode(root)
            while self.ls[self.ind][1] != '}':
                if self.ls[self.ind][1] in classvardecs:
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
        while self.ls[self.ind][1] == ',':
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
        if self.ls[self.ind][1] != ')':
            self.addnode(node)
            self.addnode(node)
            while self.ls[self.ind][1] == ',':
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
        while self.ls[self.ind][1] != '}':
            if self.ls[self.ind][1] == 'var':
                self.varDec(node)
            else: self.statments(node)
        self.addnode(node) # 函数体 }

    def varDec(self,root):
        # 函数变量声明
        node = self.doc.createElement('varDec')
        root.appendChild(node)
        for i in range(3):
            self.addnode(node)
        while self.ls[self.ind][1] == ',':
            self.addnode(node)
            self.addnode(node)
        self.addnode(node) # 输出 ;

    def statments(self,root):
        # 声明
        node = self.doc.createElement('statements')
        root.appendChild(node)
        while self.ls[self.ind][1] in statements:
            if self.ls[self.ind][1] == 'let':
                self.letStatement(node)
            elif self.ls[self.ind][1] == 'if':
                self.ifStatement(node)
            elif self.ls[self.ind][1] == 'while':
                self.whileStatement(node)
            elif self.ls[self.ind][1] == 'do':
                self.doStatement(node)
            elif self.ls[self.ind][1] == 'return':
                self.returnStatement(node)

    # 以下是各种声明
    def letStatement(self,root):
        node = self.doc.createElement('letStatement')
        root.appendChild(node)
        self.addnode(node) # let
        self.addnode(node)  # var
        if self.ls[self.ind][1] == '[':
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
        if self.ls[self.ind][1] == 'else':
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
        if self.ls[self.ind][1] != ';':
            self.expression(node)
        self.addnode(node) # ;

    # 以下是表达式
    def expression(self,root):
        node = self.doc.createElement('expression')
        root.appendChild(node)
        self.term(node)
        while self.ls[self.ind][1] in ops:
            self.addnode(node) # op
            self.term(node)

    def subroutineCall(self,root):
        # no mark
        node = root
        self.addnode(node) # name
        if self.ls[self.ind][1] == '.':
            self.addnode(node) # .
            self.addnode(node) # name
        self.addnode(node) # (
        self.expressionList(node)
        self.addnode(node) # )

    def term(self,root):
        node = self.doc.createElement('term')
        root.appendChild(node)
        if self.ls[self.ind][1] in unaryops:
            self.addnode(node) # op
            self.term(node)
        elif self.ls[self.ind][1] == '(':
            self.addnode(node) # (
            self.expression(node)
            self.addnode(node) # )
        elif self.ls[self.ind + 1][1] == '[':
            self.addnode(node) # var
            self.addnode(node) # [
            self.expression(node)
            self.addnode(node) # ]
        elif self.ls[self.ind + 1][1] == '.' or self.ls[self.ind + 1][1] == '(':
            self.subroutineCall(node)
        else: self.addnode(node) # other

    def expressionList(self,root):
        node = self.doc.createElement('expressionList')
        root.appendChild(node)
        if self.ls[self.ind][1] != ')':
            self.expression(node)
            while self.ls[self.ind][1] == ',':
                self.addnode(node) # ,
                self.expression(node)
        else:
            # 表达式列表为空
            node.appendChild(self.doc.createTextNode(''))