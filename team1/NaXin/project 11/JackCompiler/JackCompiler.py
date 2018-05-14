# Created by NaXin

from Tokenizer import fileAPI
from Tokenizer import codeStringProcessor
from Tokenizer import tokenTree
from CodeWriter import CodeWriterApp

fileNameList = fileAPI.getFileNames()
treeList = list()
for fileName in fileNameList:
    # 读文件并去掉注释
    code = codeStringProcessor.removeComment(fileAPI.readFile(fileName))
    # 产生属性+字元的链表
    TokenList = codeStringProcessor.tokenLister(code)
    # 写入Txml文件
    fileAPI.writeTxml(TokenList,fileName)
    # 获取xml树
    tree = tokenTree.tokenTree(TokenList).getTree()
    # 写入xml文件
    fileAPI.wrtieXML(tree,fileName)
    treeList.append(tree)

CodeWriterApp.codeWriterApp(treeList, fileNameList)
    # root = tree.documentElement
    # for node in root.childNodes:
    #     print(node)
