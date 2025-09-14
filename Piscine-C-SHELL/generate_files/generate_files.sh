#!/bin/bash

filename="default"
number=1
extension="txt"

while [ "$#" -gt 0 ]; do
    if [ "$1" = "-f" ] || [ "$1" = "--filename" ]; then
        filename="$2"
        shift 2
    elif [ "$1" = "-n" ] || [ "$1" = "--number" ]; then
        number="$2"
        shift 2
    elif [ "$1" = "-e" ] || [ "$1" = "--extension" ]; then
        extension="$2"
        shift 2
    else
        exit 1
    fi
done

i=1

while [ "$i" -le "$number" ]; do
    touch -- "$filename"-"$i"."$extension"
    i=$(( $i + 1 ))
done
