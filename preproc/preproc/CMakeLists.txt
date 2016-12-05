cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)
project (img_preproc)

# add_definitions("-std=c++11")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake" )

# Add OpenCV 3.1
#find_package( OpenCV)
find_package( OpenCV REQUIRED  core highgui imgcodecs 
                     HINTS /usr/local/opt/opencv3)
#find_package( OpenCV 2.4 REQUIRED core highgui imgproc features2d)

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})


# VLFEAT
# find_package(VLFEAT REQUIRED )
# include_directories( ${VLFEAT_INCLUDE_DIR} )


# find_package(Glog REQUIRED)
# include_directories(${GLOG_INCLUDE_DIRS})
# Google Test
# enable_testing() # Only required for CTest
#find_package(GTest )
#include_directories(${GTEST_INCLUDE_DIRS})

# add_subdirectory(modules/createvoc)
# add_subdirectory(modules/bow)
# add_subdirectory(modules/DirectoryTools)
# add_subdirectory(modules/XdibiasHelpers)
# add_subdirectory(modules/xmlParser)
# add_subdirectory(modules/classification)
# add_subdirectory(modules/training)

# set(SUBPROJECT bow)
# message(STATUS "Configuring ${SUBPROJECT}")

set(IMG_PREPROC_INC ./include)
set(IMG_PREPROC_HPP
            ${IMG_PREPROC_INC}/imgdb_converter.hpp
            )

set(IMG_PREPROC_SRC ./src)
set(IMG_PREPROC_CPP 
            ${IMG_PREPROC_SRC}/preproc.cpp
            ${IMG_PREPROC_SRC}/imgdb_converter.cpp
            )

include_directories(${IMG_PREPROC_INC})

add_executable( preproc ${IMG_PREPROC_CPP} ${IMG_PREPROC_HPP})
target_link_libraries( preproc ${OpenCV_LIBS})

