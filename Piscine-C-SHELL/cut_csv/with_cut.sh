#!/bin/sh

if [ "$#" -ne 2 ]; then
  exit 1
fi

if [ ! -f "$1" ]; then
  exit 1
fi

[ "$2" -eq "$2" ] 2>/dev/null || exit 1

i=1

while IFS= read -r lines; do
  if [ "$i" -eq "$2" ]; then
    first=$(echo "$lines" | cut -d ";" -f 2)
    second=$(echo "$lines" | cut -d ";" -f 3)
    echo "$first is $second"
    exit 0
  fi
  i=$(( $i + 1 ))
done < "$1" 
exit 1
