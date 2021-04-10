#!/bin/bash

#Using Command Line Arguments(CLA)

echo "CLA= $@"
echo "Length= $#"

max=$1
for i in $@
    do
        if [ $i -gt $max ]
            then
                max=$i
            fi
    done

echo "Largest no. = $max"