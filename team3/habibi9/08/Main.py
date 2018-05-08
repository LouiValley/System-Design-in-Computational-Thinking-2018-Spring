from vm.Parser import Parser
from vm.CodeWriter import CodeWriter

import os
import string

class Main(object):
    
    def __init__(self):
        pass
    
    def run(self):
        PATH = "C:\\Users\\Habib Derbyshire\\Documents\\Nand2Tetris\\System-Design-in-Computational-Thinking-2018-Spring\\team3\\habibi9\\08\\FunctionCalls\\FibonacciElement"
        PATH = os.path.abspath(PATH)
        print('testing!')
        if os.path.isdir(PATH):
            #file_name = str.split(PATH, '\\', 1)[1]
            file_name = PATH
            codeWriter = CodeWriter(PATH=PATH)
            print ('The path is directory ' + PATH)
            codeWriter.set_filename(file_name + '.asm')
            codeWriter.start_up_code()
            vm_files =[f for f in os.listdir(PATH) if f.find('.vm') > 0 ]
            if 'Sys.vm' in vm_files:
                sysindex = vm_files.index('Sys.vm')
                vm_files[0], vm_files[sysindex] = vm_files[sysindex], vm_files[0]
            for file_name in vm_files:
                print (file_name)
                parser = Parser(file_name, PATH)
                parser.first_scan()
                codeWriter.set_parser(parser)
                codeWriter.generate_code()
            codeWriter.terminate_code()
        else:
            print ('The path is file ' + PATH)
            PATH, file_name = str.split(PATH, '\\', 1)
            parser = Parser(file_name, PATH)
            parser.first_scan()
            codeWriter = CodeWriter(PATH=PATH)
            codeWriter.set_parser(parser)
            codeWriter.set_filename(string.split(file_name, '.', 1)[0] + '.asm')
            codeWriter.start_up_code()
            codeWriter.generate_code()
            codeWriter.terminate_code()

def test():
    main = Main()
    main.run()