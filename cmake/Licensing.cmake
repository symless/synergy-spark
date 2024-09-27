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

macro(configure_licensing)

  # activation is off by default to make life easier for contributors.
  option(SYNERGY_ENABLE_ACTIVATION "Enable activation dialog, etc" ON)
  if(SYNERGY_ENABLE_ACTIVATION)
    message(STATUS "License activation is enabled")
    add_definitions(-DSYNERGY_ENABLE_ACTIVATION)
  else()
    message(STATUS "License activation is disabled")
  endif()

endmacro()
