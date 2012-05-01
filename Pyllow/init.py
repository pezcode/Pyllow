import sys
import ollyapi

class PyllowOutFile:
	"""
	Dummy file-like class that receives stout and stderr
	and prints to the Olly log window
	"""
	
	# Possible color values
	Black = 0
	Red   = 1
	
	def __init__(self, color):
		self.color = color
		self.buf   = ''
	
	def write(self, text):
		# Addtolist doesn't handle newlines
		lines = text.split('\n')
		for l in lines[:-1]:
			ollyapi.Addtolist(0, self.color, self.buf + l)
			self.buf = ''
		self.buf = self.buf + lines[-1]

def init_environment():
	sys.stdout = PyllowOutFile(PyllowOutFile.Black)
	sys.stderr = PyllowOutFile(PyllowOutFile.Red)
	sys.argv = ['']
	sys.path.append(ollyapi._plugindir + '/Pyllow')

def print_test():
	print('\nprint test\nhehe\n')
	print('x', end='')
	print('y', end='')
	print('z')
	print('error test', file=sys.stderr)

init_environment()
print_test()
