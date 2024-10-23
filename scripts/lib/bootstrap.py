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

import sys, os, subprocess, venv

VENV_DIR = ".venv"
ODIN_DIR = "odin"


def add_odin_path(script):
    path = os.path.abspath(os.path.join(os.path.dirname(script), f"../{ODIN_DIR}/scripts"))
    if not os.path.exists(path):
        raise RuntimeError(f"Path does not exist: {path}")

    sys.path.insert(
        0,
        os.path.abspath(path),
    )


def ensure_in_venv(script):
    if in_venv():
        print(f"Running in venv, executable: {sys.executable}", flush=True)
    else:
        print(f"Using virtual environment for: {script}", flush=True)
        run_in_venv(script)


def run_in_venv(script):
    venv.create(VENV_DIR, with_pip=True)
    result = subprocess.run([get_python_executable(), script] + sys.argv[1:])
    sys.exit(result.returncode)


def in_venv():
    """Returns True if the script is running in a Python virtual environment."""
    return sys.prefix != sys.base_prefix


def get_python_executable(binary="python"):
    if sys.platform == "win32":
        return os.path.join(VENV_DIR, "Scripts", binary)
    else:
        return os.path.join(VENV_DIR, "bin", binary)
