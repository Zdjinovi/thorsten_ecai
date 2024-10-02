#! /bin/bash

export PATH=../../../probfd-generators/triangle-tireworld/:$PATH

function make-tri {
    generate.py -n $2 > $1.pddl
}

#cmd     pXX n
make-tri p01 1
make-tri p02 2
make-tri p03 3
make-tri p04 4
make-tri p05 5
make-tri p06 6
make-tri p07 7
make-tri p08 8
make-tri p09 9
make-tri p10 10
make-tri p11 11
make-tri p12 12
make-tri p13 13
make-tri p14 14
make-tri p15 15
make-tri p16 16
make-tri p17 17
make-tri p18 18
make-tri p19 19
make-tri p20 20

rm -f generate.sh~