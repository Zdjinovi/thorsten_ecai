#! /bin/bash

export PATH=../../../probfd-generators/random/:$PATH

function make-random {
    cd ../../../probfd-generators/random/ &&
    ./gen.py -i $2 -a $3 -s $4 -d $5 -e $6 -h $7 -n $8 -p $9 -r ${10} -m ${11} -z ${12} --domain-file $1.pddl --problem-file $1-domain.pddl  &&
    mv $1-domain.pddl $1.pddl ../../problems/new/random/ &&
    cd ../../problems/new/random/
}

# various parameters are involved
# -i number of initial facts
# -a number of prob actions
# -s number of predicates
# -r random walk length
# -t max predicate arity
# -c max action arity
# -p number of effects in the probability construct
# -e number of effects
# -d number of precondition
# -n probability of negating preconditions
# -m probability of negating effects
# -h probability of cutoff random walk path probability

# cp from README:

#simple difficulty
#- -i 20 -a 5 -s 5 -d 3 -e 3 -h 0.2 -n 0

#middle difficulty
#- -i 20 -a 5 -s 5 -d 5 -e 5 -h 0.2 -n 0

#harder difficulty
#- -i 100 -a 10 -s 10 -d 5 -e 5 -h 0.05 -n 0

#cmd        pXX  i a s d e   h n p   r  m seed
make-random p01 10 3 3 3 3 0.05 0 5 100 50  344
make-random p02 12 4 3 3 3 0.05 0 5 100 50   51
make-random p03 14 4 4 3 3 0.05 0 5 100 50  539
make-random p04 16 4 4 4 3 0.05 0 5 100 50  256
make-random p05 18 4 4 4 4 0.05 0 5 100 50  316
make-random p06 20 4 4 4 4 0.05 0 6 100 50  598
make-random p07 22 5 4 4 4 0.05 0 6 100 50  832
make-random p08 24 5 5 4 4 0.05 0 6 100 50  719
make-random p09 26 5 5 5 4 0.05 0 6 100 50  189
make-random p10 28 5 5 5 5 0.05 0 6 100 50  180
make-random p11 30 5 5 5 5 0.05 0 7 100 50  575
make-random p12 32 6 5 5 5 0.05 0 7 100 50  839
make-random p13 34 6 6 5 5 0.05 0 7 100 50  825
make-random p14 36 6 6 6 5 0.05 0 7 100 50 1000
make-random p15 38 6 6 6 6 0.05 0 7 100 50  860
make-random p16 40 6 6 6 6 0.05 0 8 100 50  374
make-random p17 42 7 6 6 6 0.05 0 8 100 50  771
make-random p18 44 7 7 6 6 0.05 0 8 100 50  427
make-random p19 46 7 7 7 6 0.05 0 8 100 50  975
make-random p20 48 7 7 7 7 0.05 0 8 100 50   34

rm -f generate.sh~