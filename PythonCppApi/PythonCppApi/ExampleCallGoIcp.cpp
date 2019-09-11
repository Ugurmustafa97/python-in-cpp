#include <iostream>

#include <Python.h>
#include <windows.h>


int main(int argc, char *argv[])
{
  // Initialize the Python interpreter.
  Py_Initialize();

  // Create some Python objects that will later be assigned values.
  PyObject *pName, *pModule, *pDict, *pClass;

  // Convert the file name to a Python string.
  pName = PyUnicode_FromString("py_goicp");

  // Import the file as a Python module.
  pModule = PyImport_Import(pName);

  // Create a dictionary for the contents of the module.
  pDict = PyModule_GetDict(pModule);

  // Get the add method from the dictionary.
  pClass = PyDict_GetItemString(pDict, "GoICP");

  // Create the GoIcp object.
  PyObject* goicp = PyObject_CallObject(pClass, NULL);

  // Get and print the default MSE Threshold attribute.
  pName = PyUnicode_FromString("MSEThresh");
  PyObject* mseThresh = PyObject_GetAttr(goicp, pName);
  double mseThreshDouble = PyFloat_AsDouble(mseThresh);

  std::cout << "Default MSE Theshold: " << mseThreshDouble << std::endl;

  // Set the MSE threshold attribute to something else.
  PyObject* mseThreshNew = PyFloat_FromDouble(1.23456789);
  PyObject_SetAttr(goicp, pName, mseThreshNew);

  // Get and print the new MSE threshold attribute.
  mseThresh = PyObject_GetAttr(goicp, pName);
  mseThreshDouble = PyFloat_AsDouble(mseThresh);
  
  std::cout << "New MSE Threshold: " << mseThreshDouble << std::endl;

  //// Destroy the Python interpreter.
  Py_Finalize();
}