#!/bin/bash
echo "Enter three numbers"
read s1
read s2
read s3

large=$s1
if [ $s2 -gt $large ]; then
        large=$s2
fi
if [ $s3 -gt $large ]; then
        large=$s3
fi

echo "Largest = $large"