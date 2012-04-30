import sys

sys.path.append('C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow') #(argv[0])

import ollyapi

#ollyapi.Addtolist(0, 1, str('test'.encode('utf-16-le'))) # works
#ollyapi.Addtolist(0, 0, 'test'.encode('utf-16-le')) # doesn't work
ollyapi.Addtolist(0, 0, 'Pyllow: test 1')
ollyapi.Addtolist(0, 1, 'Pyllow: test 2')
