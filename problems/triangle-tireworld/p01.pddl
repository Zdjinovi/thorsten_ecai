(define (problem triangle-tire-1)
    (:domain triangle-tire)
    (:objects l-1-1
              l-1-2
              l-1-3
              l-2-1
              l-2-2
              l-3-1
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
           (spare-in l-2-1)
           (spare-in l-2-2)
           (spare-in l-3-1)
    )
    (:goal (vehicle-at l-1-3))
    (:metric minimize (total-cost))
)
