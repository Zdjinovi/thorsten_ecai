(define (problem sysadmin-ssp-8-29-32054)
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
    (running computer6)
    (running computer7)
  ))
  (:metric minimize (total-cost))
)
