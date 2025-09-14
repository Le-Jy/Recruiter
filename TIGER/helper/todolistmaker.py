import os

os.system("git grep -n 'FIXME: Some code was deleted here' -- '../lib/' '../src/' '../tests' > todolist.md")
