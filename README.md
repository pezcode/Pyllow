Pyllow
======

Python for Ollydbg
------------------

Pyllow aims to integrate Python into Ollydbg to automate common debugging tasks or extend Ollydbg with new features.
Scripts are run from within Ollydbg and have access to most of the Olly API.

Compilation
-----------

To build Pyllow, you need:
- Visual Studio 2010 [Express]
- Boost with compiled Boost.Python
- a 32-bit Python 3.x install (tested with 3.2)

Depending on your system you may need to point Boost to the correct Python version before compiling Boost.Python.
What you'll want to do is tell Boost about all the available Python installs, and then choose one during the build process.
This is done by adding them to /boost-dir/tools/build/v2/user-config.jam, like this:

using python
	: 3.2
	: "C:/Program Files (x86)/Python32/python.exe" # path to your Python setup
	:
	:
	: <address-model>32 # x86-32 only
	;

You can add more, e.g. a 2.x version or an x86-64 version (change the <address-model>32 to <address-model>64), just make
sure you set the right path to the interpreter (python.exe), Boost will infer the include and lib paths automatically.

Then, you can build Boost.Python like this:

bjam --toolset=msvc-10.0 --build-type=complete --with-python python=3.2 address-model=32

For more info: http://www.boost.org/doc/libs/1_49_0/libs/python/doc/building.html#configuring-boost-build
