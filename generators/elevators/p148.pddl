(define (problem elev_2_7_5_6_22976)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 - pos e1 e2 e3 e4 e5 - elevator c1 c2 c3 c4 c5 c6 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (shaft e1 p7) (in e1 f1) (shaft e2 p3) (in e2 f2) (shaft e3 p4) (in e3 f1) (shaft e4 p2) (in e4 f1) (shaft e5 p6) (in e5 f1) (coin-at c1 f1 p2) (coin-at c2 f2 p6) (coin-at c3 f1 p3) (coin-at c4 f2 p7) (coin-at c5 f1 p7) (coin-at c6 f1 p4) (gate f2 p3))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6)))
)
