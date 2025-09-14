#!/bin/sh

if [ "$#" -ne 1 ]; then
    echo "Sorry, expected 1 argument but $# were passed"
    exit 1
fi

if ! test -f "$1"; then
    echo "$1:"
    echo "\tis not a valid file"
    exit 2
else
    cat "$1"
    exit 0
fi
