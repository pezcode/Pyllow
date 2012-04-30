#include "py_error.h"

#include <boost/python.hpp>

namespace py = boost::python;

std::wstring PyError::get_python_error_description()
{
	std::wstring ret = L"Unfetchable Python error";

	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);
    
	if(type_ptr != NULL)
	{
		py::handle<> h_type(type_ptr);
		py::str type_pstr(h_type);
		py::extract<std::wstring> e_type_pstr(type_pstr);
		if(e_type_pstr.check())
			ret = e_type_pstr();
		else
			ret = L"Unknown exception type";
	}

	if(value_ptr != NULL)
	{
		py::handle<> h_val(value_ptr);
		py::str a(h_val);
		py::extract<std::wstring> returned(a);
		if(returned.check())
			ret +=  L": " + returned();
		else
			ret += L": Unparseable Python error: ";
	}

	if(traceback_ptr != NULL)
	{
		py::handle<> h_tb(traceback_ptr);
		py::object tb(py::import("traceback"));
		py::object fmt_tb(tb.attr("format_tb"));
		py::object tb_list(fmt_tb(h_tb));
		py::object tb_str(py::str("\n").join(tb_list));
		py::extract<std::wstring> returned(tb_str);
		if(returned.check())
			ret += L": " + returned();
		else
			ret += L": Unparseable Python traceback";
	}

	return ret;
}
