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
import argparse
import lib.bootstrap as bootstrap

DESKFLOW_DIR = "deskflow"


def main():
    bootstrap.ensure_in_venv(__file__)
    setup_deskflow()


# Using CMake `FetchContent` would be nice, but that doesn't allow us to run the `install_deps.py`
# script before configuring, which is necessary to install the dependencies before running CMake.
# With `FetchContent`, there may be a way of running `install_deps.py`` before populating,
# but it seemed quite complex and potentially required upstream changes. This approach seems
# to be simpler and easier to maintain.
def setup_deskflow():
    if not os.getenv("CI"):
        subprocess.run(
            [
                "git",
                "submodule",
                "update",
                "--init",
                "--recursive",
            ]
        )

    current_dir = os.getcwd()
    try:
        os.chdir(DESKFLOW_DIR)
        subprocess.run([sys.executable, "scripts/install_deps.py"] + sys.argv[1:])
    finally:
        os.chdir(current_dir)


if __name__ == "__main__":
    main()
