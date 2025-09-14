#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "Usage: ./hcf.sh num1 num2"
    exit 1
fi

if [ "$2" -eq 0 ]; then
    echo "Exception: division by 0"
    exit 2
fi
if [ "$1" -gt "$2" ]; then
    a=$1
    b=$2
else
    a=$2
    b=$1
fi
while [ "$b" -ne 0 ]; do
    tmp=$b
    b=$(( $a % $b ))
    a=$tmp
done
echo "$a"
exit 0
