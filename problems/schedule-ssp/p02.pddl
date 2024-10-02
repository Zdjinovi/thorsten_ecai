(define (problem p02)
  (:domain p02-dom)
  (:objects )
  (:init 
         (current-phase Arrivals-and-updating)
         (current-timestep U0)
         (need-to-process-arrivals C0)
         (available P0)
         (available P1)
         (available P2)
         (available P3)
         (next-timestep U0 U1)
         (next-timestep U1 U2)
         (next-timestep U2 U3)
         (next-timestep U3 U4)
         (next-timestep U4 U5)
         (next-timestep U5 U6)
         (next-timestep U6 U7)
         (next-timestep U7 U8)
         (next-timestep U8 U9)
         (next-timestep U9 U10)
         (next-timestep U10 U11)
         (next-timestep U11 U12)
         (next-timestep U12 U13)
         (next-timestep U13 U14)
         (next-timestep U14 U15)
         (next-timestep U15 U16)
         (next-timestep U16 U17)
         (next-timestep U17 U18)
         (next-timestep U18 U19)
         (next-timestep U19 U20)
         (next-timestep U20 U0)
  )
  (:goal (and
      (served C0)
  ))
  (:metric minimize (total-cost))
)
