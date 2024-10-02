(define (domain p14-dom)
 (:requirements :probabilistic-effects :negative-preconditions :typing)
 (:types class packet timestep phase)
 (:constants 
    C0 C1 C2 - class
    U0 U1 U2 U3 - timestep
    P0 P1 P2 P3 P4 P5 - packet
    Arrivals-and-updating Cleanup-and-service - phase
 )
 (:predicates
   (current-phase ?s - phase)
   (packet-class ?p - packet ?c - class)
   (time-to-live ?p - packet ?t - timestep)
   (available ?p - packet)
   (current-timestep ?t - timestep)
   (next-timestep ?t0 ?t1 - timestep)
   (need-to-process-arrivals ?c - class)
   (served ?c - class)
 )
 (:action process-arrivals-C0
  :parameters (?arriving-packet - packet ?t - timestep)
  :precondition (and
                    (current-phase Arrivals-and-updating)
                    (available ?arriving-packet)
                    (need-to-process-arrivals C0)
                    (current-timestep ?t)
                )
  :effect (and
              (not (need-to-process-arrivals C0))
              (probabilistic 166/1000
                            (and (not (available ?arriving-packet))
                                 (packet-class ?arriving-packet C0)
                                 (time-to-live ?arriving-packet ?t)
                            )
              )
              (increase (total-cost) 1)
          )
 )
 (:action process-arrivals
  :parameters (?arriving-packet - packet ?c - class ?t - timestep)
  :precondition (and
                    (not (= ?c C0))
                    (current-phase Arrivals-and-updating)
                    (available ?arriving-packet)
                    (need-to-process-arrivals ?c)
                    (current-timestep ?t)
            )
  :effect (and
             (not (need-to-process-arrivals ?c))
             (probabilistic 110/200
                              (and (not (available ?arriving-packet))
                                   (packet-class ?arriving-packet ?c)
                                   (time-to-live ?arriving-packet ?t)
                              )
             )
             (increase (total-cost) 1)
          )
 )
 (:action time-update
 :parameters (?t0 ?t1 - timestep)
 :precondition (and
                   (current-phase Arrivals-and-updating)
                   (current-timestep ?t0)
                   (next-timestep ?t0 ?t1)
                   (not (need-to-process-arrivals C0))
                   (not (need-to-process-arrivals C1))
                   (not (need-to-process-arrivals C2))
               )
 :effect (and 
            (not (current-phase Arrivals-and-updating))
            (current-phase Cleanup-and-service)
            (not (current-timestep ?t0))
            (current-timestep ?t1)
            (increase (total-cost) 1)
         )
 )
 (:action reclaim-packet-C0
  :parameters (?p - packet ?t - timestep)
  :precondition (and
                    (current-phase Cleanup-and-service)
                    (packet-class ?p C0)
                    (time-to-live ?p ?t)
                )
  :effect (and
              (not (time-to-live ?p ?t))
              (not (packet-class ?p C0))
              (available ?p)
              (increase (total-cost) 5)
          )
 )
 (:action reclaim-packet-C1
  :parameters (?p - packet ?t - timestep)
  :precondition (and
                    (current-phase Cleanup-and-service)
                    (packet-class ?p C1)
                    (time-to-live ?p ?t)
                )
  :effect (and
              (not (time-to-live ?p ?t))
              (not (packet-class ?p C1))
              (available ?p)
              (increase (total-cost) 5)
          )
 )
 (:action reclaim-packet-C2
  :parameters (?p - packet ?t - timestep)
  :precondition (and
                    (current-phase Cleanup-and-service)
                    (packet-class ?p C2)
                    (time-to-live ?p ?t)
                )
  :effect (and
              (not (time-to-live ?p ?t))
              (not (packet-class ?p C2))
              (available ?p)
              (increase (total-cost) 5)
          )
 )
 (:action packet-serve
  :parameters (?p - packet ?c - class ?t - timestep)
  :precondition (and
                    (current-phase Cleanup-and-service)
                    (packet-class ?p ?c)
                    (current-timestep ?t)
                    (not (time-to-live P0 ?t))
                    (not (time-to-live P1 ?t))
                    (not (time-to-live P2 ?t))
                    (not (time-to-live P3 ?t))
                    (not (time-to-live P4 ?t))
                )
  :effect (and
              (forall (?c1 - class) (need-to-process-arrivals ?c1))
              (forall (?u - timestep) (not (time-to-live ?p ?u)))
              (not (current-phase Cleanup-and-service))
              (current-phase Arrivals-and-updating)
              (served ?c)
              (not (packet-class ?p ?c))
              (available ?p)
              (increase (total-cost) 1)
          )
 )
 (:action serve-nothing
  :parameters (?t - timestep)
  :precondition (and
                    (current-phase Cleanup-and-service)
                    (current-timestep ?t)
                    (not (time-to-live P0 ?t))
                    (not (time-to-live P1 ?t))
                    (not (time-to-live P2 ?t))
                    (not (time-to-live P3 ?t))
                    (not (time-to-live P4 ?t))
                )
  :effect (and    
              (forall (?c1 - class) (need-to-process-arrivals ?c1))
              (not (current-phase Cleanup-and-service))
              (current-phase Arrivals-and-updating)
              (increase (total-cost) 1)
          )
 )
)
