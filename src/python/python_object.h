#ifndef SO_PYTHON_OBJECT_H
#define SO_PYTHON_OBJECT_H
#include <string>
#include <Python.h>
#include <sno/so_exception.h>
#include <tuple>
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
   * @brief Constructor, a new python tuple from the C++ tuple
   * @param tuple
   */
  template<class...Types>
  Python_object(const std::tuple<Types...> tuple)
    :
      m_obj(PyTuple_New(sizeof... (Types)))
  {
    if(!m_obj)
    {
      throw so::runtime_error("Failed to create PyTuple");
    }
    make_pytuple(tuple, m_obj);
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

  /**
   * @brief Get the value of this python object as the specified type
   * @return Python object as the specified type
   * @throws so::runtime_error if this object cannot be converted to T
   */
  template<class T>
  T As() const;

private:
  /**
   * @brief m_obj The python object managed by this class
   */
  PyObject* m_obj;

  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I == sizeof...(Tp), void>::type
  make_pytuple(std::tuple<Tp...>&, PyObject*)
  { }

  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I < sizeof...(Tp), void>::type
  make_pytuple(std::tuple<Tp...>& t, PyObject* py_tuple)
  {
    PyTuple_SetItem(py_tuple, I, so::Python_object(std::get<I>(t)).Get());
  }
};
}
#endif
