(define (problem elev_2_7_3_7_34255)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 - pos e1 e2 e3 - elevator c1 c2 c3 c4 c5 c6 c7 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (shaft e1 p2) (in e1 f1) (shaft e2 p7) (in e2 f1) (shaft e3 p3) (in e3 f1) (coin-at c1 f2 p1) (coin-at c2 f1 p7) (coin-at c3 f2 p7) (coin-at c4 f2 p7) (coin-at c5 f2 p6) (coin-at c6 f2 p3) (coin-at c7 f1 p2) (gate f2 p3) (gate f2 p4) (gate f2 p6) (gate f2 p7))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7)))
)
