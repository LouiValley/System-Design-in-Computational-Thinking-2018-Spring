import string
import re

JACK_TOKENS = {
	'keyword':
				['class', 'constructor', 'function', 'method', 'field', 'static',
				 'var', 'int', 'char', 'boolean', 'void', 'true', 'false', 'null',
				  'this', 'let', 'do', 'if', 'else', 'while', 'return'],

	'symbol':
				['{', '}', '(', ')', '[', ']', '.', ',', ';', '+',
				 '-', '*', '/', '&', '|', '<', '>', '+', '~'],
}

class JackTokenizer(object):
	"""docstring for JackTokenizer"""
	PATH = None
	def __init__(self, filename, PATH):
		self._outfilename = filename + '.xml'
		self._filename = filename + '.jack'
		self._file_object = open(PATH + '\\' + self._filename, 'r')
		self._outfile = open(PATH + '\\' + self._outfilename, 'w')
		self._lines = ['']
		self._tokens = []

	def get_filename(self):
		return self._filename
	
	def first_scan(self):
		"""
		First scan to remove comments
		"""
		
		for line in self._file_object.readlines():
			strip_line = str.strip(line)
			# Eliminating empty lines and line beginning with '//'
			if len(strip_line) == 0 or strip_line[0:2] == '//': 
				continue
			# removing whitespace and getting rid of comment
			white_space_free_line = str.strip(str.split(strip_line, '/')[0], ' ')
			self._lines.append(white_space_free_line)
	
	
	def print_lines(self):
		"""
		Helper function to look at the comment free code
		"""
		for line in self._lines:
			print (line)

	def remove_whitespace(self):
		print('whitespace!')
		for line in self._lines:
			a = line.split(' ')
			for word in a:
				self._tokens.append(word)

		for word in self._tokens:
			print(word)