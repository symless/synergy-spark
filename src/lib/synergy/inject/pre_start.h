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

#include "synergy/gui/ActivationDialog.h"
#include "synergy/gui/license/LicenseHandler.h"
#include "synergy/gui/license/license_utils.h"

#include <QtCore>
#include <qdebug.h>

namespace synergy::inject {

inline bool preStart(AppConfig *appConfig) {

  // qRegisterMetaType<Edition>("Edition");

  if (!synergy::gui::license::isActivationEnabled()) {
    qDebug("license activation disabled");
    return true;
  }

  qDebug("license activation enabled");
  LicenseHandler licenseHandler;
  const auto &license = licenseHandler.license();

  if (license.isValid()) {
    qInfo("license is valid");
    return true;
  }

  qInfo("license not valid, showing activation dialog");
  ActivationDialog dialog(nullptr, *appConfig, licenseHandler);
  const auto result = dialog.exec();
  if (result == QDialog::Accepted) {
    qDebug("license activation dialog accepted");
    return true;
  } else {
    qWarning("license activation dialog declined, exiting");
    return false;
  }
}

} // namespace synergy::inject
