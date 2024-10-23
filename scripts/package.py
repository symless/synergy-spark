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

import os, argparse
import lib.bootstrap as bootstrap

APP_NAME = "Synergy"
DESKFLOW_SOURCE_DIR = "odin"
DESKFLOW_BUILD_DIR = "build/odin"
DEFAULT_PREFIX = "synergy"
DIST_DIR = "dist"
VERSION_FILENAME = "odin/VERSION"
TEST_CMD = "synergy-server --version"
PACKAGE_NAME = "synergy"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--leave-test-installed",
        action="store_true",
        help="Leave test package installed",
    )
    args = parser.parse_args()

    bootstrap.ensure_in_venv(__file__)
    bootstrap.add_odin_path(__file__)

    import package

    filename_base = get_env("SYNERGY_PACKAGE_PREFIX", default=DEFAULT_PREFIX)
    version = package.get_app_version(VERSION_FILENAME)

    print("Filename base: ", filename_base)
    print("Version: ", version)

    package.package(
        filename_base,
        version,
        DESKFLOW_BUILD_DIR,
        DIST_DIR,
        TEST_CMD,
        APP_NAME,
        PACKAGE_NAME,
        source_dir=DESKFLOW_SOURCE_DIR,
        leave_test_installed=args.leave_test_installed,
    )


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
