#include <Python.h>

/**
 * print_python_string - Python strings
 * @p: str
 */
void print_python_string(PyObject *p)
{
	char *id;

	printf("[.] string object info\n");
	if (!p || !PyUnicode_Check(p))
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	if (PyUnicode_IS_COMPACT_ASCII(p))
		id = "compact ascii";
	else if (PyUnicode_IS_COMPACT(p))
		id = "compact unicode object";
	else if (PyUnicode_KIND(p) == PyUnicode_WCHAR_KIND)
		id = "legacy string, not ready";
	else if (!PyUnicode_IS_COMPACT(p))
		id = "legacty string, ready";
	printf("  type: %s\n", id);
	printf("  length: %ld\n", (((PyASCIIObject *)(p))->length));
	printf("  value: %ls\n", (PyUnicode_AsWideCharString(p, NULL)));
}
