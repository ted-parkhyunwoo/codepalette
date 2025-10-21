class myClass:
    def __init__(self) -> None:
        pass
    
    def printArgs(self, *args):
        for a in args:
            print(a)
    
    def printKwargs(self, **kwargs):
        for key in kwargs:
            print(key, kwargs[key])

