#!/bin/bash

bin="build/a.out"
test_dir="test"
diff_output="./__DIFF__"

txtred=$(tput setaf 1) # Red
txtgrn=$(tput setaf 2) # Green
txtmga=$(tput setaf 5) # Magenta
bold=$(tput bold) # Bold
norm=$(tput sgr0) # Normal

if [ $# -lt 1 ] || [ $# -gt 2 ]; then
    echo -e "Usage:\n$0 <input_file> <output_file_to_compare_to>\n\tOR\n$0 <algorithm>"
    exit 0
fi

if [ $# -eq 1 ] && [ "$1" != "bench" ]; then
    inputs=($test_dir/$1/input??.txt)
    outputs=($test_dir/$1/output??.txt)
    for ((i=0; i<${#inputs[@]}; i++)); do
        $bin < ${inputs[$i]} > $diff_output
        diff $diff_output ${outputs[$i]} &> /dev/null
        if [ $? -eq 0 ]; then
            echo "${txtgrn}${bold}[PASSED] ${norm}${inputs[$i]}"
        else
            echo "${txtred}${bold}[FAILED] ${norm}${inputs[$i]}"
        fi
    done
    rm $diff_output
fi

if [ "$1" = "bench" ]; then
    inputs=($test_dir/$1/*.txt)
    for file in ${inputs[@]}; do
        echo "${txtmga}${bold}[INPUT] ${norm}${file}"
        for i in {0..2}; do
            $bin < $file
        done
        echo -e "\n"
    done
fi

if [ $# -eq 2 ]; then
    $bin < $1 | tee $diff_output
    echo -e "\n\n${txtred}${bold}===== Diff =====${norm}"
    diff -y --suppress-common-lines $diff_output $2
    echo -e "\n${txtred}${bold}===== End of Diff ====="
    rm $diff_output
fi