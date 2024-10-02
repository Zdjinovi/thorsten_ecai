(define (problem elev_2_11_4_11_59357)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 - pos e1 e2 e3 e4 - elevator c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (dec_p p8 p7) (dec_p p9 p8) (dec_p p10 p9) (dec_p p11 p10) (shaft e1 p2) (in e1 f2) (shaft e2 p4) (in e2 f2) (shaft e3 p10) (in e3 f2) (shaft e4 p9) (in e4 f2) (coin-at c1 f2 p2) (coin-at c2 f1 p7) (coin-at c3 f1 p7) (coin-at c4 f1 p3) (coin-at c5 f1 p6) (coin-at c6 f2 p3) (coin-at c7 f1 p11) (coin-at c8 f1 p3) (coin-at c9 f2 p7) (coin-at c10 f2 p2) (coin-at c11 f2 p8) (gate f2 p2) (gate f2 p8) (gate f2 p9) (gate f2 p10) (gate f2 p11))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7) (have c8) (have c9) (have c10) (have c11)))
)
