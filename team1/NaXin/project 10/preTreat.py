# Created by NaXin

import sys

def readFiles():
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

def removeComment(fname):
    import re
    result = ''
    file = open(fname,'r')
    str = file.read()
    m1 = re.compile(r'//.*')
    m2 = re.compile(r'/\*.*?\*/',re.S)
    otemp = re.sub(m1, '', str)
    result = re.sub(m2, '', otemp)
    file.close()
    return result