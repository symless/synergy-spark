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


def main():
    setup_deskflow()


def setup_deskflow():
    subprocess.run(["git", "clone", "git@github.com:deskflow/deskflow.git"])

    current_dir = os.getcwd()
    try:
        os.chdir("deskflow")
        subprocess.run([sys.executable, "scripts/install_deps.py"] + sys.argv[1:])
    finally:
        os.chdir(current_dir)


if __name__ == "__main__":
    main()
