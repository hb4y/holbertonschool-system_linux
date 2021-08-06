#include <Python.h>

/**
 * print_python_float - info Python float
 * @p: float
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
 * print_python_bytes - info Python bytes
 * @p: byttes
 */
void print_python_bytes(PyObject *p)
{
	char *b_str;
	Py_ssize_t size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = (((PyVarObject *)(p))->ob_size);
	b_str = (((PyBytesObject *)(p))->ob_sval);
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", b_str);
	size = size > 9 ? 10 : size + 1;
	printf("  first %ld bytes: ", size);
	for (i = 0; i < size; i++)
	{
		printf("%02hhx%c", b_str[i], i < size - 1 ? ' ' : '\n');
	}
}

/**
 * print_python_list - info python list
 * @p: list
 */
void print_python_list(PyObject *p)
{
	PyObject *obj;
	Py_ssize_t size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	if (!p || !PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	size = (((PyVarObject *)(p))->ob_size);
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", size);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);
	for (i = 0; i < size; i++)
	{
		obj = ((PyListObject *)(p))->ob_item[i];
		printf("Element %ld: %s\n", i, obj->ob_type->tp_name);
		if (PyBytes_Check(obj))
			print_python_bytes(obj);
		else if (PyFloat_Check(obj))
			print_python_float(obj);
	}
}
