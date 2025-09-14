#!/bin/sh

if [ "$#" -eq 0 ]; then
  extension="txt"
else
  extension="$1"
fi

rm *.$extension || exit 1
