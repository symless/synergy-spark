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
import venv

VENV_DIR = ".venv"
DESKFLOW_DIR = "deskflow"
DESKFLOW_TAG = "decommercialize"


def main():
    if in_venv():
        setup_deskflow()
    else:
        venv.create(VENV_DIR, with_pip=True)
        run_in_venv()


def run_in_venv():
    print("Re-running in virtual environment...")
    subprocess.run([get_python_executable(), __file__] + sys.argv[1:], check=True)


def in_venv():
    """Returns True if the script is running in a Python virtual environment."""
    return sys.prefix != sys.base_prefix


def get_python_executable(binary="python"):
    if sys.platform == "win32":
        return os.path.join(VENV_DIR, "Scripts", binary)
    else:
        return os.path.join(VENV_DIR, "bin", binary)


# Using CMake `FetchContent` would be nice, but that doesn't allow us to run the `install_deps.py`
# script before configuring, which is necessary to install the dependencies before running CMake.
# With `FetchContent`, there may be a way of running `install_deps.py`` before populating,
# but it seemed quite complex and potentially required upstream changes. This approach seems
# to be simpler and easier to maintain.
def setup_deskflow():
    subprocess.run(
        [
            "git",
            "clone",
            "git@github.com:deskflow/deskflow.git",
            DESKFLOW_DIR,
            "--branch",
            DESKFLOW_TAG,
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
