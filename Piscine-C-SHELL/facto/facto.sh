#!/bin/sh

if [ "$#" -ne 1 ]; then
    exit 1
fi
i=$1
res=1
while [ "$i" -ge 1 ]; do
    res=$(( $res * $i ))
    i=$(( $i - 1 ))
done
echo "$res"
exit 0
