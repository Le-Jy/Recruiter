#!/bin/sh

[ "$#" -ne 1 ] && exit 1

! test -f "$1" && exit 1

while IFS= read -r line; do
  nbline=$(echo -n "$line" | wc -m)
  [ "$nbline" -ge 80 ] && printf "%s\n" "$line"
done < "$1"
exit 0
