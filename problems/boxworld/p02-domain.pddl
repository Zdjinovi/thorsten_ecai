(define (domain box-p02-domain)
 (:requirements :typing
                :probabilistic-effects
                :negative-preconditions
)
 (:types city box truck plane)
 (:predicates (box-at-city ?b - box ?c - city)
              (truck-at-city ?t - truck ?c - city)
              (box-on-truck ?b - box ?t - truck)
              (plane-at-city ?p - plane ?c - city)
              (box-on-plane ?b - box ?p - plane)
              (destination ?b - box ?dst - city)
              (can-drive ?src - city ?dst - city)
              (wrong-drive1 ?src - city ?wrongdst - city)
              (wrong-drive2 ?src - city ?wrongdst - city)
              (wrong-drive3 ?src - city ?wrongdst - city)
              (can-fly ?src - city ?dst - city))
 (:action load-box-on-truck-in-city
  :parameters (?b - box ?t - truck ?c - city)
  :precondition (and (box-at-city ?b ?c)
                     (not (destination ?b ?c))
                     (truck-at-city ?t ?c)
                )
  :effect (and (increase (total-cost) 1)
               (box-on-truck ?b ?t)
               (not (box-at-city ?b ?c))
          )
 )
 (:action unload-box-from-truck-in-city
  :parameters (?b - box ?t - truck ?c - city)
  :precondition (and (box-on-truck ?b ?t)
                     (truck-at-city ?t ?c)
                )
  :effect (and (increase (total-cost) 1)
               (box-at-city ?b ?c)
               (not (box-on-truck ?b ?t))
          )
 )
 (:action load-box-on-plane-in-city
  :parameters (?b - box ?p - plane ?c - city)
  :precondition (and (box-at-city ?b ?c)
                     (not (destination ?b ?c))
                     (plane-at-city ?p ?c)
                )
  :effect (and (increase (total-cost) 1)
               (box-on-plane ?b ?p)
               (not (box-at-city ?b ?c))
          )
 )
 (:action unload-box-from-plane-in-city
  :parameters (?b - box ?p - plane ?c - city)
  :precondition (and (box-on-plane ?b ?p)
                     (plane-at-city ?p ?c)
                )
  :effect (and (increase (total-cost) 1)
               (box-at-city ?b ?c)
               (not (box-on-plane ?b ?p))
          )
 )
 (:action drive-truck
  :parameters (?t - truck ?src - city ?dst ?w1 ?w2 ?w3 - city)
  :precondition (and (truck-at-city ?t ?src)
                     (can-drive ?src ?dst)
                     (wrong-drive1 ?src ?w1)
                     (wrong-drive2 ?src ?w2)
                     (wrong-drive3 ?src ?w3)
                )
  :effect (and (increase (total-cost) 5)
               (not (truck-at-city ?t ?src))
                 (probabilistic
                   1/15 (truck-at-city ?t ?w1)
                   1/15 (truck-at-city ?t ?w2)
                   1/15 (truck-at-city ?t ?w3)
                   4/5  (truck-at-city ?t ?dst)
                 )
          )
)
 (:action fly-plane
  :parameters (?p - plane ?src - city ?dst - city)
  :precondition (and (plane-at-city ?p ?src)
                     (can-fly ?src ?dst)
                )
  :effect (and (increase (total-cost) 20)
              (not (plane-at-city ?p ?src))
               (plane-at-city ?p ?dst)
          )
 )
)
