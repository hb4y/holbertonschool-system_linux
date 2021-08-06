#include <Python.h>

/**
 * print_python_list - prints list object
 * @p: pointer to PyObjects
 */
void print_python_list(PyObject *p)
{
	PyObject *n;
	Py_ssize_t size = PyList_Size(p);
	Py_ssize_t i;

	if (!p)
		return;
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %lu\n", size);
	printf("[*] Allocated = %lu\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < size; i++)
	{
		n = ((PyListObject *)(p))->ob_item[i];
		printf("Element %ld: %s\n", i, n->ob_type->tp_name);
		if (PyBytes_Check(n))
			print_python_bytes(n);
	}
}

/**
 * print_python_bytes - prints object
 * @p: PyObject list
 */
void print_python_bytes(PyObject *p)
{
	char *b_str;
	Py_ssize_t size;
	Py_ssize_t i;

	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
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