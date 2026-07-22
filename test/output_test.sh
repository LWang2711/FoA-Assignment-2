#!/usr/bin/env bash

mkdir -p test/test_results

is_failed=0

for test_number in 0 1 2
do
    actual="test/test_results/test${test_number}_actual.txt"
    expected="expected_outputs/test${test_number}_out.txt"

    ./build/a2 \
        < "inputs/test${test_number}.txt" \
        > "$actual"

    if diff -u "${expected}" "${actual}" # returns 0 if nothing is different and 1 if different and greater than 2 if error
    then
        echo "PASS: test${test_number}"
    else
        echo "FAIL: test${test_number}"
        is_failed=1
    fi
done

exit "${is_failed}"
