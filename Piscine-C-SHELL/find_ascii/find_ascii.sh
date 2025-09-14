[ ! -d "$1" ] && exit 1

for files in "$1"/*; do
  filetype=$(file "$files")
  if echo "$filetype" | grep -q "ASCII"; then
    echo "$filetype"
  fi
done
