#!/bin/bash

LABS="lab1 lab2 lab3 lab4 lab5 lab6 lab7 lab8"
USERS=$(sed -n 's/^.*@\([^ ][^ ]*\) .*$/\1/p' README.md)

for l in ${LABS}
do
    for u in ${USERS}
    do
	mkdir -p labs/${l}/${u}
	echo "### ${l}/${u}" > labs/${l}/${u}/README.md
    done
done
