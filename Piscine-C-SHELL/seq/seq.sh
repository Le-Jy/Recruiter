#!/bin/sh

if [ "$#" -ne 3 ]; then
    >&2 echo "Usage: ./seq.sh FIRST INCREMENT LAST"
    exit 1
fi

if [ "$2" -eq 0 ]; then
  exit 1
fi

if [ "$1" -eq "$3" ]; then
    echo "$1"
    exit 0
fi
value=$1
if [ "$1" -gt "$3" ]; then
    if [ "$2" -lt 0 ]; then
        while [ "$value" -ge "$3" ]; do
            echo "$value"
            value=$(( $value + $2 ))
        done
        exit 0
    fi
    exit 1
fi

if [ "$1" -lt "$3" ]; then
    if [ "$2" -gt 0 ]; then
        while [ "$value" -le "$3" ]; do
            echo "$value"
            value=$(( $value + $2 ))
        done
        exit 0
    fi
    exit 1
fi
