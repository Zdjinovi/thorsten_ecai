(define (problem elev_2_7_3_11_15445)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 - pos e1 e2 e3 - elevator c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (shaft e1 p5) (in e1 f2) (shaft e2 p5) (in e2 f2) (shaft e3 p5) (in e3 f2) (coin-at c1 f1 p4) (coin-at c2 f2 p1) (coin-at c3 f1 p6) (coin-at c4 f1 p2) (coin-at c5 f1 p6) (coin-at c6 f1 p6) (coin-at c7 f2 p1) (coin-at c8 f1 p2) (coin-at c9 f1 p5) (coin-at c10 f2 p6) (coin-at c11 f2 p4) (gate f2 p2) (gate f2 p3) (gate f2 p7))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7) (have c8) (have c9) (have c10) (have c11)))
)
