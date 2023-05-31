#!/bin/bash

if [ ! -e data/$1.txt ]; then
    echo $1 $(($RANDOM % $1 + 1)) > data/$1.txt
    for i in $(seq 1 $1); do
        echo -n "$RANDOM " >> data/$1.txt
    done
    echo >> data/$1.txt
fi
