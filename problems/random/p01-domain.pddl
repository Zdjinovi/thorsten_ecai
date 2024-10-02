(define (domain prob_domain) 
 (:requirements :strips :probabilistic-effects :conditional-effects) 
 (:constants OT XO GK ST XE KG PN TM KQ JI )
 (:predicates 
	 (SZ ?X ) 
	 (RH ?X ) 
	 (CN ?X ) 
(clear)
(not-clear)
 )
(:action FDW
 :parameters (?X ?Y )
 :precondition (and 
		 (RH ?Y) 
		 (SZ ?X) 
		 (CN ?X) 
  )
 :effect (probabilistic 
		 100/100 (and (RH ?X) )  
          )
 )
(:action HDE
 :parameters (?X ?Y ?Z )
 :precondition (and 
		 (RH ?Z) 
  )
 :effect (probabilistic 
		 27/100 (and (not (RH ?Z)) (CN ?Y) )  
		 73/100 (and (SZ ?X) )  
          )
 )
(:action HAM
 :parameters (?X )
 :precondition (and 
		 (CN ?X) 
  )
 :effect (probabilistic 
		 32/100 (and (not (CN ?X)) (RH ?X) )  
		 68/100 (and (not (CN ?X)) )  
          )
 )
(:action reset1 
 :precondition (not-clear)
 :effect (and 
	     (forall (?x) (and 
      (not (SZ ?x)) 
      (not (RH ?x)) 
      (not (CN ?x)) 
))
(not (not-clear))
(clear)))

(:action reset2 
 :precondition (clear) 
 :effect (and (not-clear)
              (not (clear))
(CN OT) 
(SZ XO) 
(CN ST) 
(SZ OT) 
(RH ST) 
(SZ KG) 
(SZ JI) 
(CN JI) 
(RH JI) 
(RH OT) 
)))
