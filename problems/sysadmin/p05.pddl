(define (problem sysadmin-ssp-6-7-40384)
  (:domain sysadmin-ssp)
  (:init (all-updated))
  (:goal (and
    (all-updated)
    (running computer0)
    (running computer1)
    (running computer2)
    (running computer3)
    (running computer4)
    (running computer5)
  ))
  (:metric minimize (total-cost))
)
