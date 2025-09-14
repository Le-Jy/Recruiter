#!/bin/sh

dir="/etc/passwd"
for ids in "$dir"; do
  cut -d ":" -f 3,3 "$ids" | sort -nru
done
