;; Generated by boxworld generator
;; http://www.cs.rutgers.edu/~jasmuth/boxworld.tar.gz
;; by John Asmuth (jasmuth@cs.rutgers.edu)

(define
 (problem box-p16)
  (:domain box-p16-domain)
  (:objects box0 - box
            box1 - box
            box2 - box
            box3 - box
            box4 - box
            truck0 - truck
            truck1 - truck
            plane0 - plane
            truck2 - truck
            truck3 - truck
            plane1 - plane
            city0 - city
            city1 - city
            city2 - city
            city3 - city
            city4 - city
            city5 - city
            city6 - city
  )
  (:init (box-at-city box0 city5)
         (destination box0 city2)
         (box-at-city box1 city5)
         (destination box1 city6)
         (box-at-city box2 city4)
         (destination box2 city2)
         (box-at-city box3 city5)
         (destination box3 city6)
         (box-at-city box4 city4)
         (destination box4 city2)
         (truck-at-city truck0 city0)
         (truck-at-city truck1 city0)
         (plane-at-city plane0 city0)
         (truck-at-city truck2 city1)
         (truck-at-city truck3 city1)
         (plane-at-city plane1 city1)
         (can-drive city0 city1)
         (can-drive city0 city5)
         (can-drive city0 city4)
         (wrong-drive1 city0 city1)
         (wrong-drive2 city0 city5)
         (wrong-drive3 city0 city4)
         (can-fly city0 city1)
         (can-drive city1 city0)
         (can-drive city1 city5)
         (can-drive city1 city4)
         (wrong-drive1 city1 city0)
         (wrong-drive2 city1 city5)
         (wrong-drive3 city1 city4)
         (can-fly city1 city0)
         (can-drive city2 city3)
         (can-drive city2 city6)
         (can-drive city2 city5)
         (wrong-drive1 city2 city3)
         (wrong-drive2 city2 city6)
         (wrong-drive3 city2 city5)
         (can-drive city3 city2)
         (can-drive city3 city6)
         (can-drive city3 city4)
         (wrong-drive1 city3 city2)
         (wrong-drive2 city3 city6)
         (wrong-drive3 city3 city4)
         (can-drive city4 city0)
         (can-drive city4 city1)
         (can-drive city4 city3)
         (can-drive city4 city5)
         (can-drive city4 city6)
         (wrong-drive1 city4 city0)
         (wrong-drive2 city4 city1)
         (wrong-drive3 city4 city3)
         (can-drive city5 city0)
         (can-drive city5 city1)
         (can-drive city5 city2)
         (can-drive city5 city4)
         (wrong-drive1 city5 city0)
         (wrong-drive2 city5 city1)
         (wrong-drive3 city5 city2)
         (can-drive city6 city2)
         (can-drive city6 city3)
         (can-drive city6 city4)
         (wrong-drive1 city6 city2)
         (wrong-drive2 city6 city3)
         (wrong-drive3 city6 city4)
  )
  (:goal (and
         (box-at-city box0 city2)
         (box-at-city box1 city6)
         (box-at-city box2 city2)
         (box-at-city box3 city6)
         (box-at-city box4 city2)
  ))
  (:metric minimize (total-cost))
)
