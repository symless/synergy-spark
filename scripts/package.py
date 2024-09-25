#!/usr/bin/env python3

# Synergy -- mouse and keyboard sharing utility
# Copyright (C) 2024 Symless Ltd.
#
# This package is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# found in the file LICENSE that should have accompanied this file.
#
# This package is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import subprocess
import sys
import os

DESKFLOW_DIR = "deskflow"
DEFAULT_PREFIX = "synergy"


def main():
    args = [
        "--filename-base",
        get_env("SYNERGY_PACKAGE_PREFIX", default=DEFAULT_PREFIX),
        "--build-dir",
        "../build/deskflow",
        "--dist-dir",
        "../dist",
    ]

    current_dir = os.getcwd()
    try:
        os.chdir(DESKFLOW_DIR)
        subprocess.run([sys.executable, "scripts/package.py"] + args)
    finally:
        os.chdir(current_dir)


def get_env(name, required=True, default=None):
    value = os.getenv(name)
    if value:
        value = value.strip()

    if not value:
        if default:
            return default
        elif required:
            raise ValueError(f"Required env var not set: {name}")

    return value


if __name__ == "__main__":
    main()
