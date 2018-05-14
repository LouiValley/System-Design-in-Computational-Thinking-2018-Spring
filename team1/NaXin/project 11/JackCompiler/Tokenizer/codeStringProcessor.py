# Created by NaXin
# 此文件提供所有对一整个代码字符串的操作

# 取出代码中的注释
# 此函数输入一个代码段
# 输出一个已经去掉所有注释的代码段
def removeComment(str):
    import re
    result = ''
    m1 = re.compile(r'//.*')
    m2 = re.compile(r'/\*.*?\*/',re.S)
    temp = re.sub(m1, '', str)
    result = re.sub(m2, '', temp)
    return result

# 判断一个字符串是否为空
def isEmpty(s):
    if s == ' ' or s == '' or s == '\t' or s == '\n':
        return True
    return False

# 将一个文件读入
# 设为集合形式
def readAsSet(filename):
    result = set()
    file = open(filename,'r')
    for line in file.readlines():
        result.add(line.rstrip('\n'))
    file.close()
    return result

# 此函数用于处理代码段第一阶段
# 生成一个字元链表(属性+字元 的格式)
# 输入为去掉注释的代码段
# 输出为如上所示字元链表
def tokenLister(str):
    import sys
    import re

    # 读入keywords文件, symbols文件
    keywords = readAsSet(sys.path[0] + '/Tokenizer/keywords')
    symbols = readAsSet(sys.path[0] + '/Tokenizer/symbols')

    result = list()
    stringRe = re.compile(r'"')# 分为字符串
    tokenRe = re.compile(r'([\{\}\(\)\[\]\.,;+\-\*/&|<>=~\s])')# 用于切分字元的字符串
    byString = stringRe.split(str)

    i = 0
    while i < len(byString):
        byToken = tokenRe.split(byString[i])
        for token in byToken:
            # 这里的token必定不含有stringConstant
            if isEmpty(token):
                continue
            if token in keywords:
                result.append(['keyword', token])
            elif token in symbols:
                result.append(['symbol', token])
            elif token.isdigit():
                result.append(['integerConstant', token])
            else:
                result.append(['identifier', token])
        if i < len(byString) - 1:
            result.append(['stringConstant', byString[i+1]])
        i += 2
    return result