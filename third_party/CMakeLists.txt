# Copyright (c) 2021, A Effective Infrastructure Committee.
# All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
include(FetchContent)

FetchContent_Declare(
  xlib
  GIT_REPOSITORY "https://github.com/ifplusor/xlib.git"
  GIT_TAG "develop")

FetchContent_GetProperties(xlib)
if(NOT xlib_POPULATED)
  option(CHECK_LOCAL_XLIB "Check local XLib library" ON)

  if(${CHECK_LOCAL_XLIB})
    if(EXISTS ${CMAKE_SOURCE_DIR}/../xlib)
      get_filename_component(xlib_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../xlib
                             REALPATH)
      message(STATUS "Found XLib library in local: ${xlib_SOURCE_DIR}")
      set(FETCHCONTENT_SOURCE_DIR_XLIB ${xlib_SOURCE_DIR})
    endif()
  endif()

  FetchContent_Populate(xlib)
  add_subdirectory(${xlib_SOURCE_DIR} ${xlib_BINARY_DIR})
endif()

FetchContent_Declare(
  logxx
  GIT_REPOSITORY "https://github.com/aeic/logxx.git"
  GIT_TAG "develop")

FetchContent_GetProperties(logxx)
if(NOT logxx_POPULATED)
  option(CHECK_LOCAL_LOGXX "Check local Log++ library" ON)
  if(${CHECK_LOCAL_LOGXX})
    if(EXISTS ${CMAKE_SOURCE_DIR}/../logxx)
      get_filename_component(logxx_SOURCE_DIR ${CMAKE_SOURCE_DIR}/../logxx
                             REALPATH)
      message(STATUS "Found Log++ library in local: ${logxx_SOURCE_DIR}")
      set(FETCHCONTENT_SOURCE_DIR_LOGXX ${logxx_SOURCE_DIR})
    endif()
  endif()

  FetchContent_Populate(logxx)
  add_subdirectory(${logxx_SOURCE_DIR} ${logxx_BINARY_DIR})
endif()

FetchContent_Declare(
  abseil
  GIT_REPOSITORY "https://github.com/aeic/abseil-cpp.git"
  GIT_TAG "20200923.2")
FetchContent_MakeAvailable(abseil)

FetchContent_Declare(
  json
  GIT_REPOSITORY "https://github.com/aeic/json.git"
  GIT_TAG "v3.9.1")
FetchContent_MakeAvailable(json)
