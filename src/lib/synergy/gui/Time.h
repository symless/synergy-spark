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
#include <optional>

namespace synergy::gui {

class Time {
  using time_point = std::chrono::system_clock::time_point;

public:
  Time();
  time_point now();
  bool hasTestTime() const;

private:
  std::optional<std::chrono::seconds> m_testStartTime;
  time_point m_realStartTime = std::chrono::system_clock::now();
};

} // namespace synergy::gui
