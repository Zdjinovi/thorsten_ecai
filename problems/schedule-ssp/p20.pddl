(define (problem p20)
  (:domain p20-dom)
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
         (available P5)
         (next-timestep U0 U1)
         (next-timestep U1 U2)
         (next-timestep U2 U3)
         (next-timestep U3 U4)
         (next-timestep U4 U5)
         (next-timestep U5 U6)
         (next-timestep U6 U7)
         (next-timestep U7 U8)
         (next-timestep U8 U0)
  )
  (:goal (and
      (served C0)
      (served C1)
      (served C2)
  ))
  (:metric minimize (total-cost))
)
