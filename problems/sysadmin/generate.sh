#! /bin/bash

export PATH=../../../probfd-generators/sysAdmin-SSP/:$PATH

#usage: generate-SA [options]
#options:
#  -n n, --nodes=n       number of nodes in the loop
#  -l l, --links=l       number of additional links
#  -s s, --seed=s        random number generator seed (if not using time)
#  -?     --help         display this help and exit

function make-SA {
    generate-SA -n $2 -l $3 -s $4 \
   2> $1.pddl 1> $1-domain.pddl
}

#cmd    pXX    n    l      s
make-SA p01    4    1  14123
make-SA p02    4    2  40127
make-SA p03    5    3  27051
make-SA p04    5    5  31353
make-SA p05    6    7  40384
make-SA p06    6   11  18445
make-SA p07    7   13  32510
make-SA p08    7   17  10930
make-SA p09    8   19    631
make-SA p10    8   29  32054
make-SA p11    9   31  15373
make-SA p12    9   43  27160
make-SA p13   10   47  34795
make-SA p14   10   61  41334
make-SA p15   11   67  36993
make-SA p16   11   79  49847
make-SA p17   12   83  32952
make-SA p18   12   97  695
make-SA p19   13  101  24043
make-SA p20   13  127  49748

rm -f generate.sh~
