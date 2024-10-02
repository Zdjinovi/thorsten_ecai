import os
import itertools
import random

random.seed(13)

loop_nums = [
    # set([2, 3, 4]),
    set([2]),
    set([6, 7, 8, 9, 10, 11, 12]),
    set([3, 4, 5]),
    set([5, 6, 7, 8, 9, 10, 11]),
    # set([21192, 17938, 27049]) # random 400 16bit int seed for each combination
]

# Generate all combinations
combinations = itertools.product(*loop_nums)

i = 1
# Print each combination
for combination in combinations:
    n,  m, e, c = combination
    
    for _ in range(4): # generate some random seeds for each setting
	    seed = random.getrandbits(16)
	    # print(f'make-elevators p{i}', n, m, e, c, seed) # need to put a random seed each line here instead of the list
	    os.system(f"./elevators {seed} {n} {m} {e} {c} 0.3333 > p{i}.pddl")
	    i+=1

# os.system("./elevators 17332 2 4 2 3 0.3333 > p2.pddl")
