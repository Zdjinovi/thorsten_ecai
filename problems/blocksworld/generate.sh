#! /bin/bash

export PATH=../../../probfd-generators/blocksworld/:$PATH

function make-bw {
   blocksworld -c $2 -C $3 $1 `bwstates -r $5 -s 2 -n $4` \
   1> $1.pddl 2> $1-domain.pddl
}

#cmd    pXX c C  n seed
make-bw p01 1 1  6 38749
make-bw p02 3 2  6  8231 
make-bw p03 1 1  7 19173
make-bw p04 3 2  7 46277
make-bw p05 1 1  8 35947
make-bw p06 3 2  8 11139
make-bw p07 1 1  9 29705
make-bw p08 3 2  9 39274
make-bw p09 1 1 10 35718
make-bw p10 3 2 10  4924
make-bw p11 1 1 11  7471
make-bw p12 3 2 11 48371
make-bw p13 1 1 12 10903
make-bw p14 3 2 12 26073
make-bw p15 1 1 13 42855
make-bw p16 3 2 13 19842
make-bw p17 1 1 14 43267
make-bw p18 3 2 14 45578
make-bw p19 1 1 15 15927
make-bw p20 3 2 15 35814
#make-bw p21 1 1 16 44180
#make-bw p22 3 2 16 23147
#make-bw p23 1 1 17  2002
#make-bw p24 3 2 17 14392

rm -f generate.sh~
