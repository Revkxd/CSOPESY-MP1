#!/bin/bash

bin="build/a.out"
test_dir="test"
diff_output="./__DIFF__"

txtred=$(tput setaf 1) # Red
txtgrn=$(tput setaf 2) # Green
txtwht=$(tput setaf 7) # White

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
    echo -e "Usage:\n$0 <input_file> <output_file_to_compare_to>\n\tOR\n$0 <algorithm>"
    exit 0
fi

if [ $# -eq 1 ]; then
    inputs=($test_dir/$1/input??.txt)
    outputs=($test_dir/$1/output??.txt)
    for ((i=0; i<${#inputs[@]}; i++)); do
        $bin < ${inputs[$i]} > $diff_output
        diff $diff_output ${outputs[$i]} &> /dev/null
        if [ $? -eq 0 ]; then
            echo "${txtgrn}[PASSED] ${txtwht}${inputs[$i]}"
        else
            echo "${txtred}[FAILED] ${txtwht}${inputs[$i]}"
        fi
    done
fi

if [ $# -eq 2 ]; then
    $bin < $1 | tee $diff_output
    echo -e "\n\n===== Diff ====="
    diff -y --suppress-common-lines $diff_output $2
    echo -e "\n===== End of Diff ====="
fi

rm $diff_output