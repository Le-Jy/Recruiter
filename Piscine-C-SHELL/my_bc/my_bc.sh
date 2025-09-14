#!/bin/sh

if [ $# -eq 1 ]; then
    echo $(( $1 ))
fi

if [ $# -eq 0 ]; then
    while read str; do
        echo $(( $str ))
    done
fi
