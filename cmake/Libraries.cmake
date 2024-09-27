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

macro(configure_libs)

  configure_qt()

endmacro()

macro(configure_qt)

  find_package(
    Qt6
    COMPONENTS Core Widgets Network
    REQUIRED)

  message(STATUS "Qt version: ${Qt6_VERSION}")

  set(GUI_RES_DIR ${DESKFLOW_RES_DIR}/gui)
  set(GUI_QRC_FILE ${GUI_RES_DIR}/app.qrc)

endmacro()
