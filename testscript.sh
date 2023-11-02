#!/bin/bash

output_file="./__test_output__"

if [ $# -ne 2 ]; then
    echo "Usage: $0 <input_file> <output_file_to_compare_to>"
    exit 0
fi

build/a.out < $1 | tee $output_file
echo -e "\n\n===== Diff ====="
diff -y --suppress-common-lines $output_file $2
rm $output_file
echo -e "\n===== End of Diff ====="