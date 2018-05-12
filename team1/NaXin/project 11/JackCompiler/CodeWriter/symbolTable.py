# Created by NaXin

class VarInfo:
    def __init__(self, scope, type, id):
        self.scope = scope
        self.type = type
        self.id = id


class func:
    def __init__(self, kind, reType):
        self.kind = kind
        self.reType = reType