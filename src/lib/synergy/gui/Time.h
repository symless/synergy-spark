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

#pragma once

#include <chrono>

namespace synergy::gui {

class Time {
  using system_clock = std::chrono::system_clock;

public:
  Time();
  system_clock::time_point now();
  bool hasTestTime() const { return m_testStartTime.has_value(); }

private:
  std::optional<std::chrono::seconds> m_testStartTime;
  system_clock::time_point m_realStartTime = system_clock::now();
};

} // namespace synergy::gui
