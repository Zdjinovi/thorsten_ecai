(define (domain sysadmin-ssp)
  (:requirements :probabilistic-effects :negative-preconditions :typing)
  (:types computer - object)
  (:constants computer0 computer1 computer2 computer3 - computer)
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
      (running computer2)
    )
    :effect (and 
      (all-on computer1)
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
      (running computer3)
    )
    :effect (and 
      (all-on computer2)
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
      (update-status computer0)
    )
  )
  (:action evaluate-computer3-all-on
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (running computer0)
    )
    :effect (and 
      (all-on computer3)
      (not (evaluate computer3))
      (update-status computer0)
    )
  )
  (:action evaluate-computer3-off-computer0
    :precondition (and
      (evaluate computer3)
      (not (rebooted computer3))
      (not (running computer0))
    )
    :effect (and 
      (one-off computer3)
      (not (evaluate computer3))
      (update-status computer0)
    )
  )
  (:action update-status-computer3-rebooted
    :precondition (and
      (update-status computer3)
      (rebooted computer3)
    )
    :effect (and 
      (not (update-status computer3))
      (all-updated)
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
      (all-updated)
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
      (all-updated)
      (not (one-off computer3))
      (probabilistic 1/4 (not (running computer3)))
    )
  )
)
