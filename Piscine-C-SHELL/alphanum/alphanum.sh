#!/bin/sh

while IFS= read -r stdin; do
  if  $(echo "$stdin" | grep -q "^[[:space:]]*$"); then
    echo "it is empty"
  elif $(echo "$stdin" | grep -q "^[0-9]$"); then
    echo "it is a digit"
  elif $(echo "$stdin" | grep -q "^[0-9]*$"); then
    echo "it is a number"
  elif $(echo "$stdin" | grep -q "^[a-zA-Z]*$"); then
    echo "it is a word"
  elif $(echo "$stdin" | grep -q "^[a-zA-Z0-9]*$"); then
    echo "it is an alphanum"
  else
    echo "it is too complicated"
    exit 0
  fi
done
