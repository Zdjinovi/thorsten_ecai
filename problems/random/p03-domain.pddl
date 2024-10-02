(define (domain prob_domain) 
 (:requirements :strips :probabilistic-effects :conditional-effects) 
 (:constants HM VL DV UG SK PF NA MT QL MY )
 (:predicates 
	 (QI ?X ?Y ) 
	 (FO ?X ?Y ) 
	 (CF ?X ) 
	 (CT ?X ?Y ) 
(clear)
(not-clear)
 )
(:action UGQ
 :parameters (?X )
 :precondition (and 
		 (QI ?X ?X) 
  )
 :effect (probabilistic 
		 90/100 (and (CT ?X ?X) (not (QI ?X ?X)) )  
		 10/100 (and (CF ?X) (not (QI ?X ?X)) )  
          )
 )
(:action MHH
 :parameters (?X ?Y )
 :precondition (and 
		 (CF ?X) 
  )
 :effect (probabilistic 
		 84/100 (and (CT ?X ?Y) )  
		 9/100 (and (FO ?Y ?X) (FO ?X ?Y) (not (CF ?X)) )  
		 4/100 (and (FO ?Y ?X) (FO ?X ?Y) )  
		 0/100 (and (not (CF ?X)) )  
		 3/100 (and (not (CF ?X)) (CT ?Y ?X) )  
          )
 )
(:action WOT
 :parameters (?X )
 :precondition (and 
		 (QI ?X ?X) 
		 (FO ?X ?X) 
  )
 :effect (probabilistic 
		 100/100 (and (CF ?X) )  
          )
 )
(:action IPW
 :parameters (?X ?Y )
 :precondition (and 
		 (CT ?Y ?Y) 
		 (CF ?Y) 
		 (CF ?X) 
  )
 :effect (probabilistic 
		 77/100 (and (not (CF ?X)) (CT ?X ?Y) )  
		 23/100 (and (FO ?X ?X) )  
          )
 )
(:action reset1 
 :precondition (not-clear)
 :effect (and 
	     (forall (?x) (and 
      (not (QI ?x HM)) 
      (not (QI ?x VL)) 
      (not (QI ?x DV)) 
      (not (QI ?x UG)) 
      (not (QI ?x SK)) 
      (not (QI ?x PF)) 
      (not (QI ?x NA)) 
      (not (QI ?x MT)) 
      (not (QI ?x QL)) 
      (not (QI ?x MY)) 
      (not (FO ?x HM)) 
      (not (FO ?x VL)) 
      (not (FO ?x DV)) 
      (not (FO ?x UG)) 
      (not (FO ?x SK)) 
      (not (FO ?x PF)) 
      (not (FO ?x NA)) 
      (not (FO ?x MT)) 
      (not (FO ?x QL)) 
      (not (FO ?x MY)) 
      (not (CF ?x)) 
      (not (CT ?x HM)) 
      (not (CT ?x VL)) 
      (not (CT ?x DV)) 
      (not (CT ?x UG)) 
      (not (CT ?x SK)) 
      (not (CT ?x PF)) 
      (not (CT ?x NA)) 
      (not (CT ?x MT)) 
      (not (CT ?x QL)) 
      (not (CT ?x MY)) 
))
(not (not-clear))
(clear)))

(:action reset2 
 :precondition (clear) 
 :effect (and (not-clear)
              (not (clear))
(FO UG UG) 
(FO PF QL) 
(CT MY DV) 
(CT UG DV) 
(FO QL VL) 
(CF UG) 
(QI SK PF) 
(QI QL SK) 
(QI SK MT) 
(FO HM HM) 
(CF DV) 
(QI UG PF) 
(FO HM SK) 
(FO VL QL) 
)))
