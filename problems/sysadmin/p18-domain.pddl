(define (domain sysadmin-ssp)
  (:requirements :probabilistic-effects :negative-preconditions :typing)
  (:types computer - object)
  (:constants computer0 computer1 computer2 computer3 computer4 computer5 computer6 computer7 computer8 computer9 computer10 computer11 - computer)
  (:predicates 
    (running ?c - computer)
    (rebooted ?c - computer)
    (evaluate ?c - computer)
    (update-status ?c - computer)
    (one-off ?c - computer)
    (all-on ?c - computer)
    (all-updated)
  )
  (:action reboot
    :parameters (?c - computer)
    :precondition (all-updated)
    :effect (and 
      (increase (total-cost) 1)
      (not (all-updated))
      (evaluate computer0)
      (rebooted ?c)
    )
  )
  (:action evaluate-computer0-rebooted
    :precondition (and
      (evaluate computer0)
      (rebooted computer0)
    )
    :effect (and 
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-all-on
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer6)
      (running computer8)
      (running computer11)
    )
    :effect (and 
      (all-on computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer1
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer2
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer3
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer4
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer5
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer6
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer8
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action evaluate-computer0-off-computer11
    :precondition (and
      (evaluate computer0)
      (not (rebooted computer0))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer0)
      (not (evaluate computer0))
      (evaluate computer1)
    )
  )
  (:action update-status-computer0-rebooted
    :precondition (and
      (update-status computer0)
      (rebooted computer0)
    )
    :effect (and 
      (not (update-status computer0))
      (update-status computer1)
      (not (rebooted computer0))
      (probabilistic 9/10 (running computer0))
    )
  )
  (:action update-status-computer0-all-on
    :precondition (and
      (update-status computer0)
      (not (rebooted computer0))
      (all-on computer0)
    )
    :effect (and 
      (not (update-status computer0))
      (update-status computer1)
      (not (all-on computer0))
      (probabilistic 1/20 (not (running computer0)))
    )
  )
  (:action update-status-computer0-one-off
    :precondition (and
      (update-status computer0)
      (not (rebooted computer0))
      (one-off computer0)
    )
    :effect (and 
      (not (update-status computer0))
      (update-status computer1)
      (not (one-off computer0))
      (probabilistic 1/4 (not (running computer0)))
    )
  )
  (:action evaluate-computer1-rebooted
    :precondition (and
      (evaluate computer1)
      (rebooted computer1)
    )
    :effect (and 
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-all-on
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (running computer0)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer6)
      (running computer8)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer0
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer2
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer3
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer4
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer5
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer6
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer8
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer9
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer10
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action evaluate-computer1-off-computer11
    :precondition (and
      (evaluate computer1)
      (not (rebooted computer1))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer1)
      (not (evaluate computer1))
      (evaluate computer2)
    )
  )
  (:action update-status-computer1-rebooted
    :precondition (and
      (update-status computer1)
      (rebooted computer1)
    )
    :effect (and 
      (not (update-status computer1))
      (update-status computer2)
      (not (rebooted computer1))
      (probabilistic 9/10 (running computer1))
    )
  )
  (:action update-status-computer1-all-on
    :precondition (and
      (update-status computer1)
      (not (rebooted computer1))
      (all-on computer1)
    )
    :effect (and 
      (not (update-status computer1))
      (update-status computer2)
      (not (all-on computer1))
      (probabilistic 1/20 (not (running computer1)))
    )
  )
  (:action update-status-computer1-one-off
    :precondition (and
      (update-status computer1)
      (not (rebooted computer1))
      (one-off computer1)
    )
    :effect (and 
      (not (update-status computer1))
      (update-status computer2)
      (not (one-off computer1))
      (probabilistic 1/4 (not (running computer1)))
    )
  )
  (:action evaluate-computer2-rebooted
    :precondition (and
      (evaluate computer2)
      (rebooted computer2)
    )
    :effect (and 
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-all-on
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (running computer0)
      (running computer1)
      (running computer3)
      (running computer4)
      (running computer7)
      (running computer10)
    )
    :effect (and 
      (all-on computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer0
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer1
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer3
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer4
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer7
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action evaluate-computer2-off-computer10
    :precondition (and
      (evaluate computer2)
      (not (rebooted computer2))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer2)
      (not (evaluate computer2))
      (evaluate computer3)
    )
  )
  (:action update-status-computer2-rebooted
    :precondition (and
      (update-status computer2)
      (rebooted computer2)
    )
    :effect (and 
      (not (update-status computer2))
      (update-status computer3)
      (not (rebooted computer2))
      (probabilistic 9/10 (running computer2))
    )
  )
  (:action update-status-computer2-all-on
    :precondition (and
      (update-status computer2)
      (not (rebooted computer2))
      (all-on computer2)
    )
    :effect (and 
      (not (update-status computer2))
      (update-status computer3)
      (not (all-on computer2))
      (probabilistic 1/20 (not (running computer2)))
    )
  )
  (:action update-status-computer2-one-off
    :precondition (and
      (update-status computer2)
      (not (rebooted computer2))
      (one-off computer2)
    )
    :effect (and 
      (not (update-status computer2))
      (update-status computer3)
      (not (one-off computer2))
      (probabilistic 1/4 (not (running computer2)))
    )
  )
  (:action evaluate-computer3-rebooted
    :precondition (and
      (evaluate computer3)
      (rebooted computer3)
    )
    :effect (and 
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-all-on
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (running computer2)
      (running computer4)
      (running computer5)
      (running computer6)
      (running computer7)
      (running computer8)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer2
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer4
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer5
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer6
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer7
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer8
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer9
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer10
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action evaluate-computer3-off-computer11
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (evaluate computer4)
    )
  )
  (:action update-status-computer3-rebooted
    :precondition (and
      (update-status computer3)
      (rebooted computer3)
    )
    :effect (and 
      (not (update-status computer3))
      (update-status computer4)
      (not (rebooted computer3))
      (probabilistic 9/10 (running computer3))
    )
  )
  (:action update-status-computer3-all-on
    :precondition (and
      (update-status computer3)
      (not (rebooted computer3))
      (all-on computer3)
    )
    :effect (and 
      (not (update-status computer3))
      (update-status computer4)
      (not (all-on computer3))
      (probabilistic 1/20 (not (running computer3)))
    )
  )
  (:action update-status-computer3-one-off
    :precondition (and
      (update-status computer3)
      (not (rebooted computer3))
      (one-off computer3)
    )
    :effect (and 
      (not (update-status computer3))
      (update-status computer4)
      (not (one-off computer3))
      (probabilistic 1/4 (not (running computer3)))
    )
  )
  (:action evaluate-computer4-rebooted
    :precondition (and
      (evaluate computer4)
      (rebooted computer4)
    )
    :effect (and 
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-all-on
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer5)
      (running computer6)
      (running computer7)
      (running computer8)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer0
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer1
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer2
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer5
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer6
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer7
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer8
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer10
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action evaluate-computer4-off-computer11
    :precondition (and
      (evaluate computer4)
      (not (rebooted computer4))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer4)
      (not (evaluate computer4))
      (evaluate computer5)
    )
  )
  (:action update-status-computer4-rebooted
    :precondition (and
      (update-status computer4)
      (rebooted computer4)
    )
    :effect (and 
      (not (update-status computer4))
      (update-status computer5)
      (not (rebooted computer4))
      (probabilistic 9/10 (running computer4))
    )
  )
  (:action update-status-computer4-all-on
    :precondition (and
      (update-status computer4)
      (not (rebooted computer4))
      (all-on computer4)
    )
    :effect (and 
      (not (update-status computer4))
      (update-status computer5)
      (not (all-on computer4))
      (probabilistic 1/20 (not (running computer4)))
    )
  )
  (:action update-status-computer4-one-off
    :precondition (and
      (update-status computer4)
      (not (rebooted computer4))
      (one-off computer4)
    )
    :effect (and 
      (not (update-status computer4))
      (update-status computer5)
      (not (one-off computer4))
      (probabilistic 1/4 (not (running computer4)))
    )
  )
  (:action evaluate-computer5-rebooted
    :precondition (and
      (evaluate computer5)
      (rebooted computer5)
    )
    :effect (and 
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-all-on
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer6)
      (running computer7)
      (running computer8)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer0
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer1
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer2
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer3
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer4
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer6
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer7
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer8
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer9
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer10
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action evaluate-computer5-off-computer11
    :precondition (and
      (evaluate computer5)
      (not (rebooted computer5))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer5)
      (not (evaluate computer5))
      (evaluate computer6)
    )
  )
  (:action update-status-computer5-rebooted
    :precondition (and
      (update-status computer5)
      (rebooted computer5)
    )
    :effect (and 
      (not (update-status computer5))
      (update-status computer6)
      (not (rebooted computer5))
      (probabilistic 9/10 (running computer5))
    )
  )
  (:action update-status-computer5-all-on
    :precondition (and
      (update-status computer5)
      (not (rebooted computer5))
      (all-on computer5)
    )
    :effect (and 
      (not (update-status computer5))
      (update-status computer6)
      (not (all-on computer5))
      (probabilistic 1/20 (not (running computer5)))
    )
  )
  (:action update-status-computer5-one-off
    :precondition (and
      (update-status computer5)
      (not (rebooted computer5))
      (one-off computer5)
    )
    :effect (and 
      (not (update-status computer5))
      (update-status computer6)
      (not (one-off computer5))
      (probabilistic 1/4 (not (running computer5)))
    )
  )
  (:action evaluate-computer6-rebooted
    :precondition (and
      (evaluate computer6)
      (rebooted computer6)
    )
    :effect (and 
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-all-on
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer7)
      (running computer8)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer0
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer1
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer2
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer3
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer4
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer5
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer7
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer8
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer9
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer10
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action evaluate-computer6-off-computer11
    :precondition (and
      (evaluate computer6)
      (not (rebooted computer6))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer6)
      (not (evaluate computer6))
      (evaluate computer7)
    )
  )
  (:action update-status-computer6-rebooted
    :precondition (and
      (update-status computer6)
      (rebooted computer6)
    )
    :effect (and 
      (not (update-status computer6))
      (update-status computer7)
      (not (rebooted computer6))
      (probabilistic 9/10 (running computer6))
    )
  )
  (:action update-status-computer6-all-on
    :precondition (and
      (update-status computer6)
      (not (rebooted computer6))
      (all-on computer6)
    )
    :effect (and 
      (not (update-status computer6))
      (update-status computer7)
      (not (all-on computer6))
      (probabilistic 1/20 (not (running computer6)))
    )
  )
  (:action update-status-computer6-one-off
    :precondition (and
      (update-status computer6)
      (not (rebooted computer6))
      (one-off computer6)
    )
    :effect (and 
      (not (update-status computer6))
      (update-status computer7)
      (not (one-off computer6))
      (probabilistic 1/4 (not (running computer6)))
    )
  )
  (:action evaluate-computer7-rebooted
    :precondition (and
      (evaluate computer7)
      (rebooted computer7)
    )
    :effect (and 
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-all-on
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer8)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer0
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer1
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer2
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer3
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer4
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer5
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer8
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer9
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer10
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action evaluate-computer7-off-computer11
    :precondition (and
      (evaluate computer7)
      (not (rebooted computer7))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer7)
      (not (evaluate computer7))
      (evaluate computer8)
    )
  )
  (:action update-status-computer7-rebooted
    :precondition (and
      (update-status computer7)
      (rebooted computer7)
    )
    :effect (and 
      (not (update-status computer7))
      (update-status computer8)
      (not (rebooted computer7))
      (probabilistic 9/10 (running computer7))
    )
  )
  (:action update-status-computer7-all-on
    :precondition (and
      (update-status computer7)
      (not (rebooted computer7))
      (all-on computer7)
    )
    :effect (and 
      (not (update-status computer7))
      (update-status computer8)
      (not (all-on computer7))
      (probabilistic 1/20 (not (running computer7)))
    )
  )
  (:action update-status-computer7-one-off
    :precondition (and
      (update-status computer7)
      (not (rebooted computer7))
      (one-off computer7)
    )
    :effect (and 
      (not (update-status computer7))
      (update-status computer8)
      (not (one-off computer7))
      (probabilistic 1/4 (not (running computer7)))
    )
  )
  (:action evaluate-computer8-rebooted
    :precondition (and
      (evaluate computer8)
      (rebooted computer8)
    )
    :effect (and 
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-all-on
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer6)
      (running computer9)
      (running computer10)
      (running computer11)
    )
    :effect (and 
      (all-on computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer0
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer1
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer2
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer3
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer4
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer5
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer6
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer9
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer10
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action evaluate-computer8-off-computer11
    :precondition (and
      (evaluate computer8)
      (not (rebooted computer8))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer8)
      (not (evaluate computer8))
      (evaluate computer9)
    )
  )
  (:action update-status-computer8-rebooted
    :precondition (and
      (update-status computer8)
      (rebooted computer8)
    )
    :effect (and 
      (not (update-status computer8))
      (update-status computer9)
      (not (rebooted computer8))
      (probabilistic 9/10 (running computer8))
    )
  )
  (:action update-status-computer8-all-on
    :precondition (and
      (update-status computer8)
      (not (rebooted computer8))
      (all-on computer8)
    )
    :effect (and 
      (not (update-status computer8))
      (update-status computer9)
      (not (all-on computer8))
      (probabilistic 1/20 (not (running computer8)))
    )
  )
  (:action update-status-computer8-one-off
    :precondition (and
      (update-status computer8)
      (not (rebooted computer8))
      (one-off computer8)
    )
    :effect (and 
      (not (update-status computer8))
      (update-status computer9)
      (not (one-off computer8))
      (probabilistic 1/4 (not (running computer8)))
    )
  )
  (:action evaluate-computer9-rebooted
    :precondition (and
      (evaluate computer9)
      (rebooted computer9)
    )
    :effect (and 
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-all-on
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer5)
      (running computer7)
      (running computer8)
      (running computer10)
    )
    :effect (and 
      (all-on computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer1
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer2
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer3
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer5
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer7
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer8
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action evaluate-computer9-off-computer10
    :precondition (and
      (evaluate computer9)
      (not (rebooted computer9))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer9)
      (not (evaluate computer9))
      (evaluate computer10)
    )
  )
  (:action update-status-computer9-rebooted
    :precondition (and
      (update-status computer9)
      (rebooted computer9)
    )
    :effect (and 
      (not (update-status computer9))
      (update-status computer10)
      (not (rebooted computer9))
      (probabilistic 9/10 (running computer9))
    )
  )
  (:action update-status-computer9-all-on
    :precondition (and
      (update-status computer9)
      (not (rebooted computer9))
      (all-on computer9)
    )
    :effect (and 
      (not (update-status computer9))
      (update-status computer10)
      (not (all-on computer9))
      (probabilistic 1/20 (not (running computer9)))
    )
  )
  (:action update-status-computer9-one-off
    :precondition (and
      (update-status computer9)
      (not (rebooted computer9))
      (one-off computer9)
    )
    :effect (and 
      (not (update-status computer9))
      (update-status computer10)
      (not (one-off computer9))
      (probabilistic 1/4 (not (running computer9)))
    )
  )
  (:action evaluate-computer10-rebooted
    :precondition (and
      (evaluate computer10)
      (rebooted computer10)
    )
    :effect (and 
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-all-on
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (running computer0)
      (running computer1)
      (running computer2)
      (running computer3)
      (running computer6)
      (running computer7)
      (running computer8)
      (running computer11)
    )
    :effect (and 
      (all-on computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer0
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer1
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer2
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer2))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer3
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer6
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer7
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer8
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action evaluate-computer10-off-computer11
    :precondition (and
      (evaluate computer10)
      (not (rebooted computer10))
      (not (running computer11))
    )
    :effect (and 
      (one-off computer10)
      (not (evaluate computer10))
      (evaluate computer11)
    )
  )
  (:action update-status-computer10-rebooted
    :precondition (and
      (update-status computer10)
      (rebooted computer10)
    )
    :effect (and 
      (not (update-status computer10))
      (update-status computer11)
      (not (rebooted computer10))
      (probabilistic 9/10 (running computer10))
    )
  )
  (:action update-status-computer10-all-on
    :precondition (and
      (update-status computer10)
      (not (rebooted computer10))
      (all-on computer10)
    )
    :effect (and 
      (not (update-status computer10))
      (update-status computer11)
      (not (all-on computer10))
      (probabilistic 1/20 (not (running computer10)))
    )
  )
  (:action update-status-computer10-one-off
    :precondition (and
      (update-status computer10)
      (not (rebooted computer10))
      (one-off computer10)
    )
    :effect (and 
      (not (update-status computer10))
      (update-status computer11)
      (not (one-off computer10))
      (probabilistic 1/4 (not (running computer10)))
    )
  )
  (:action evaluate-computer11-rebooted
    :precondition (and
      (evaluate computer11)
      (rebooted computer11)
    )
    :effect (and 
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-all-on
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (running computer0)
      (running computer1)
      (running computer3)
      (running computer4)
      (running computer5)
      (running computer6)
      (running computer7)
      (running computer8)
      (running computer9)
      (running computer10)
    )
    :effect (and 
      (all-on computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer0
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer1
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer1))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer3
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer3))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer4
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer4))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer5
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer5))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer6
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer6))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer7
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer7))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer8
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer8))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer9
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer9))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action evaluate-computer11-off-computer10
    :precondition (and
      (evaluate computer11)
      (not (rebooted computer11))
      (not (running computer10))
    )
    :effect (and 
      (one-off computer11)
      (not (evaluate computer11))
      (update-status computer0)
    )
  )
  (:action update-status-computer11-rebooted
    :precondition (and
      (update-status computer11)
      (rebooted computer11)
    )
    :effect (and 
      (not (update-status computer11))
      (all-updated)
      (not (rebooted computer11))
      (probabilistic 9/10 (running computer11))
    )
  )
  (:action update-status-computer11-all-on
    :precondition (and
      (update-status computer11)
      (not (rebooted computer11))
      (all-on computer11)
    )
    :effect (and 
      (not (update-status computer11))
      (all-updated)
      (not (all-on computer11))
      (probabilistic 1/20 (not (running computer11)))
    )
  )
  (:action update-status-computer11-one-off
    :precondition (and
      (update-status computer11)
      (not (rebooted computer11))
      (one-off computer11)
    )
    :effect (and 
      (not (update-status computer11))
      (all-updated)
      (not (one-off computer11))
      (probabilistic 1/4 (not (running computer11)))
    )
  )
)
