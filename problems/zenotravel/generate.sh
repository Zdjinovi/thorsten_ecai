#! /bin/bash

export PATH=../../../probfd-generators/zenotravel/:$PATH

cp ../../../probfd-generators/zenotravel/domain.pddl ./

#usage: zeno [--cities <n>] [--persons <n>] [--aircrafts <n>] [--seed <seed>]
function make-zt {
   zeno --cities $2 --persons $3 --aircrafts $4 --seed $5 \
   > $1-c$2-p$3-a$4-s$5.pddl
}

#cmd    pXX  c  p  a      s
make-zt p01  2  2  2    38
make-zt p02  3  2  2  17462
make-zt p03  3  3  2   3674
make-zt p04  3  2  3  12861
make-zt p05  3  3  3  24056
make-zt p06  4  3  2   6554
make-zt p07  4  3  3  24564
make-zt p08  4  4  3  27436
make-zt p09  4  3  4  29223
make-zt p10  4  4  4   7229
make-zt p11  5  4  3  21350
make-zt p12  5  4  4  14893
make-zt p13  5  5  4  12510
make-zt p14  5  4  5  11709
make-zt p15  5  5  5  24164
make-zt p16  6  5  4   4860
make-zt p17  6  5  5  11053
make-zt p18  6  6  5  12866
make-zt p19  6  5  6  24633
make-zt p20  6  6  6  24874


rm -f generate.sh~
