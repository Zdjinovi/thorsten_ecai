#! /bin/bash

export PATH=../../../probfd-generators/boxworld/:$PATH

#usage: ./boxworld [-h]
#                  [-b box-count]
#                  [-c city-count]
#                  [-dc drive-cost]
#                  [-fc fly-cost]
#                  [-tlc truck-load-cost]
#                  [-tuc truck-unload-cost]
#                  [-plc plane-load-cost]
#                  [-puc plane-unload-cost]
#                  [-dn domain name]
#                  [-pn problem name]

function make-box {
   boxworld -b $2 -c $3 -dc $4 -fc $5 -pn box-$1 -dn box-$1-domain \
   -tlc $6 -tuc $7 -plc $8 -puc $9 1> $1.pddl 2> $1-domain.pddl
}

#cmd    pXX  b  c dc  fc tlc tuc plc puc 
make-box p01  2  4  5  20   1   1   1   1
make-box p02  3  4  5  20   1   1   1   1
make-box p03  4  4  5  20   1   1   1   1
make-box p04  5  4  5  20   1   1   1   1
make-box p05  6  4  5  20   1   1   1   1
make-box p06  3  5  5  20   1   1   1   1
make-box p07  4  5  5  20   1   1   1   1
make-box p08  5  5  5  20   1   1   1   1
make-box p09  6  5  5  20   1   1   1   1
make-box p10  7  5  5  20   1   1   1   1
make-box p11  4  6  5  20   1   1   1   1
make-box p12  5  6  5  20   1   1   1   1
make-box p13  6  6  5  20   1   1   1   1
make-box p14  7  6  5  20   1   1   1   1
make-box p15  8  6  5  20   1   1   1   1
make-box p16  5  7  5  20   1   1   1   1
make-box p17  6  7  5  20   1   1   1   1
make-box p18  7  7  5  20   1   1   1   1
make-box p19  8  7  5  20   1   1   1   1
make-box p20  9  7  5  20   1   1   1   1

rm -f generate.sh~
