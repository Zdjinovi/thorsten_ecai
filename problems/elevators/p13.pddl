(define (problem elev_3_11_5_10_15003)
  (:domain elevators)
  (:objects f2 f3 - floor p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 - pos e1 e2 e3 e4 e5 - elevator c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_f f3 f2) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (dec_p p8 p7) (dec_p p9 p8) (dec_p p10 p9) (dec_p p11 p10) (shaft e1 p1) (in e1 f1) (shaft e2 p7) (in e2 f1) (shaft e3 p9) (in e3 f1) (shaft e4 p1) (in e4 f3) (shaft e5 p7) (in e5 f3) (coin-at c1 f3 p3) (coin-at c2 f2 p9) (coin-at c3 f3 p7) (coin-at c4 f3 p1) (coin-at c5 f1 p3) (coin-at c6 f2 p1) (coin-at c7 f3 p8) (coin-at c8 f3 p9) (coin-at c9 f1 p1) (coin-at c10 f1 p6) (gate f2 p3) (gate f2 p4) (gate f2 p5) (gate f2 p8) (gate f3 p3) (gate f3 p9))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7) (have c8) (have c9) (have c10)))
)
