#!/bin/bash

#Using -a option

echo "Enter the elements of array:"
read -a A

echo "Elements of array are:"
for i in ${A[@]}
    do
        echo $i
    done

max=${A[0]}
for i in ${A[@]}
    do
        if [ $i -gt $max ]
            then
                max=$i
            fi
    done

echo "Largest no. = $max"