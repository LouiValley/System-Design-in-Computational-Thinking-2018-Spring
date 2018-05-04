# Created by Naxin
# This file is used to output the TXML file for jack

import re
import sys

keywords = set()
keyw = open(sys.path[0]  + '/keywords','r')
for line in keyw.readlines():
    keywords.add(line.rstrip('\n'))
keyw.close()

symbols = set()
symb = open(sys.path[0]  + '/symbols','r')
for line in symb.readlines():
    symbols.add(line.rstrip('\n'))
symb.close()

def outT(ls,fname):
    import os
    result = list()
    (prefix, fe) = os.path.splitext(fname)
    txml = open(prefix + 'T_my.xml','w')
    txml.write('<tokens>\n')
    for e in ls:
        if e in keywords:
            result.append(['keyword',e])
            txml.write('<keyword> ' + e + ' </keyword>\n')
        elif e in symbols:
            result.append(['symbol',e])
            if e == '<':
                temp = '&lt;'
            elif e == '>':
                temp = '&gt;'
            elif e == '&':
                temp = '&amp;'
            else: temp = e
            txml.write('<symbol> ' + temp + ' </symbol>\n')
        elif e.isdigit():
            result.append(['integerConstant',e])
            txml.write('<integerConstant> ' + e + ' </integerConstant>\n')
        elif re.match(r'<stringConstant>',e):
            temp = re.sub(r'<stringConstant>[ ]', '', e)
            temp = re.sub(r'[ ]</stringConstant>', '', temp)
            result.append(['stringConstant',temp])
            txml.write(e + '\n')
        else:
            result.append(['identifier',e])
            txml.write('<identifier> ' + e + ' </identifier>\n')
    txml.write('</tokens>\n')
    txml.close()
    return result