#include <Python.h>

/**
 * print_python_float - floats
 * @p: obj
 */
void print_python_float(PyObject *p)
{
	char *str;
	double val;

	setbuf(stdout, NULL);
	printf("[.] float object info\n");
	if (!p || !PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	val = (((PyFloatObject *)(p))->ob_fval);
	str = PyOS_double_to_string(val, 'r', 0, Py_DTSF_ADD_DOT_0, NULL);
	printf("  value: %s\n", str);
}

/**
 * print_python_bytes - bytes
 * @p: obj
 */
void print_python_bytes(PyObject *p)
{
	char *b_str;
	Py_ssize_t b_size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	b_size = (((PyVarObject *)(p))->ob_size);
	b_str = (((PyBytesObject *)(p))->ob_sval);
	printf("  size: %ld\n", b_size);
	printf("  trying string: %s\n", b_str);
	b_size = b_size > 9 ? 10 : b_size + 1;
	printf("  first %ld bytes: ", b_size);
	for (i = 0; i < b_size; i++)
		printf("%02hhx%c", b_str[i], i < b_size - 1 ? ' ' : '\n');
}

/**
 * print_python_list - list
 * an Python list objects.
 * @p: Pyobject list
 */
void print_python_list(PyObject *p)
{
	PyObject *it;
	Py_ssize_t l_size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	if (!p || !PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	l_size = (((PyVarObject *)(p))->ob_size);
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", l_size);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < l_size; i++)
	{
		it = ((PyListObject *)(p))->ob_item[i];
		printf("Element %ld: %s\n", i, it->ob_type->tp_name);
		if (PyBytes_Check(it))
			print_python_bytes(it);
		else if (PyFloat_Check(it))
			print_python_float(it);
	}
}
