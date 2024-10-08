(define (domain p06-dom)
 (:requirements :probabilistic-effects :negative-preconditions :typing)
 (:types class packet timestep phase)
 (:constants 
    C0 - class
    U0 U1 U2 U3 U4 U5 U6 U7 U8 U9 U10 U11 U12 U13 U14 U15 U16 U17 U18 U19 U20 U21 U22 U23 U24 U25 U26 U27 U28 U29 U30 U31 U32 U33 U34 U35 U36 U37 U38 U39 U40 U41 U42 U43 U44 U45 U46 U47 U48 U49 U50 U51 U52 U53 U54 U55 U56 U57 U58 U59 U60 - timestep
    P0 P1 P2 P3 P4 P5 P6 P7 P8 - packet
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
              (probabilistic 10/1000
                            (and (not (available ?arriving-packet))
                                 (packet-class ?arriving-packet C0)
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
                    (not (time-to-live P5 ?t))
                    (not (time-to-live P6 ?t))
                    (not (time-to-live P7 ?t))
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
                    (not (time-to-live P5 ?t))
                    (not (time-to-live P6 ?t))
                    (not (time-to-live P7 ?t))
                )
  :effect (and    
              (forall (?c1 - class) (need-to-process-arrivals ?c1))
              (not (current-phase Cleanup-and-service))
              (current-phase Arrivals-and-updating)
              (increase (total-cost) 1)
          )
 )
)
