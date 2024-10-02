#! /bin/bash

export PATH=../../../probfd-generators/schedule-ssp/:$PATH

# example: schedule -c 2 -u 2 -l 1000 -p 2 -r 10

function make-s {
    schedule -c $2 -u $3 -l $4 -n $1 -p $5 -r $6 \
   1> $1.pddl 2> $1-domain.pddl
}

rm -f p*.pddl

#cmd   pXX  c  u    l p r
make-s p01  1 10   50 2 5
make-s p02  1 20  100 3 5
make-s p03  1 30  150 4 5
make-s p04  1 40  200 5 5
make-s p05  1 50  250 6 5
make-s p06  1 60  300 7 5
make-s p07  2  2   50 3 5
make-s p08  2  3   60 3 5
make-s p09  2  4   70 3 5
make-s p10  2  4   75 4 5
make-s p11  2  5   80 4 5
make-s p12  2  6   90 4 5
make-s p13  2  7  100 4 5
make-s p14  3  3   40 2 5
make-s p15  3  4   50 2 5
make-s p16  3  5   60 2 5
make-s p17  3  5   65 3 5
make-s p18  3  6   70 3 5
make-s p19  3  7   80 3 5
make-s p20  3  8   90 3 5

rm -f generate.sh~