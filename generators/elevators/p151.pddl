(define (problem elev_2_7_5_7_55945)
  (:domain elevators)
  (:objects f2 - floor p2 p3 p4 p5 p6 p7 - pos e1 e2 e3 e4 e5 - elevator c1 c2 c3 c4 c5 c6 c7 - coin)
  (:init (at f1 p1) (dec_f f2 f1) (dec_p p2 p1) (dec_p p3 p2) (dec_p p4 p3) (dec_p p5 p4) (dec_p p6 p5) (dec_p p7 p6) (shaft e1 p7) (in e1 f2) (shaft e2 p1) (in e2 f2) (shaft e3 p4) (in e3 f2) (shaft e4 p4) (in e4 f2) (shaft e5 p4) (in e5 f1) (coin-at c1 f1 p6) (coin-at c2 f1 p1) (coin-at c3 f1 p4) (coin-at c4 f1 p4) (coin-at c5 f2 p7) (coin-at c6 f1 p2) (coin-at c7 f1 p7))
  (:goal (and (have c1) (have c2) (have c3) (have c4) (have c5) (have c6) (have c7)))
)
