# Synergy -- mouse and keyboard sharing utility
# Copyright (C) 2024 Symless Ltd.
#
# This package is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# found in the file LICENSE that should have accompanied this file.
#
# This package is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

macro(configure_build)

  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

  warnings_as_errors()

  if(APPLE)
    configure_apple()
  endif()

endmacro()

macro(configure_apple)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")
  set(CMAKE_CXX_FLAGS "--sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS}")
endmacro()

macro(warnings_as_errors)
  if(WIN32)
    message(STATUS "Enabling warnings as errors (MSVC)")
    add_compile_options(/WX)
  elseif(UNIX)
    message(STATUS "Enabling warnings as errors (GNU/Clang)")
    add_compile_options(-Werror)
  endif()
endmacro()
