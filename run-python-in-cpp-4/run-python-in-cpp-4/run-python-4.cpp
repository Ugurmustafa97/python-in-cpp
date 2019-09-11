/* Error messages were removed for easy reading but those are required. */

#include <iostream>
#include <Python.h>

int main(int argc, char *argv[])
{
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	Py_Initialize(); /* Initializing python.*/

	pName = PyUnicode_DecodeFSDefault(argv[1]);
	pModule = PyImport_Import(pName);

	pFunc = PyObject_GetAttrString(pModule, argv[2]);

	pArgs = PyTuple_New(argc - 3); /* Creates tuple for 2 items. */

	/* For loop to assign the values of pArgs.*/
	for (int i = 0; i < argc - 3; ++i)
	{
		pValue = PyLong_FromLong(atoi(argv[i + 3])); /* Take value from command.*/
		PyTuple_SetItem(pArgs, i, pValue); /* Assign the value into pArgs. */
	}

	pValue = PyObject_CallObject(pFunc, pArgs);
	std::cout << "Result of call: " << PyFloat_AsDouble(pValue) << std::endl;
	
	Py_XDECREF(pFunc);
	Py_DECREF(pName);
	Py_DECREF(pModule);
	Py_DECREF(pArgs);
	Py_DECREF(pValue);

	Py_Finalize();

	return 0;

}