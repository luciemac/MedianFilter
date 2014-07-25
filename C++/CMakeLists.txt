# This is the root ITK CMakeList file: 
cmake_minimum_required(VERSION 2.8)

# This project is designed to be built outside the Insight source tree.
project(MedianFilter)

# Find Slicer3
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})
 
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set(MedianFilter_SOURCE MedianFilter.cxx)
SEMMacroBuildCLI(
  NAME MedianFilter
  EXECUTABLE_ONLY
  TARGET_LIBRARIES ${ITK_LIBRARIES}
  )

target_link_libraries(MedianFilter ${ITK_LIBRARIES})

option(BUILD_TESTING "Build the testing tree" ON)

IF(BUILD_TESTING)
  include(CTest)
  ADD_SUBDIRECTORY(Testing)
ENDIF(BUILD_TESTING)

