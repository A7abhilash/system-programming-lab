#!/bin/bash

arr=(10 20 30 40 50)

echo "Array elements: ${arr[@]}"

echo "2nd element: ${arr[1]}"

echo "Array elements from 2nd: ${arr[*]:1}"

echo "Length: ${#arr[*]}"