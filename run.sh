#!/usr/bin/env bash
echo "Building C++ code"
make

echo "Setting python virtual environment"
python3 -m venv uvxamples-venv
set e
source uvxamples-venv/bin/activate
pip install console-menu

echo ":)"
