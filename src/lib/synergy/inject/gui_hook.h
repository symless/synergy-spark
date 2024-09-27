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

#pragma once

#include "synergy/gui/license/LicenseHandler.h"
#include "synergy/gui/license/license_utils.h"

using namespace Qt;

namespace synergy::inject {

inline bool onStart(QMainWindow *parent, AppConfig *appConfig) {
  if (synergy::gui::license::isActivationEnabled()) {
    qDebug("license activation enabled");
    return LicenseHandler::instance().handleStart(parent, appConfig);
  } else {
    qDebug("license activation disabled");
    return true;
  }
}

inline void onSettings(QDialog *parent, QCheckBox *checkBoxEnableTls) {
  if (synergy::gui::license::isActivationEnabled()) {
    return LicenseHandler::instance().handleSettings(parent, checkBoxEnableTls);
  }
}

} // namespace synergy::inject
