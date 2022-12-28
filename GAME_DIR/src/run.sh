#!/bin/bash

# Resolve the symbolic link and extract the directory part of the real path
script_dir=$(dirname "$(readlink -f "$0")")

# Change to the script directory
cd "$script_dir"

# Run the program
./game