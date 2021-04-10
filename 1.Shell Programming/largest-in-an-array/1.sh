#!/bin/bash

#Using Loops

echo "Enter the no. of elements:"
read n

echo "Enter $n elements:"
for (( i=0;i<$n;i++ ))
    do
        read A[$i]
    done

max=${A[0]}
for (( i=1;i<$n;i++ ))
    do
        if [ ${A[$i]} -gt $max ]
            then
                max=${A[$i]}
            fi
    done

echo "Largest no. = $max"