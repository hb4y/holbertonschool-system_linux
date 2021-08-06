#include <Python.h>
/**
 * print_python_int - Python int
 * @p: int
 */
void print_python_int(PyObject *p)
{
	PyLongObject *_b, *_d;
	Py_ssize_t s, i, j;
	digit *_p, u, *c;
	twodigits z;
	int tmp_dig;

	if (!p || !PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	_d = (PyLongObject *)p;
	tmp_dig = (33 * _PyLong_DECIMAL_SHIFT) /
		(10 * PyLong_SHIFT - 33 * _PyLong_DECIMAL_SHIFT);
	s = 1 + abs(Py_SIZE(_d)) + abs(Py_SIZE(_d)) / tmp_dig;
	_b = _PyLong_New(s);
	if (_b == NULL)
		return;
	_p = _d->ob_digit, c = _b->ob_digit,  s = 0;

	for (i = abs(Py_SIZE(_d)); --i >= 0; )
	{
		u = _p[i];
		for (j = 0; j < s; j++)
		{
			z = (twodigits)c[j] << PyLong_SHIFT | u;
			u = (digit)(z / _PyLong_DECIMAL_BASE);
			c[j] = (digit)(z - (twodigits)u * _PyLong_DECIMAL_BASE);
		}
		while (u)
			c[s++] = u % _PyLong_DECIMAL_BASE, u /= _PyLong_DECIMAL_BASE;
	}
	s == 0 ? c[s++] = 0 : 0, Py_SIZE(_d) < 0 ? putchar('-') : 0;

	for (i = s; --i >= 0;)
		i == s - 1 ? printf("%u", c[i]) : printf("%09u", c[i]);
	printf("\n");
}
