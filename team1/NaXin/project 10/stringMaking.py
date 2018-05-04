# Create by Naxin
# This part does the string part and split the element

def isEmpty(s):
    if s == ' ' or s == '' or s == '\t' or s == '\n':
        return True
    return False

# str is the code without comment
def strMaking(str):
    result = list()
    import re
    m = re.compile(r'"')
    sp = m.split(str)
    m1 = re.compile(r'([\{\}\(\)\[\]\.,;+\-\*/&|<>=~\s])')
    i = 0
    while i < len(sp):
        sp1 = m1.split(sp[i])
        for e1 in sp1:
            if isEmpty(e1):
                continue
            result.append(e1)
        if i < len(sp) - 1:
            result.append('<stringConstant> ' + sp[i+1] + ' </stringConstant>')
        i += 2
    return result