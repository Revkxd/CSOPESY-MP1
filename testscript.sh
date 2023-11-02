#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file_to_compare_to>"
    exit 0
fi

build/a.out < $1 | tee >(diff $2 -)