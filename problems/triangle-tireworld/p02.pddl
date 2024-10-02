(define (problem triangle-tire-2)
    (:domain triangle-tire)
    (:objects l-1-1
              l-1-2
              l-1-3
              l-1-4
              l-1-5
              l-2-1
              l-2-2
              l-2-3
              l-2-4
              l-3-1
              l-3-2
              l-3-3
              l-4-1
              l-4-2
              l-5-1
              - location
    )
    (:init (vehicle-at l-1-1)
           (not-flattire)
           (road l-1-1 l-1-2)
           (road l-1-2 l-1-3)
           (road l-1-1 l-2-1)
           (road l-2-1 l-3-1)
           (road l-1-2 l-2-2)
           (road l-2-1 l-1-2)
           (road l-3-1 l-2-2)
           (road l-2-2 l-1-3)
           (road l-1-3 l-1-4)
           (road l-1-4 l-1-5)
           (road l-1-3 l-2-3)
           (road l-2-3 l-3-3)
           (road l-1-4 l-2-4)
           (road l-2-3 l-1-4)
           (road l-3-3 l-2-4)
           (road l-2-4 l-1-5)
           (road l-3-1 l-3-2)
           (road l-3-2 l-3-3)
           (road l-3-1 l-4-1)
           (road l-4-1 l-5-1)
           (road l-3-2 l-4-2)
           (road l-4-1 l-3-2)
           (road l-5-1 l-4-2)
           (road l-4-2 l-3-3)
           (spare-in l-2-1)
           (spare-in l-2-2)
           (spare-in l-3-1)
           (spare-in l-2-3)
           (spare-in l-2-4)
           (spare-in l-3-3)
           (spare-in l-4-1)
           (spare-in l-4-2)
           (spare-in l-5-1)
    )
    (:goal (vehicle-at l-1-5))
    (:metric minimize (total-cost))
)
