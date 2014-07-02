#! /usr/bin/env python

if __name__ == '__main__':
	import setup
	raise SystemExit(setup.main())

import os
import sys
import shutil
from subprocess import call
#import win32file

def main():
	workDir = os.getcwd()

	os.chdir('../../libs/GAF/')

	gafDir = os.getcwd()

	platform = sys.platform
	if platform == 'win32':
		#win32file.CreateSymbolicLink(gafDir, workDir + '/Examples', 1)
	else:
		os.symlink(gafDir, workDir + '/Examples')
		