#! /usr/bin/env python3

import argparse

parser = argparse.ArgumentParser(description="Triangle-Tireworld Generator")
parser.add_argument('-n', type=int, required=True, help='Problem size')
args = parser.parse_args()

n = args.n

spare_tires = []
edges = []

def generateTriangle(x, y):
    edges.append(((x, y), (x+1, y)))
    edges.append(((x+1, y), (x+2, y)))

    edges.append(((x, y), (x, y+1)))
    edges.append(((x, y+1), (x, y+2)))
    edges.append(((x+1, y), (x+1, y+1)))

    edges.append(((x, y+1), (x+1, y)))
    edges.append(((x, y+2), (x+1, y+1)))
    edges.append(((x+1, y+1), (x+2, y)))

    spare_tires.append((x, y+1))
    spare_tires.append((x+1, y+1))
    spare_tires.append((x, y+2))

for y in range(0, n):
    for x in range(0, n - y):
        generateTriangle(2 * x, 2 * y)

print(f"(define (problem triangle-tire-{n})")
print("    (:domain triangle-tire)")
print("    (:objects ", end="")

for y in range(0, 2*n+1):
    for x in range(0, 2*n-y+1):
        if x != 0 or y != 0:
            print("              ", end="")
        print(f"l-{y+1}-{x+1}")

print("              - location")
print("    )")
print("    (:init (vehicle-at l-1-1)")
print("           (not-flattire)")
for r_start, rend in edges:
    sx, sy = r_start
    ex, ey = rend
    print(f"           (road l-{sy+1}-{sx+1} l-{ey+1}-{ex+1})")
for tx, ty in spare_tires:
    print(f"           (spare-in l-{ty+1}-{tx+1})")
print("    )")
print(f"    (:goal (vehicle-at l-1-{2*n+1}))")
print("    (:metric minimize (total-cost))")
print(")")

