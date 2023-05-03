#!/bin/zsh

for n in {6..15}; do
  echo $n > data/$n.txt
  for i in {1..$n}; do
    for j in {1..$n}; do
        if [[ $i -eq $j ]]; then
          echo -n "100 " >> data/$n.txt
        else
          echo -n "$(($RANDOM % 99 + 1)) " >> data/$n.txt
        fi
    done
    echo >> data/$n.txt
  done
done
