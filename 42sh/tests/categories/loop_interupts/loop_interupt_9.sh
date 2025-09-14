for i in 12 234 3 4; do
    echo $?;
    echo ls;
    for j in 1 2 3; do
            echo OK
            break 2;
    done;
done
