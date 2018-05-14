# Created by NaXin
# 此文件是Jackcomplier的文件处理部分，对外部文件输入输出提供接口

import os
import sys
import xml.dom.minidom
import re

# 从参数读入文件或路径
# 返回一个要打开的文件名称列表
def getFileNames():
    if len(sys.argv) < 2:
        raise RuntimeError('arguments not enough')
        return
    result = list()
    path = sys.argv[1]
    import os
    if os.path.isdir(path):
        filelist = os.listdir(path)
        for i in range(0,len(filelist)):
            chpath = os.path.join(path,filelist[i])
            if os.path.isfile(chpath):
                (fname,fexten) = os.path.splitext(chpath)
                if fexten == '.jack':
                    result.append(chpath)
    else:
        (fname,fexten) = os.path.splitext(path)
        if fexten == '.jack':
            result.append(path)
    return result

# 读入一个文件
# 输入文件名
# 输出全部字符串
def readFile(fname):
    file = open(fname, 'r')
    str = file.read()
    file.close()
    return str

# 此为处理文件的第二阶段
# 写以 _T_my 结尾的xml文件
# 输入tokenList为属性 + 字元 的链表
def writeTxml(tokenList,fname):
    import os

    (prefix, fe) = os.path.splitext(fname)
    Txml = open(prefix + 'T_my.xml','w')
    Txml.write('<tokens>\n')
    for attrToken in tokenList:
        if attrToken[0] == 'symbol':
            if attrToken[1] == '<':
                ele = '&lt;'
            elif attrToken[1] == '>':
                ele = '&gt;'
            elif attrToken[1] == '&':
                ele = '&amp;'
            else: ele = attrToken[1]
            Txml.write('<' + attrToken[0] + '> ' + ele + ' </' + attrToken[0] + '>\n')
        else:
            Txml.write('<' + attrToken[0] + '> ' + attrToken[1] + ' </' + attrToken[0] + '>\n')
    Txml.write('</tokens>')
    Txml.close()

# 将xml格式化，为project10专门做的。。
def wrtieXML(xmldoc, fname):
    (prefix, fe) = os.path.splitext(fname)
    xmlFile = open(prefix + '_my.xml', 'w')
    xmldoc.writexml(xmlFile, indent='', addindent='  ', newl='\n', encoding='utf-8')
    xmlFile.close()

    xmlFile = open(prefix + '_my.xml', 'r')
    lines = list()
    # 匹配第一行注释
    m1 = re.compile(r'<\?.*')
    # 匹配空链表的情况
    m2 = re.compile(r'\s*<\w*List></\w*List>')
    m3 = re.compile(r'(<\w*List>)')
    # 匹配有text的情况
    m4 = re.compile(r'\s*<\w+>.+</\w+>')
    for line in xmlFile.readlines():
        temp = line.rstrip('\n')
        if m1.match(temp):# 注释
            continue
        elif m2.match(temp):# 空表
            t = m3.split(temp)
            lines.append(t[0] + t[1])
            lines.append(t[0] + t[2])
        elif m4.match(temp):# 有内容
            m5 = re.compile(r'([<>])')
            t = m5.split(temp)
            lines.append(t[0] + t[1] + t[2] + t[3] + ' ' + t[4] + ' ' + t[5] + t[6] + t[7])
        else:lines.append(temp)
    xmlFile.close()

    # write
    xmlFile = open(prefix + '_my.xml', 'w')
    for line in lines:
        xmlFile.write(line + '\n')
    xmlFile.close()

# 写VM文件
def writeVM(list, fname):
    (prefix, fe) = os.path.splitext(fname)
    VMfile = open(prefix + '.vm','w')
    for line in list:
        VMfile.write(line + '\n')
    VMfile.close()