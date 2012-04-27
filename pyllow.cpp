#define BOOST_PYTHON_STATIC_LIB

#include "pyllow.h"
#include <boost/python.hpp>

namespace py = boost::python;

const wchar_t Pyllow::VERSION[] = L"0.1";

Pyllow::Pyllow()
{
	Py_SetPythonHome(L"C:\\Program Files (x86)\\Python32\\");

	Py_Initialize();

	py::object main_module = py::import("__main__");
	py::object main_namespace = main_module.attr("__dict__");

	// CRASH :( exception? add error handling
	/*
	py::exec("import Tkinter", main_namespace);
	py::exec("import tkMessageBox", main_namespace);
	py::exec("tkMessageBox.showinfo('tkMessageBox', 'Ohai there')", main_namespace);
	*/

	py::exec("open('test.txt', 'w').write('trololo')", main_namespace);

	Py_Finalize();
}
