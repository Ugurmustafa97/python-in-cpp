#include <iostream>
#include <Python.h>

int main()
{
	bool pyReturnValue;

	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault("returnTrue");

	pModule = PyImport_Import(pName);
	

	pFunc = PyObject_GetAttrString(pModule, "returnTrue");

	pValue = PyObject_CallObject(pFunc, NULL);

	pyReturnValue = PyObject_IsTrue(pValue);

	if (pyReturnValue == true)
		std::cout << "Python Object is True" << std::endl;
	else
		std::cout << "Python Object is False" << std::endl;

	Py_Finalize();

	return 0;
}