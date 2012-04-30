#pragma once

#include <string>
#include <vector>

class PySetup
{
public:

	// name of exe -> finds python path (call before initialize)
	static void set_program_name(const std::wstring& program_name);
	// set python path manually (call before initialize)
	static void set_python_home(const std::wstring& python_home);

	static void initialize();
	static void finalize();

	static bool is_initialized();

	// set argv (first is script path, or empty)
	static void set_argv(const std::vector<std::wstring>& argv);

	static std::wstring get_program_name();
	static std::wstring get_prefix();
	static std::wstring get_exec_prefix();
	static std::wstring get_program_fullpath();
	static std::wstring get_path();

	static std::string get_version();
	static std::string get_platform();
	static std::string get_copyright();
	static std::string get_compiler();
	static std::string get_buildinfo();

private:

	// Ensure static storage for strings given to Python

	static std::wstring program_name;
	static std::wstring python_home;
};
