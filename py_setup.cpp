#include "py_setup.h"

#include <boost/python.hpp>

namespace py = boost::python;

std::wstring PySetup::program_name;
std::wstring PySetup::python_home;

void PySetup::set_program_name(const std::wstring& program_name)
{
	PySetup::program_name = program_name;
	Py_SetProgramName(const_cast<wchar_t*>(PySetup::program_name.c_str()));
}

void PySetup::set_python_home(const std::wstring& python_home)
{
	PySetup::python_home = python_home;
	Py_SetPythonHome(const_cast<wchar_t*>(PySetup::python_home.c_str()));
}

void PySetup::initialize()
{
	Py_Initialize();
}

void PySetup::finalize()
{
	Py_Finalize();
}

bool PySetup::is_initialized()
{
	return Py_IsInitialized() != 0;
}

void PySetup::set_argv(const std::vector<std::wstring>& argv)
{
	std::vector<const wchar_t*> argv_ptrs(argv.size());
	std::transform(argv.begin(), argv.end(), argv_ptrs.begin(), [](const std::wstring& s) { return s.c_str(); } );

	PySys_SetArgv(argv_ptrs.size(), const_cast<wchar_t**>(argv_ptrs.data()));
}

std::wstring PySetup::get_program_name()
{
	return Py_GetProgramName();
}

std::wstring PySetup::get_prefix()
{
	return Py_GetPrefix();
}

std::wstring PySetup::get_exec_prefix()
{
	return Py_GetExecPrefix();
}

std::wstring PySetup::get_program_fullpath()
{
	return Py_GetProgramFullPath();
}

std::wstring PySetup::get_path()
{
	return Py_GetPath();
}

std::string PySetup::get_version()
{
	return Py_GetVersion();
}

std::string PySetup::get_platform()
{
	return Py_GetPlatform();
}

std::string PySetup::get_copyright()
{
	return Py_GetCopyright();
}

std::string PySetup::get_compiler()
{
	return Py_GetCompiler();
}

std::string PySetup::get_buildinfo()
{
	return Py_GetBuildInfo();
}
