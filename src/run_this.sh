#######################
# QUAN NGUYEN         #
# cssc4550            #
# CS530, Spring 2024  # 
# Assignment 2        #
# makefile            #
#######################

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

# Move the output files to their respective directories based on the file extension
for file in *; do
    case "$file" in
        *.st)
            mv "$file" SYMTAB/
            ;;
        *.e)
            mv "$file" ERROR/
            ;;
        *)
            # Handle any other file extensions or no extension files
            ;;
    esac
done
