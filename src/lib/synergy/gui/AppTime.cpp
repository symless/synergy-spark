/*
 * synergy -- mouse and keyboard sharing utility
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

#include "AppTime.h"

#include <QtCore>

using system_clock = std::chrono::system_clock;
using time_point = system_clock::time_point;

namespace synergy::gui {

const auto kTestTimeEnvVar = "SYNERGY_TEST_START_TIME";

AppTime::AppTime() {
  m_realStartTime = system_clock::now();
  if (qEnvironmentVariableIsSet(kTestTimeEnvVar)) {
    const auto testTime = qEnvironmentVariable(kTestTimeEnvVar).toLongLong();
    qDebug("setting test time to: %lld", testTime);
    m_testStartTime = std::chrono::seconds{testTime};
  }
}

bool AppTime::hasTestTime() const { return m_testStartTime.has_value(); }

time_point AppTime::now() {
  if (m_testStartTime.has_value()) {
    const auto runtime = system_clock::now() - m_realStartTime;
    return time_point{m_testStartTime.value()} + runtime;
  }
  return system_clock::now();
}

} // namespace synergy::gui
