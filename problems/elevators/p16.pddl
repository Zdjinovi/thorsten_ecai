(define (problem elev_4_7_5_7_33844)
  (:domain elevators)
  (:objects f2 f3 f4 - floor p2 p3 p4 p5 p6 p7 - pos e1 e2 e3 e4 e5 - elevator c1 c2 c3 c4 c5 c6 c7 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_f f3 f2) (dec_f f4 f3) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (shaft e1 p2) (in e1 f3) (shaft e2 p5) (in e2 f4) (shaft e3 p3) (in e3 f1) (shaft e4 p6) (in e4 f1) (shaft e5 p5) (in e5 f3) (coin-at c1 f3 p7) (coin-at c2 f2 p5) (coin-at c3 f1 p7) (coin-at c4 f2 p4) (coin-at c5 f3 p3) (coin-at c6 f1 p1) (coin-at c7 f4 p7) (gate f2 p3) (gate f2 p5) (gate f2 p6) (gate f2 p7) (gate f3 p2) (gate f3 p5) (gate f3 p6) (gate f3 p7) (gate f4 p3) (gate f4 p4))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7)))
)
