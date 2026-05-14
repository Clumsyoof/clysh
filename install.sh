#!/bin/bash
set -e

echo "===Building clumsyshell==="

if [ -d "build" ]; then
    echo "[1/4] Cleaning old build files..."
    rm -rf build/
else
    echo "[1/4] No old build files found. Proceeding..."
fi

echo "[2/4] Configuring CMake..."
cmake -S . -B build

echo "[3/4] Compiling source code..."
cmake --build build

echo "[4/4] Installing to system (this will prompt for sudo)..."
sudo cmake --install build

echo "=== Installation Complete ==="
echo "Type clysh to run."
