#!/bin/bash

echo "Enter two nos."
read n1
read n2
echo "Enter the operator"
read op

case $op in
        '+' ) echo "Addition=$((n1+n2))"
                ;;
        '-' ) echo "Subraction=$((n1-n2))"
                ;;
        '*' ) echo "Product=$((n1*n2))"
                ;;
        '/' ) echo "Division=$((n1/n2))"
                ;;
        * ) echo "Invalid operator"
                ;;
        esac