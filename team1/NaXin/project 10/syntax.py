# Created by Naxin

import preTreat
import stringMaking
import outTxml
import formatXML

fnames = preTreat.readFiles()
for fname in fnames:
    a = preTreat.removeComment(fname)
    b = stringMaking.strMaking(a)
    ls = outTxml.outT(b,fname)
    formatXML.formatApp(ls,fname)

