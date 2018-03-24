#ifndef SO_PY_OBJECT_H
#define SO_PY_OBJECT_H
#include <string>
#include <Python.h>
#include <sno/so_exception.h>
namespace so
{
class Python_object
{
public:
  /**
   * @brief Constructor, a wrapper around the provided python object
   * @param obj Python object to wrap
   * @param incref True if the reference count for this object should be
   * increased
   */
  Python_object(PyObject* obj, bool incref = true)
    :
      m_obj(obj)
  {
    if(incref)
    {
      Py_IncRef(m_obj);
    }
  }

  /**
   * @brief Constructor, a new python object representing the specified string
   * @param str String to store in a python object
   */
  Python_object(const std::string str)
    :
      m_obj(PyBytes_FromString(str.c_str()))
  {
    if(!m_obj)
    {
      throw so::runtime_error("Failed to create PyBytes from '" + str + "'");
    }
    //PyBytes_FromString returns a new reference, so there's no need to increment
  }

  /**
   * Destructor, decrements the reference count
   */
  ~Python_object()
  {
    Py_DecRef(m_obj);
  }

  /**
   * @brief Get the raw PyObject that is being managed
   * @return Raw python object being managed
   */
  PyObject* Get()
  {
    return m_obj;
  }

private:
  /**
   * @brief m_obj The python object managed by this class
   */
  PyObject* m_obj;
};
}
#endif
