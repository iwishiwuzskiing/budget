#ifndef SO_PYTHON_FUNCTION_H
#define SO_PYTHON_FUNCTION_H
#include <vector>
#include <python/python_object.h>
#include <sno/so_exception.h>
#include <python/python_utils.h>
namespace so
{
template <class R_type, class ... Args>
class Python_function
{
public:
  Python_function(so::Python_object module, std::string name)
    :
      m_func(nullptr)
  {
    //TODO: check if module is valid
    m_func = PyObject_GetAttrString(module.Get(), name.c_str());
    if(!m_func || !PyCallable_Check(m_func))
    {
      throw(so::runtime_error("Not a valid function"));
    }
  }

  /**
   * @brief Call the function
   * @param args Arguments passed to the function
   * @return output of the function
   */
  R_type operator()(Args... args)
  {
    //Unpack params into arg_tuple
    so::Python_object arg_tuple = so::Python_utils::Make_pytuple(args...);

    PyObject* out = PyObject_CallObject(m_func, arg_tuple.Get());
    if(!out)
    {
      //
    }
    return so::Python_object(out, false).As<R_type>();
  }

private:
  /**
   * @brief m_func The stored function
   */
  PyObject* m_func;

};
}
#endif
