(define (domain elevators)
    (:requirements :probabilistic-effects :negative-preconditions :typing)
    (:types
        elevator floor pos coin
    )
    (:constants
        f1 - floor
        p1 - pos
    )
    (:predicates
        (dec_f ?f ?g - floor)
        (dec_p ?p ?q - pos)
        (in ?e - elevator ?f - floor)
        (at ?f - floor ?p - pos)
        (shaft ?e - elevator ?p - pos)
        (inside ?e - elevator)
        (gate ?f - floor ?p - pos)
        (coin-at ?c - coin ?f - floor ?p - pos)
        (have ?c - coin)
    )
    (:action go-up
        :parameters (?e - elevator ?f ?nf - floor)
        :precondition (and (dec_f ?nf ?f) (in ?e ?f))
        :effect (and (increase (total-cost) 1) (in ?e ?nf) (not (in ?e ?f)))
    )
    (:action go-down
        :parameters (?e - elevator ?f ?nf - floor)
        :precondition (and (dec_f ?f ?nf) (in ?e ?f))
        :effect (and (increase (total-cost) 1) (in ?e ?nf) (not (in ?e ?f)))
    )
    (:action step-in
        :parameters (?e - elevator ?f - floor ?p - pos)
        :precondition (and (at ?f ?p) (in ?e ?f) (shaft ?e ?p))
        :effect (and (increase (total-cost) 1) (inside ?e) (not (at ?f ?p)))
    )
    (:action step-out
        :parameters (?e - elevator ?f - floor ?p - pos)
        :precondition (and (inside ?e) (in ?e ?f) (shaft ?e ?p))
        :effect (and (increase (total-cost) 1) (at ?f ?p) (not (inside ?e)))
    )
    (:action move-left-no-gate
        :parameters (?f - floor ?p ?np - pos)
        :precondition (and (at ?f ?p) (dec_p ?p ?np) (not (gate ?f ?p)))
        :effect (and (increase (total-cost) 1) (not (at ?f ?p)) (at ?f ?np))
    )
    (:action move-left-gate
        :parameters (?f - floor ?p ?np - pos)
        :precondition (and (at ?f ?p) (dec_p ?p ?np) (gate ?f ?p))
        :effect (and (increase (total-cost) 1) (not (at ?f ?p))
            (probabilistic 1/2 (at ?f ?np) 1/2 (at f1 p1)))
    )
    (:action move-right-no-gate
        :parameters (?f - floor ?p ?np - pos)
        :precondition (and (at ?f ?p) (dec_p ?np ?p) (not (gate ?f ?p)))
        :effect (and (increase (total-cost) 1) (not (at ?f ?p)) (at ?f ?np))
    )
    (:action move-right-gate
        :parameters (?f - floor ?p ?np - pos)
        :precondition (and (at ?f ?p) (dec_p ?np ?p) (gate ?f ?p))
        :effect (and (increase (total-cost) 1) (not (at ?f ?p))
            (probabilistic 1/2 (at ?f ?np) 1/2 (at f1 p1)))
    )
    (:action collect
        :parameters (?c - coin ?f - floor ?p - pos)
        :precondition (and (coin-at ?c ?f ?p) (at ?f ?p))
        :effect (and (increase (total-cost) 1) (have ?c) (not (coin-at ?c ?f ?p)))
    )
)