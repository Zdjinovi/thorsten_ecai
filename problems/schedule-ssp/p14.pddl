(define (problem p14)
  (:domain p14-dom)
  (:objects )
  (:init 
         (current-phase Arrivals-and-updating)
         (current-timestep U0)
         (need-to-process-arrivals C0)
         (need-to-process-arrivals C1)
         (need-to-process-arrivals C2)
         (available P0)
         (available P1)
         (available P2)
         (available P3)
         (available P4)
         (next-timestep U0 U1)
         (next-timestep U1 U2)
         (next-timestep U2 U3)
         (next-timestep U3 U0)
  )
  (:goal (and
      (served C0)
      (served C1)
      (served C2)
  ))
  (:metric minimize (total-cost))
)
