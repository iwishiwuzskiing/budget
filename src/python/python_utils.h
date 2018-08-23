#ifndef SO_PYTHON_UTILS_H
#define SO_PYTHON_UTILS_H

#include <string>
#include <python/python_object.h>
#include <wchar.h>
namespace so
{
namespace Python_utils
{
/**
 * @brief Import a module
 * @param name Name of the module to import
 * @return Python_object containing the loaded module
 * @throws so::runtime_error if the module can't be loaded
 */
so::Python_object Import_module(const std::string name)
{
  so::Python_object module(PyImport_ImportModule(name.c_str()), false);
  if(!module.Get())
  {
    throw so::runtime_error("Failed to load module '" + name + "'");
  }
  return module;
}

/**
 * @brief Make a python tuple from a set of values
 * @param types Values to make tuple from
 * @return Python object containing the tuple
 * @throws so::runtime_error if the tuple can't be created
 */
template<class ...T>
so::Python_object Make_pytuple(T...types)
{
  return so::Python_object(std::make_tuple(types...));
}

wchar_t** char_array_wchar_array(int argc, char** argv)
{

}

} // namespace Python_utils
} // namespace so
#endif
