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

#include <QString>
#include <qsettings.h>

namespace synergy::gui::license {

class LicenseSettings : public QSettings {
public:
  LicenseSettings() = default;
  virtual ~LicenseSettings() = default;
  void load();
  void save();

  QString serialKey() const { return m_serialKey; }
  void setSerialKey(const QString &serialKey) { m_serialKey = serialKey; }

private:
  QString m_serialKey;
};

} // namespace synergy::gui::license
