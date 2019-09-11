#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <Python.h>

int main(int argc, char *argv[])
{
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;

	int i;

	if (argc < 3)
	{
		std::cout << "Usage: call Python file funcname [args]\n" << std::endl;
	}

	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	/* Error checking of pName left out */
	
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		/*pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc))
		{
			pArgs = PyTuple_New(argc - 3);
			for (i = 0; i < argc - 3; ++i)
			{
				pValue = PyLong_FromLong(atoi(argv[i + 3]));
				if (!pValue)
				{
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					std::cout << " Cannot convert argument" << std::endl;
					return 1;
				}
				/* pValue reference stolen here: */
				PyTuple_SetItem(pArgs, i, pValue);
			}
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				std::cout << "Result of the call: " << PyLong_AsLong(pValue) << std::endl;
				Py_DECREF(pValue);
			}
			else
			{
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				std::cout << "Call failed" << std::endl;
				return 1;
			}

		}
		else
		{
			if (PyErr_Occurred())
				PyErr_Print();
			std::cout << "Cannot find function " << argv[2] << std::endl;
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else
	{
		PyErr_Print();
		std::cout << "Failed to load " << argv[1] << std::endl;
		return 1;
	} 
	if (Py_FinalizeEx() < 0)
	{
		return 120;
	}
	
	return 0;
}

