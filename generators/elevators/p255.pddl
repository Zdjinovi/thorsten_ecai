(define (problem elev_2_9_3_5_16944)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 p8 p9 - pos e1 e2 e3 - elevator c1 c2 c3 c4 c5 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (dec_p p8 p7) (dec_p p9 p8) (shaft e1 p9) (in e1 f1) (shaft e2 p3) (in e2 f2) (shaft e3 p7) (in e3 f1) (coin-at c1 f2 p1) (coin-at c2 f1 p4) (coin-at c3 f1 p9) (coin-at c4 f2 p6) (coin-at c5 f1 p4) (gate f2 p3) (gate f2 p6))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5)))
)
