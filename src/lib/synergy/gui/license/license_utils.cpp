/*
 * Synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2024 Symless Ltd.
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "license_utils.h"

#include "gui/string_utils.h"
#include "synergy/license/parse_serial_key.h"

#include <QString>
#include <QtGlobal>

namespace synergy::gui::license {

#ifndef DESKFLOW_LICENSED_PRODUCT
const bool kEnableActivation = true;
#else
const bool kEnableActivation = false;
#endif // SYNERGY_ENABLE_ACTIVATION

bool isActivationEnabled() {
  if (strToTrue(qEnvironmentVariable("SYNERGY_ENABLE_ACTIVATION"))) {
    return true;
  } else {
    return kEnableActivation;
  }
}

synergy::license::SerialKey parseSerialKey(const QString &hexString) {
  try {
    return synergy::license::parseSerialKey(hexString.toStdString());
  } catch (const std::exception &e) {
    qFatal("failed to parse serial key: %s", e.what());
    abort();
  } catch (...) {
    qFatal("failed to parse serial key, unknown error");
    abort();
  }
}

} // namespace synergy::gui::license
