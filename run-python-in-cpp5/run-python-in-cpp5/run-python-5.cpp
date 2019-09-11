#include <iostream>
#include <Python.h>
#include <string.h>

int main(int argc, char *argv[])
{
	/* Creating Python objects. */
	PyObject *pName, *pModule, *pDict;
	PyObject *pClass, *pInstance, *pValue;
	
	int arg[2];
	
	//const char *className = "Operations";

	/* Tell user command is wrong. */
	if (argc < 4)
	{
		std::cout << "Usage: exe_name python_file_name class_name function_name"
			<< std::endl;
		return 1;
	}

	/* Initialize Python, and assign command line to Python objects. */
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	//pClass = PyDict_GetItemString(pDict, className);
	pClass = PyDict_GetItemString(pDict, argv[2]);
	
	/* Check the class name*/
	if (PyCallable_Check(pClass))
	{
		pInstance = PyObject_CallObject(pClass, NULL);
	}
	else
	{
		std::cout << "Class name is wrong" << std::endl;
		return 1;
	}
		
	/* Assign the function inputs in a array and run the function. */
	if (argc > 4)
	{
		for (int i = 0; i < argc - 4; i++)
			arg[i] = atoi(argv[i + 4]);

		pValue = PyObject_CallMethod(pInstance, argv[3], "(ii)", arg[0], arg[1]);
	}
	else
	{
		pValue = PyObject_CallMethod(pInstance, argv[3], NULL);
	}

	/* Check the function result. */
	if (pValue != NULL)
	{
		std::cout << "Return of call: " << PyLong_AsLong(pValue) << std::endl;
		Py_DECREF(pValue);
	}

	else
	{
		PyErr_Print();
	}

	/* Clear the Python objects. */
	Py_DECREF(pName);
	Py_DECREF(pModule);
	Py_DECREF(pDict);
	Py_DECREF(pClass);
	Py_DECREF(pInstance);

	/* Shut down the Python interpreter. */
	Py_Finalize();

	return 0;
}