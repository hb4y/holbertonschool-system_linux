#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <object.h>
#include <listobject.h>
#include <bytesobject.h>
#include <floatobject.h>
#include <string.h>
/**
 * print_python_bytes - bytes
 * @p: obj
 */
void print_python_bytes(PyObject *p)
{
	size_t b_size, i;
	char *str;

	setbuf(stdout, NULL);

	printf("[.] bytes object info\n");

	if (PyBytes_Check(p) == 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	str = ((PyBytesObject *)(p))->ob_sval, b_size = PyBytes_Size(p);
	printf("  size: %ld\n  trying string: %s\n", b_size, str);
	b_size >= 10 ? b_size = 10 : b_size++;
	printf("  first %ld bytes: ", b_size);
	for (i = 0; i < b_size - 1; i++)
		printf("%02hhx ", str[i]);
	printf("%02hhx\n", str[i]);
}
/**
 * print_python_float - float
 * @p: obj
 */
void print_python_float(PyObject *p)
{
	char *b_str;
	double f;

	setbuf(stdout, NULL);

	printf("[.] float object info\n");
	if (PyFloat_Check(p) == 0)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	f = (((PyFloatObject *)(p))->ob_fval);
	b_str = PyOS_double_to_string(f, 'g', 16, 0, NULL);
	if (strchr(b_str, '.'))
		printf("  value: %s\n", b_str);
	else
		printf("  value: %s.0\n", b_str);
}
/**
 * print_python_list - list
 * @p: obj
 */
void print_python_list(PyObject *p)
{
	size_t a;
	const char *tmp;
	size_t size, i;
	PyListObject *list;

	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	if (PyList_Check(p) == 0)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	list = (PyListObject *)p;
	size = PyList_GET_SIZE(p);
	a = list->allocated;
	printf("[*] Size of the Python List = %ld\n[*] Allocated = %li\n", size, a);

	for (i = 0; i < size; i++)
	{
		tmp = (list->ob_item[i])->ob_type->tp_name;
		printf("Element %li: %s\n", i, tmp);
		!strcmp(tmp, "bytes") ? print_python_bytes(list->ob_item[i]) : (void)tmp;
		!strcmp(tmp, "float") ? print_python_float(list->ob_item[i]) : (void)tmp;
	}
}
