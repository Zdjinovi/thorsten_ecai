#! /bin/bash

export PATH=../../../generators/probabilistic/elevators/:$PATH

function make-elevators {
    elevators $6 $2 $3 $4 $5 0.3333 > $1.pddl
}

# n = floors, m = positions, e = elevators, c = coins

#cmd           pXX  n  m e c seed
make-elevators p01  2  4 2 3 17332
make-elevators p02  2  4 2 3 15003
make-elevators p03  2  4 2 3 9142
make-elevators p04  3  4 2 4 17938
make-elevators p05  3  4 2 4 27049
make-elevators p06  3  4 2 4 24676
make-elevators p07  4 12 3 9 21687
make-elevators p08  4 12 3 9 25489
make-elevators p09  4 12 3 9 3382
make-elevators p10  3 12 3 9 21687
make-elevators p11  3 12 3 9 25489
make-elevators p12  3 12 3 9 3382
make-elevators p13  3 12 3 9 21687
make-elevators p14  3 12 3 9 25489
make-elevators p15  3 12 3 9 3382
make-elevators p16  3 12 3 9 21687
make-elevators p17  3 12 3 9 25489
make-elevators p18  3 12 3 9 3382
make-elevators p19  3 12 3 9 21687
make-elevators p20  3 12 3 9 25489
make-elevators p21  3 12 3 9 3382
make-elevators p22  3 12 3 9 21687
make-elevators p23  3 12 3 9 25489
make-elevators p24  3 12 3 9 3382
make-elevators p25  3 12 3 9 21687
make-elevators p26  3 12 3 9 25489
make-elevators p27  3 12 3 9 3382
make-elevators p28  3 12 3 9 21687
make-elevators p29  3 12 3 9 25489
make-elevators p30  3 12 3 9 3382

rm -f generate.sh~