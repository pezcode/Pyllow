#include "pyllow.h"

#include <boost/python.hpp>
#include "py_setup.h"
#include "py_error.h"

#include <windows.h>
#include <ollydbg.h>

namespace py = boost::python;

const wchar_t Pyllow::VERSION[] = L"0.1";

Pyllow::Pyllow()
{
	// Needed if Python can't find the path automatically via env vars / registry
	//PySetup::set_python_home(L"C:\\Program Files (x86)\\Python32\\");

	PySetup::initialize();

	py::object main_module = py::import("__main__");
	py::object main_namespace = main_module.attr("__dict__");

	try
	{
		py::exec("import sys", main_namespace, main_namespace);
		py::exec("sys.path.append('C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow')", main_namespace, main_namespace);
		py::exec("import init", main_namespace, main_namespace);

		// how to load unicode path? py::str is char only
		// worse: crashes in ntdll
		//std::wstring init_script = std::wstring(_plugindir) + L"/Pyllow/init.py";
		//std::string init_script = std::string("C:/Program Files (x86)/RE/Olly 2/Plugins") + "/Pyllow/init.py";
		//py::exec_file(py::str(init_script), main_namespace, main_namespace);

		// doesn't find execfile
		//py::exec("execfile('C:/Program Files (x86)/RE/Olly 2/Plugins/Pyllow/init.py')", main_namespace, main_namespace);
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
