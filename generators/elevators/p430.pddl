(define (problem elev_2_11_3_7_9886)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 - pos e1 e2 e3 - elevator c1 c2 c3 c4 c5 c6 c7 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (dec_p p8 p7) (dec_p p9 p8) (dec_p p10 p9) (dec_p p11 p10) (shaft e1 p2) (in e1 f2) (shaft e2 p11) (in e2 f1) (shaft e3 p6) (in e3 f2) (coin-at c1 f1 p2) (coin-at c2 f2 p1) (coin-at c3 f2 p7) (coin-at c4 f1 p1) (coin-at c5 f2 p8) (coin-at c6 f1 p8) (coin-at c7 f2 p9) (gate f2 p3) (gate f2 p7) (gate f2 p11))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7)))
)
