/*
 * Synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2015 Symless Ltd.
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

#include "synergy/gui/constants.h"
#include "synergy/gui/license/LicenseSettings.h"
#include "synergy/gui/license/license_utils.h"
#include "synergy/license/License.h"
#include "synergy/license/Product.h"

class AppConfig;
class QMainWindow;
class QDialog;
class QCheckBox;

/**
 * @brief A convenience wrapper for `License` that provides Qt signals, etc.
 */
class LicenseHandler : public QObject {
  Q_OBJECT

  using License = synergy::license::License;
  using SerialKey = synergy::license::SerialKey;

public:
  enum class ChangeSerialKeyResult {
    kSuccess,
    kFatal,
    kUnchanged,
    kInvalid,
    kExpired,
  };

  static LicenseHandler &instance();

  void load();
  void save();
  Product::Edition productEdition() const;
  const License &license() const;
  void validate() const;
  QString productName() const;
  ChangeSerialKeyResult changeSerialKey(const QString &hexString);
  void setEnabled(bool enabled) { m_enabled = enabled; }
  bool handleStart(QMainWindow *parent, AppConfig *appConfig);
  void handleSettings(QDialog *parent, QCheckBox *checkBoxEnableTls) const;
  void checkTlsCheckBox(
      QDialog *parent, QCheckBox *checkBoxEnableTls, bool showDialog) const;
  void updateMainWindow() const;
  bool showActivationDialog(QMainWindow *parent, AppConfig *appConfig);

signals:
  void serialKeyChanged(const QString &serialKey) const;
  void invalidLicense() const;

private:
  bool m_enabled = synergy::gui::license::isActivationEnabled();
  License m_license = License::invalid();
  synergy::gui::license::LicenseSettings m_settings;
  QMainWindow *m_mainWindow = nullptr;
  AppConfig *m_appConfig = nullptr;
};
