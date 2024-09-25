# Deskflow -- mouse and keyboard sharing utility
# Copyright (C) 2024 Symless Ltd.
# Copyright (C) 2009 Nick Bolton
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

macro(configure_branding)

  if(NOT "$ENV{DESKFLOW_PRODUCT_NAME}" STREQUAL "")
    set(DESKFLOW_PRODUCT_NAME $ENV{DESKFLOW_PRODUCT_NAME})
  endif()

  set(DESKFLOW_APP_ID
      "synergy"
      CACHE STRING "ID of the app for filenames, etc")

  set(DESKFLOW_DOMAIN
      "symless.com"
      CACHE STRING "Domain of the app maintainer (not a URL)")

  set(DESKFLOW_PRODUCT_NAME
      "Synergy"
      CACHE STRING "Product name")

  set(DESKFLOW_AUTHOR_NAME
      "Symless"
      CACHE STRING "Author name")

  set(DESKFLOW_MAINTAINER
      "Synergy <support@symless.com>"
      CACHE STRING "Maintainer email address in RFC 5322 mailbox format")

  set(DESKFLOW_WEBSITE_URL
      "https://symless.com/synergy"
      CACHE STRING "URL of the app website")

  set(DESKFLOW_VERSION_URL
      "https://api.symless.com/version/synergy1"
      CACHE STRING "URL to get the latest version")

  set(DESKFLOW_RES_DIR
      "${CMAKE_SOURCE_DIR}/res"
      CACHE STRING "Path to the res directory")

  set(GUI_BINARY_NAME
      "synergy"
      CACHE STRING "Filename of the GUI binary")

  set(SERVER_BINARY_NAME
      "synergy-server"
      CACHE STRING "Filename of the server binary")

  set(CLIENT_BINARY_NAME
      "synergy-client"
      CACHE STRING "Filename of the client binary")

  set(CORE_BINARY_NAME
      "synergy-core"
      CACHE STRING "Filename of the core binary")

  set(DAEMON_BINARY_NAME
      "synergy-daemon"
      CACHE STRING "Filename of the daemon binary")

  set(LEGACY_BINARY_NAME
      "synergy-legacy"
      CACHE STRING "Filename of the legacy binary")
endmacro()
