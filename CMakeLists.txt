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

cmake_minimum_required(VERSION 3.8)

project(synergy C CXX)

include(cmake/Odin.cmake)
include(cmake/Licensing.cmake)
include(cmake/Build.cmake)
include(cmake/Libraries.cmake)

configure_odin()
configure_licensing()
configure_build()
configure_libs()

add_subdirectory(odin)
add_subdirectory(src)
