#! /bin/bash

export PATH=../../../probfd-generators/elevators/:$PATH

cp ../../../probfd-generators/elevators/domain.pddl ./domain.pddl

function make-elevators {
    elevators $6 $2 $3 $4 $5 0.3333 > $1.pddl
}

# n = floors, m = positions, e = elevators, c = coins

#cmd           pXX  n  m e  c  seed
make-elevators p01  3  6 3  5 21192
make-elevators p02  3  6 4  5 17938
make-elevators p03  3  7 4  5 27049
make-elevators p04  3  7 4  6 24676
make-elevators p05  3  8 4  6  1096
make-elevators p06  3  8 4  7  4968
make-elevators p07  3  8 5  7 21143
make-elevators p08  3  9 5  7 29838
make-elevators p09  3  9 5  8 21687
make-elevators p10  3 10 5  8 25489
make-elevators p11  3 10 5  9  3382
make-elevators p12  3 11 5  9 17332
make-elevators p13  3 11 5 10 15003
make-elevators p14  3 12 5 10  9142
make-elevators p15  3 12 5 11 22270
make-elevators p16  4  7 5  7 33844
make-elevators p17  4  8 5  7 47010
make-elevators p18  4  8 5  8 17133
make-elevators p19  4  9 5  8  3959
make-elevators p20  4  9 5  9 46335

rm -f generate.sh~