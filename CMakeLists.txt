#################################
## Project specific stuff
cmake_minimum_required(VERSION 3.7)
#Project name
set(project_name budget)
#Description
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Budget Application")
#Directory for the rest of our CMake stuff
set(cmake_dir /home/shay/development/cmake)
include(${cmake_dir}/basic_app.cmake)
target_link_libraries(${project_name} python3.5m)
target_include_directories(${project_name} PUBLIC /usr/include/python3.5)
