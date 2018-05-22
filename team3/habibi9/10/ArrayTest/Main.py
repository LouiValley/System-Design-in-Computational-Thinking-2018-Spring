from JackTokenizer import JackTokenizer
import os
import string



PATH = "C:\\Users\\Habib Derbyshire\\Documents\\Nand2Tetris\\System-Design-in-Computational-Thinking-2018-Spring\\team3\\habibi9\\10\\ArrayTest"
PATH = os.path.abspath(PATH)

tokenizer = JackTokenizer("Main", PATH)
print(tokenizer.get_filename())
tokenizer.first_scan()
tokenizer.remove_whitespace()
tokenizer.print_lines()
