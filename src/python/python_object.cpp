#include <python/python_object.h>

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Get this object as a double
 * @param[out] dbl Object as a double
 * @throws so::runtime_exception if this object cannot be represented as a double
 */
void so::Python_object::get_as(double& dbl) const
{

}

/**
 * @brief Get this object as a string
 * @param[out] str String representing this object
 * @throws so::runtime_exception if this object cannot be represented as a string
 */
void so::Python_object::get_as(std::string& str) const
{
  PyObject* repr = PyObject_Repr(m_obj);
  str = std::string(PyUnicode_AsUTF8(repr));
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
