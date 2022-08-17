#!/bin/bash 

# This script selects the posix compiler for mingw

# check if user has right permissions
if [ "$(id -u)" != "0" ]; then
    echo "Sorry, you are not root. Please try again using sudo."
    exit 1
fi

# terminate script after first line that fails
set -e

# These files are created by the NDS build, wheras Linux builds install to a system folder.
if [ "$WINE" == "64" ]; then
    # see https://github.com/randombit/botan/issues/2039
    if [ ! -f /usr/bin/x86_64-w64-mingw32-g++-win32 ]; then
        apt-get install -y g++-mingw-w64-x86-64
    fi
    update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix
    # find /usr -name '*mingw*'
elif [ "$WINE" == "32" ]; then
    if [ ! -f /usr/bin/i686-w64-mingw32-g++-win32 ]; then
        apt-get install -y g++-mingw-w64-i686
    fi
    # see https://github.com/randombit/botan/issues/2039
    update-alternatives --set i686-w64-mingw32-g++ /usr/bin/i686-w64-mingw32-g++-posix
fi
