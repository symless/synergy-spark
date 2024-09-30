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

#include "LicenseHandler.h"

#include "ActivationDialog.h"
#include "constants.h"
#include "dialogs/UpgradeDialog.h"
#include "gui/config/AppConfig.h"
#include "synergy/gui/license/license_utils.h"
#include "synergy/license/Product.h"

#include <QAction>
#include <QCheckBox>
#include <QCoreApplication>
#include <QDebug>
#include <QDialog>
#include <QMainWindow>
#include <QMenuBar>
#include <QObject>
#include <QProcessEnvironment>
#include <QTimer>
#include <QtCore>
#include <chrono>

using namespace std::chrono;
using namespace synergy::gui::license;
using License = synergy::license::License;

bool LicenseHandler::handleStart(QMainWindow *parent, AppConfig *appConfig) {
  m_mainWindow = parent;
  m_appConfig = appConfig;

  if (m_mainWindow == nullptr) {
    qFatal("main window not set");
  }

  if (m_appConfig == nullptr) {
    qFatal("app config not set");
  }

  const auto serialKeyAction = new QAction("Change serial key", parent);
  QObject::connect(
      serialKeyAction, &QAction::triggered, [this] { showActivationDialog(); });

  const auto licenseMenu = new QMenu("License");
  licenseMenu->addAction(serialKeyAction);
  parent->menuBar()->addAction(licenseMenu->menuAction());

  if (!loadSettings()) {
    qCritical("failed to load license settings");
    return false;
  }

  if (m_license.isExpired()) {
    qInfo("license is expired, showing activation dialog");
    return showActivationDialog();
  }

  if (m_license.isValid()) {
    qInfo("license is valid, continuing with start");
    updateApp();
    return true;
  }

  qInfo("license not valid, showing activation dialog");
  return showActivationDialog();
}

void LicenseHandler::handleSettings(
    QDialog *parent, QCheckBox *checkBoxEnableTls) const {

  const auto onTlsToggle = [this, parent, checkBoxEnableTls] {
    qDebug("tls checkbox toggled");
    checkTlsCheckBox(parent, checkBoxEnableTls, true);
  };

  QObject::connect(checkBoxEnableTls, &QCheckBox::toggled, onTlsToggle);

  checkTlsCheckBox(parent, checkBoxEnableTls, false);
}

bool LicenseHandler::loadSettings() {
  using enum SetSerialKeyResult;

  m_settings.load();

  const auto serialKey = m_settings.serialKey();
  if (!serialKey.isEmpty()) {
    const auto result = setLicense(m_settings.serialKey(), true);
    if (result != SetSerialKeyResult::kSuccess) {
      qWarning("set serial key failed, showing activation dialog");
      showActivationDialog();
      return false;
    }
  }

  return true;
}

void LicenseHandler::saveSettings() {
  const auto hexString = m_license.serialKey().hexString;
  m_settings.setSerialKey(QString::fromStdString(hexString));
  m_settings.save();
}

bool LicenseHandler::showActivationDialog() {
  ActivationDialog dialog(m_mainWindow, *m_appConfig, *this);
  const auto result = dialog.exec();
  if (result == QDialog::Accepted) {
    saveSettings();
    updateApp();
    qDebug("license activation dialog accepted");
    return true;
  } else {
    qWarning("license activation dialog declined");
    return false;
  }
}

void LicenseHandler::updateApp() const {
  const auto productName = QString::fromStdString(m_license.productName());
  qDebug("updating main window title: %s", qPrintable(productName));
  m_mainWindow->setWindowTitle(m_license.productName().c_str());
  m_appConfig->setTlsEnabled(m_license.isTlsAvailable());
}

void LicenseHandler::checkTlsCheckBox(
    QDialog *parent, QCheckBox *checkBoxEnableTls, bool showDialog) const {
  if (m_license.isTlsAvailable() && checkBoxEnableTls->isChecked()) {
    qDebug("tls not available, showing upgrade dialog");
    checkBoxEnableTls->setChecked(false);

    if (showDialog) {
      UpgradeDialog dialog(parent);
      dialog.showDialog(
          QString("TLS Encryption"),
          QString("Please upgrade to %1 to enable TLS encryption.")
              .arg(synergy::gui::kProProductName));
    }
  }
}

const synergy::license::License &LicenseHandler::license() const {
  return m_license;
}

Product::Edition LicenseHandler::productEdition() const {
  return m_license.productEdition();
}

QString LicenseHandler::productName() const {
  return QString::fromStdString(m_license.productName());
}

/// @param allowExpired If true, allow expired licenses to be set.
///     Useful for passing an expired license to the activation dialog.
LicenseHandler::SetSerialKeyResult
LicenseHandler::setLicense(const QString &hexString, bool allowExpired) {
  using enum LicenseHandler::SetSerialKeyResult;

  if (hexString.isEmpty()) {
    qFatal("serial key is empty");
  }

  qDebug() << "changing serial key to:" << hexString;
  auto serialKey = parseSerialKey(hexString);

  if (serialKey == m_license.serialKey()) {
    qDebug("serial key did not change, ignoring");
    return kUnchanged;
  }

  if (!serialKey.isValid) {
    qDebug() << "invalid serial key, ignoring";
    return kInvalid;
  }

  const auto license = License(serialKey);
  if (!allowExpired && license.isExpired()) {
    qDebug("license is expired, ignoring");
    return kExpired;
  }

  m_license = license;

  if (m_time.hasTestTime()) {
    m_license.setNowFunc([this]() { return m_time.now(); });
  }

  if (!m_license.isExpired() && m_license.isTimeLimited()) {
    auto secondsLeft = m_license.secondsLeft();
    if (secondsLeft.count() < INT_MAX) {
      const auto validateAt = secondsLeft + seconds{1};
      const auto interval = duration_cast<milliseconds>(validateAt);
      QTimer::singleShot(interval, this, &LicenseHandler::validate);
    } else {
      qDebug("license expiry too distant to schedule timer");
    }
  }

  return kSuccess;
}

void LicenseHandler::validate() {
  if (!m_license.isValid()) {
    qDebug("license validation failed, license invalid");
    showActivationDialog();
    return;
  }

  if (m_license.isExpired()) {
    qDebug("license validation failed, license expired");
    showActivationDialog();
    return;
  }

  qDebug("license validation succeeded");
}
