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

#include "LicenseSettings.h"

#include <QSettings>
#include <QtCore>

namespace synergy::gui::license {

const auto kSerialKeySettingKey = "serialKey";

#if defined(Q_OS_UNIX)
const auto kUnixSystemConfigPath = "/usr/local/etc/";
#endif

QString getSystemSettingsBaseDir();

LicenseSettings::LicenseSettings() {
  m_pUserSettings = new QSettings(QSettings::Scope::UserScope);
  qDebug().noquote() << "user license settings path: "
                     << m_pUserSettings->fileName();

  QSettings::setPath(
      QSettings::Format::IniFormat, QSettings::Scope::SystemScope,
      getSystemSettingsBaseDir());
  m_pSystemSettings = new QSettings(
      QSettings::Format::IniFormat, QSettings::Scope::SystemScope,
      QCoreApplication::organizationName(),
      QCoreApplication::applicationName());
  qDebug().noquote() << "system license settings path: "
                     << m_pSystemSettings->fileName();
}

void LicenseSettings::load() {
  if (m_pSystemSettings->contains(kSerialKeySettingKey)) {
    qDebug("loading serial key from system settings");
    m_serialKey = m_pSystemSettings->value(kSerialKeySettingKey).toString();
  } else if (m_pUserSettings->contains(kSerialKeySettingKey)) {
    qDebug("loading serial key from user settings");
    m_serialKey = m_pUserSettings->value(kSerialKeySettingKey).toString();
  } else {
    qDebug("no serial key found in settings");
  }
}

void LicenseSettings::save() {

  if (m_pSystemSettings->isWritable()) {
    qDebug("saving serial key to system settings");
    m_pSystemSettings->setValue(kSerialKeySettingKey, m_serialKey);
    m_pSystemSettings->sync();
  } else {
    qWarning("not saving serial key to system settings, not writable");
  }

  qDebug("saving serial key to user settings");
  m_pUserSettings->setValue(kSerialKeySettingKey, m_serialKey);
  m_pUserSettings->sync();
}

/**
 * Important: Cloned from upstream `QSettingsProxy.cpp`
 */
QString getSystemSettingsBaseDir() {
#if defined(Q_OS_WIN)
  return QCoreApplication::applicationDirPath();
#elif defined(Q_OS_UNIX)
  // Qt already adds application and filename to the end of the path.
  // On macOS, it would be nice to use /Library dir, but qt has no elevate
  // system.
  return kUnixSystemConfigPath;
#else
#error "unsupported platform"
#endif
}

} // namespace synergy::gui::license
