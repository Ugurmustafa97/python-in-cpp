#include <iostream>
#include <Python.h>
#include <Windows.h>
#include <string.h>

#define JOINT_VALUE 10

void printList(PyObject* pInstance, char* functionName);

int main()
{
	PyObject *pName, *pModule, *pDict;
	PyObject *pClass, *pInstance;

	char *fileName = "fakeDaVinciXiAPI";
	char *className = "fakeDaVinciXiAPI";
	char *functionName = "get_usm_joint_values";

	Py_Initialize();

	//PyObject* sysPath = PySys_GetObject((char*)"path");
	//PyObject* directoryName = PyUnicode_DecodeFSDefault("C:/Users/Mustafa Ugur/Desktop/python-in-cpp/getPythonList/fakeDaVinciXiAPI2");
	
	//PyList_Append(sysPath, directoryName);
	//std::cout << "Imported daVinci package" << std::endl;
	//PyRun_SimpleString("import sys");

	//std::cout << "Imported sys package" << std::endl;
	std::cout << "Before pName assignmet" << std::endl;
	pName = PyUnicode_DecodeFSDefault(fileName);
	std::cout << "After pName assignmet" << std::endl;
	pModule = PyImport_Import(pName);
	std::cout << "After import statement" << std::endl;

	pDict = PyModule_GetDict(pModule);
	std::cout << "After dict statement" << std::endl;
	// get the class name as python string 
	pClass = PyDict_GetItemString(pDict, className);
	std::cout << "After class statement" << std::endl;
	pInstance = PyObject_CallObject(pClass, NULL);
	std::cout << "After object statement" << std::endl;

	while (true)
	{	
		printList(pInstance, functionName);
			
		Sleep(1000);
	}
	
	return 0;

}

void printList(PyObject* pInstance, char* functionName)
{
	long dataArray[JOINT_VALUE];

	PyObject *pList;
	//PyObject *pDataArray[JOINT_VALUE];

	pList = PyList_New(JOINT_VALUE);
	pList = PyObject_CallMethod(pInstance, functionName, NULL, NULL);

	std::cout << "Started to for loop" << std::endl;

	for (int i = 0; i < JOINT_VALUE; i++)
	{
		//pDataArray[i] = PyList_GetItem(pList, i);
		dataArray[i] = PyLong_AsLong(PyList_GetItem(pList, i));
		std::cout << "i= " << i << "     value = " << dataArray[i] << std::endl;
	}

	std::cout << "Closed to for loop" << std::endl;

	Sleep(500);
}