#include "pyllow.h"

#include <windows.h>
#include <boost/python.hpp>
#include "py_setup.h"
#include "py_error.h"

namespace py = boost::python;

const wchar_t Pyllow::VERSION[] = L"0.1";

Pyllow::Pyllow()
{
	// Needed if Python can't find the path automatically via env vars / registry
	//PySetup::set_python_home(L"C:\\Program Files (x86)\\Python32\\");

	PySetup::initialize();

	// Needed by some modules
	std::vector<std::wstring> argv(1); // one empty string (argv[0])
	PySetup::set_argv(argv);

	py::object main_module = py::import("__main__");
	py::object main_namespace = main_module.attr("__dict__");

	try
	{
		//py::exec("from tkinter import messagebox", main_namespace);
		//py::exec("messagebox.showinfo('tkMessageBox', 'Ohai there')", main_namespace);

		py::exec("import sys", main_namespace, main_namespace);
		py::exec("sys.path.append('C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow')", main_namespace, main_namespace);

		argv[0] = L"C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow/init.py";
		PySetup::set_argv(argv);

		// Add Olly-Plugin-Dir/Pyllow to Python path
		// in Pyllow path: Olly functions (SWIG?)
		//                 Pyllow module (higher level stuff)
		//                 user-supplied modules (addition plugins.py? or let users add to init.py)
		// load init.py [explicit path] -> Bootstrap

		//py::exec("import sys", main_namespace, main_namespace);
		//py::exec("sys.path.append('C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow')", main_namespace, main_namespace);

		//py::exec_file("C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow/init.py", main_namespace, main_namespace);

		py::exec("import init", main_namespace, main_namespace);

		/*
		py::exec("import mod_test", main_namespace, main_namespace);
		py::exec("x = mod_test.test()", main_namespace, main_namespace);
		py::exec("x.set('oh')", main_namespace, main_namespace);
		py::exec("s = x.get()", main_namespace, main_namespace);
		*/
	}
	catch(const py::error_already_set& e)
	{
		std::wstring error_description = PyError::get_python_error_description();
		MessageBox(NULL, error_description.c_str(), L"Error", MB_ICONERROR);
	}
}

Pyllow::~Pyllow()
{
	PySetup::finalize();
}
