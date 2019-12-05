#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuffle:
	def __init__(self, arg, LOHI, COUNT, REPEAT):
		self.REPEAT = REPEAT
		self.COUNT = COUNT
		self.lines = []
		if LOHI:
			lowerbound,upperbound = arg[0].split("-")
			l = int(lowerbound)
			u = int(upperbound)
			i = l
			if not self.REPEAT and not COUNT:
				self.COUNT = u-l+1
			while i <= u:
				self.lines.append(str(i)+"\n")
				i = i + 1
		elif len(arg) == 0 or arg[0] == '-':
			self.lines = sys.stdin.readlines()
			self.COUNT = len(self.lines)
			if self.REPEAT and COUNT:
				self.COUNT = COUNT
		else:
			filename = open(arg[0],'r')
			self.lines = filename.readlines()
			filename.close()
			self.COUNT = len(self.lines)
		if not self.REPEAT and COUNT:
			if COUNT <= self.COUNT:
				self.COUNT = int(COUNT)

	def chooseline(self):
		ret = random.choice(self.lines)
		if not self.REPEAT:
			self.lines.remove(ret)
		return ret

	def printout(self):
		i = 0
		if self.REPEAT and not self.COUNT:
			while True:
				sys.stdout.write(self.chooseline())
		else:
			for i in range(int(self.COUNT)):
				sys.stdout.write(self.chooseline())
def main():
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION]... [FILE]
	or:  %prog -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input."""

	parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    
	parser.add_option("-i", "--input-range",
                      action="store_true", dest="LOHI", default=False,
                      help="treat each number LO through HI as an input line")
                      
	parser.add_option("-n", "--headcount",action="store",dest="COUNT",default=False,help="output lines can be repeated")

	parser.add_option("-r", "--repeat",action="store_true", dest="REPEAT", default=False,help="output lines can be repeated")

	options, args = parser.parse_args(sys.argv[1:])
    
	COUNT = None
	if options.COUNT:
		try:
			COUNT = int(options.COUNT)
		except:
			parser.error("invalid line count: {0}".format(COUNT))
		if COUNT < 0:
			parser.error("invalid line count: {0}".format(COUNT))

	if len(args) > 1:
		parser.error("wrong number of operands")	

	if options.LOHI:
		try:
			lowerbound,upperbound = args[0].split("-")
			lowerbound = int(lowerbound)
			upperbound = int(upperbound)
		except:
			parser.error("invalid input range: {0}".format(args[0]))

	try:
		generator = shuffle(args, options.LOHI, options.COUNT, options.REPEAT)
		generator.printout()
	except IOError as e:
		parse.error("I/O error({0}):{1}".format(e.errno,e.strerror))

if __name__ == "__main__":
    main()
