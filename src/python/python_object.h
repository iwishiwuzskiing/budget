#ifndef SO_PYTHON_OBJECT_H
#define SO_PYTHON_OBJECT_H
#include <string>
#include <Python.h>
#include <sno/so_exception.h>
#include <tuple>
#include <vector>

namespace so
{
class Python_object
{
public:
  /**
   * @brief Constructor, a wrapper around the provided python object
   * @param obj Python object to wrap
   * @param incref True if the reference count for this object should be
   * increased. The reference count only needs to be increased if this
   * Python_object is being initialized with a borrowed reference
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
  T As() const
  {
    T out;
    get_as(out);
    return out;
  }

private:
  /**
   * @brief m_obj The python object managed by this class
   */
  PyObject* m_obj;

  /**
   * @brief Base case for populating py_tuple, does nothing
   */
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I == sizeof...(Tp), void>::type
  make_pytuple(const std::tuple<Tp...>&, PyObject*)
  { }

  /**
   * @brief Populate a python tuple from a std::tuple
   * @param[in] t C++ tuple to populate python tuple from
   * @param[out] py_tuple Python tuple to be populated
   */
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I < sizeof...(Tp), void>::type
  make_pytuple(const std::tuple<Tp...>& t, PyObject* py_tuple)
  {
    PyTuple_SetItem(py_tuple, I, so::Python_object(std::get<I>(t)).Get());
    make_pytuple<I + 1, Tp...>(t, py_tuple);
  }

  /**
   * @brief Get this object as a double
   * @param[out] dbl Object as a double
   * @throws so::runtime_exception if this object cannot be represented as a double
   */
  void get_as(double& dbl) const;

  /**
   * @brief Get this object as a string
   * @param[out] str String representing this object
   * @throws so::runtime_exception if this object cannot be represented as a string
   */
  void get_as(std::string& str) const;

  /**
   * @brief Get this object as a vector.
   * Strong exception guarantee.
   * @param[out] vec Vector to populate
   * @throws so::runtime_exception if this object cannot be converted into the
   * specified type of vector
   */
  template<class T>
  void get_as(std::vector<T>& vec) const
  {
    if(!PySequence_Check(m_obj))
    {
      throw so::runtime_error("Object is not a sequence");
    }

    // Populate a temporary object in case creation fails
    std::vector<T> out_tmp;
    Py_ssize_t num = PySequence_Size(m_obj);
    for(ssize_t k = 0; k < num; k++)
    {
      out_tmp.push_back(so::Python_object(PySequence_GetItem(m_obj, k), false).As<T>());
    }
    std::swap(vec, out_tmp);
  }
};
}
#endif
