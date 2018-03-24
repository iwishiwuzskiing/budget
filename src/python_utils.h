#ifndef SO_PYTHON_UTILS_H
#define SO_PYTHON_UTILS_H

#include <string>
#include <python_object.h>
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
  so::Python_object py_name(name);
  so::Python_object module(PyImport_Import(py_name.Get()), false);
  if(!module.Get())
  {
    throw so::runtime_error("Failed to load module" + name);
  }
  return module;
}

} // namespace Python_utils
} // namespace so
#endif
