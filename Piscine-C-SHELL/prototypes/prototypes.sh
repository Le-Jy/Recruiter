#!/bin/sh

sed -n -E "s/^(struct )*[0-9a-zA-Z]+ *\**[0-9a-zA-Z]+_*[0-9a-zA-Z]*\([0-9a-zA-Z]+.*\)$/&;/p" "$1"
