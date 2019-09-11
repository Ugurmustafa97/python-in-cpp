#include <iostream>

#include <Python.h>
#include <windows.h>


int main(int argc, char *argv[])
{
  // Initialize the Python interpreter.
  Py_Initialize();

  // Create some Python objects that will later be assigned values.
  PyObject *pName, *pModule, *pDict, *pClass, *pMethod, *pResult;

  // Convert the file name to a Python string.
  pName = PyUnicode_FromString("ModuleWithThread");

  // Import the file as a Python module.
  pModule = PyImport_Import(pName);

  // Create a dictionary for the contents of the module.
  pDict = PyModule_GetDict(pModule);

  // Get the add method from the dictionary.
  pClass = PyDict_GetItemString(pDict, "ClassWithThread");

  // Create the instance
  PyObject* classWithThread = PyObject_CallObject(pClass, NULL);

  pMethod = PyObject_GetAttrString(classWithThread, "getValue");

  while (true)
  {
    pResult = PyEval_CallObject(pMethod, NULL);

    PyObject* res0 = PyList_GetItem(pResult, 0);
    PyObject* res1 = PyList_GetItem(pResult, 1);
    PyObject* res2 = PyList_GetItem(pResult, 2);

    long result0 = PyLong_AsLong(res0);
    long result1 = PyLong_AsLong(res1);
    long result2 = PyLong_AsLong(res2);
    
    std::cout << "Value:  " << result0 << ", " << result1 << ", " << result2 << std::endl;

    Sleep(100);
  }
  

  //// Set the MSE threshold attribute to something else.
  //PyObject* mseThreshNew = PyFloat_FromDouble(1.23456789);
  //PyObject_SetAttr(goicp, pName, mseThreshNew);

  //// Get and print the new MSE threshold attribute.
  //mseThresh = PyObject_GetAttr(goicp, pName);
  //mseThreshDouble = PyFloat_AsDouble(mseThresh);

  //std::cout << "New MSE Threshold: " << mseThreshDouble << std::endl;

  //// Destroy the Python interpreter.
  Py_Finalize();
}