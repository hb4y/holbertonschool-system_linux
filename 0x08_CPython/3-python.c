#include <Python.h>

/**
 * print_python_float - info Python float
 * @p: PyObject
 */
void print_python_float(PyObject *p)
{
	char *str;
	double value;

	setbuf(stdout, NULL);

	printf("[.] float object info\n");
	if (!p || !PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	value = (((PyFloatObject *)(p))->ob_fval);
	str = PyOS_double_to_string(value, 'r', 0, Py_DTSF_ADD_DOT_0, NULL);
	printf("  value: %s\n", str);
}

/**
 * print_python_bytes - info Python bytes
 * @p: PyObject
 */
void print_python_bytes(PyObject *p)
{
	char *py_bytes_str;
	Py_ssize_t py_bytes_size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	py_bytes_size = (((PyVarObject *)(p))->ob_size);
	py_bytes_str = (((PyBytesObject *)(p))->ob_sval);

	printf("  size: %ld\n", py_bytes_size);
	printf("  trying string: %s\n", py_bytes_str);
	py_bytes_size = py_bytes_size > 9 ? 10 : py_bytes_size + 1;
	printf("  first %ld bytes: ", py_bytes_size);

	for (i = 0; i < py_bytes_size; i++)
		printf("%02hhx%c", py_bytes_str[i], i < py_bytes_size - 1 ? ' ' : '\n');
}

/**
 * print_python_list - info python list
 * @p: Pyobject list
 */
void print_python_list(PyObject *p)
{
	PyObject *item;
	Py_ssize_t list_size;
	Py_ssize_t i;

	setbuf(stdout, NULL);
	if (!p || !PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	list_size = (((PyVarObject *)(p))->ob_size);
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", list_size);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < list_size; i++)
	{
		item = ((PyListObject *)(p))->ob_item[i];
		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
		else if (PyFloat_Check(item))
			print_python_float(item);
	}
}
