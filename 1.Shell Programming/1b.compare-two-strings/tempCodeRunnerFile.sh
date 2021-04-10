#!/bin/bash
echo "Enter two strings"
read s1
read s2
if [ $s1 == $s2 ]; then
        echo "Equal"
elif [ $s1 \> $s2 ]; then
        echo "s1>s2"
else echo "s1<s2"
fi