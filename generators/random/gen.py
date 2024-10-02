#! /usr/bin/env python

# generation of random domain and problem
# use slightly modified FF  for
# 1. random walk
# 2. testing solvability (this is yet to be done)
# 

# basically genreset is almost enougth
# to make sure, we are using FF to test the
# vailidity and solvability

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

import os, sys, re, string

import argparse

parser = argparse.ArgumentParser(add_help=False)
parser.add_argument('-i', type=int, default=20, help='number of initial facts')
parser.add_argument('-a', type=int, default=5, help='number of probabilistic actions')
parser.add_argument('-s', type=int, default=5, help='number of predicates')
parser.add_argument('-d', type=int, default=3, help='number of preconditions')
parser.add_argument('-e', type=int, default=5, help='number of effects')
parser.add_argument('-h', type=float, default=0.05, help='probability of cutoff random walk path probability')
parser.add_argument('-n', type=int, default=0, help='probability of negating preconditions')
parser.add_argument('-p', type=int, default=6, help='number of effects in the probability construct')
parser.add_argument('-r', type=int, default=100, help='random walk length')
parser.add_argument('-m', type=int, default=50, help='probability of negating effects')
parser.add_argument('-z', type=int, default=19863, help='random seed')
parser.add_argument('-t', type=int, default=5, help='max predicate arity')
parser.add_argument('--domain-file', type=str, default='domain.pddl', help='domain file name')
parser.add_argument('--problem-file', type=str, default='problem.pddl', help='problem file name')

args = parser.parse_args()

found = 0
while(found == 0):
    os.system("rm -f ttt validproblem")
    os.system(f"./genreset -i {args.i} -a {args.a} -s {args.s} -d {args.d} -e {args.e} -h {args.h} -n {args.n} -p {args.p} -r {args.r} -m {args.m} -z {args.z}; ulimit -St 10;  ./ff -o det_domain -f b-problem -r ttt")

    #check valid problem
    if os.path.exists("validproblem"):
        #if os.path.exists("ttt"):
        found = 1
    else:
        args.z += 1

os.system("rm -f ttt action_table a-problem validproblem b-problem det_domain prob_domain prob_domain_reset")
os.system("csplit -f xxx b-problem_reset /problem/")
os.system(f"mv xxx00 {args.problem_file}")
os.system(f"mv xxx01 {args.domain_file}")
