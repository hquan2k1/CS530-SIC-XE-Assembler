#!/bin/bash

# Run make
make

# Check if make was successful
if [ $? -ne 0 ]; then
    echo "Make failed, exiting."
    exit 1
fi

# Move the assemble file to the output directory
mv assemble ../tests

# Change the directory to the output directory
cd ../tests

# Ask the user for arguments
echo "Please enter the arguments for ./assemble:"
read args

# Run ./assemble with the user-provided arguments from the output directory
./assemble $args
