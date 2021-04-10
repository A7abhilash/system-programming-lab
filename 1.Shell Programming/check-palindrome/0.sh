#!/bin/bash
echo "Enter a string"
read s1

len=${#s1}
for ((i=$len-1;i>=0;i--))
        do
                s2=$s2${s1:i:1}
        done

echo "Reversed string: $s2"

if [ $s1 == $s2 ]; then
        echo "Palindrome"
else echo "Non palindrome"
fi