#!/bin/bash

echo "Enter two strings"
read s1
read s2
s3=$s1$s2
echo "Conctenated string=$s3"
echo "Length=${#s3}"