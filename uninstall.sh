#!/bin/bash

if [ "$EUID" -ne 0 ]; then
    echo "Error: Permission Denied."
    exit 1
fi

MANIFEST="build/install_manifest.txt"

if [ ! -f "$MANIFEST" ]; then
    echo "Error: $MANIFEST not found."
    echo "Did you run 'sudo make install' ?"
    exit 1
fi

echo "Uninstalling clumsyshell..."

while IFS= read -r file || [ -n "$file" ]; do
    if [ -f "$file" ] || [ -L "$file" ]; then
        rm -f "$file"
        echo "Removed: $file"
    fi
done < "$MANIFEST"
echo "Cleaning up local build files..."
if [ -d "build" ]; then
    rm -rf build/
    echo "Removed local directory: build/"
else
    echo "No local build/ directory found."
fi

echo "Uninstallation complete!"
