#include <Python.h>

/* Execute func(x,y) in the Python interpreter. The
arguments and return result of the function must be Python floats */


static char Module[] = {"test"};

double call_func(PyObject *func, double x, double y) {
PyObject *args; 
PyObject *kwargs; 
PyObject *result = 0; 
double retval;

/* Make sure we own the GIL */ 
PyGILState_STATE state = PyGILState_Ensure();

/* Verify that func is a proper callable */ 
if (!PyCallable_Check(func)) {
    fprintf(stderr,"call_func: expected a callablen"); goto fail;
} 
/* Build arguments */ 
args = Py_BuildValue("(dd)", x, y); 
kwargs = NULL;

/* Call the function */ 
result = PyObject_Call(func, args, kwargs); 
Py_DECREF(args); 
Py_XDECREF(kwargs);

/* Check for Python exceptions (if any) */ 
if (PyErr_Occurred()) {
    PyErr_Print(); goto fail;
}

/* Verify the result is a float object */ 
if (!PyFloat_Check(result)) {
    fprintf(stderr,"call_func: callable didn’t return a floatn"); goto fail;
}

/* Create the return value */ 
retval = PyFloat_AsDouble(result); 
Py_DECREF(result);

/* Restore previous GIL state and return */ 
PyGILState_Release(state); 
return retval;

fail:
Py_XDECREF(result); PyGILState_Release(state); abort(); // Change to something more appropriate
}


/* Load a symbol from a module */
PyObject *import_name(const char *modname, const char *symbol) {
  PyObject *u_name, *module;
  u_name = PyUnicode_FromString(modname);
  module = PyImport_Import(u_name);
  Py_DECREF(u_name);
  return PyObject_GetAttrString(module, symbol);
}

double testpy(double a){
  PyObject *pModule = NULL;
  PyObject *pFunc = NULL;
  PyObject *kw = NULL;
  PyGILState_STATE state = PyGILState_Ensure();
  pModule = PyImport_ImportModule(Module);
  pFunc = PyObject_GetAttrString(pModule,"ad");
  PyObject* r;
  PyObject* r2;
  PyObject* arg;
  if (!PyCallable_Check(pFunc)) {
    fprintf(stderr,"testpy: expected a callablen"); goto fail;
} 
  arg = Py_BuildValue("d",a);
  double re;
  double ret;
  //r = PyEval_CallObject(pFunc, arg);
  r2= PyObject_Call(pFunc, arg, kw);
  PyArg_Parse(r, "i", &re);
  ret = PyFloat_AsDouble(r2); 
  return ret;

fail:
Py_XDECREF(r); PyGILState_Release(state); abort(); // Change to something more appropriate
}

/* Simple embedding example */
int main() {
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('./')");
  PyRun_SimpleString("print sys.path");

  PyObject *pow_func;

  double x;

  Py_Initialize();
  /* Get a reference to the math.pow function */
  pow_func = import_name("math","pow");


  /* Call it using our call_func() code */
  for (x = 0.0; x < 10.0; x += 0.1) {
    printf("%0.2f %0.2f\n", x, call_func(pow_func,x,2));

  }
  

  double val = 6;
  double o;
  //o = testpy(val);
 // printf("%lf\n", o);

  /* Done */
  Py_DECREF(pow_func);
  Py_Finalize();
  return 0;
}
