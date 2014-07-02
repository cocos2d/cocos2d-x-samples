#! /usr/bin/env python

if __name__ == '__main__':
	import setup
	raise SystemExit(setup.main())

import os
import sys
import shutil
from subprocess import call
import ctypes
#import win32file

def main():
	workDir = os.getcwd()

	os.chdir('../../libs/GAF/')

	gafDir = os.getcwd()

	platform = sys.platform
	if platform == 'win32':
		print "Please call setup.bat"
	else:
		os.symlink(gafDir, workDir + '/Examples')
		