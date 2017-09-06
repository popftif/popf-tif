(define (problem patblock-4-1)
(:domain patblock)
(:objects A B P1 P2 P3 I1 I2 I3 I0)
(:INIT (contents P1 I1 A) (contents P1 I2 B) (contents P1 I3 Z)

       (contents P2 I1 Z ) (contents P2 I2 Z ) (contents P2 I3 Z )

       (contents P3 I1 Z ) (contents P3 I2 Z ) (contents P3 I3 Z )

       (block A) (block B)
       (position P1) (position P2) (position P3)
       (index I0) (index I1) (index I2) (index I3)

       (top P1 I2) (top P2 I0) (top P3 I0)
       (notmaxblock I0) (notmaxblock I1) (notmaxblock I2)
       (notzero I1) (notzero I2) (notzero I3)
       (lower I3 I2) (lower I2 I1) (lower I1 I0)
       (higher I0 I1) (higher I1 I2) (higher I2 I3)
       (notequal P1 P2) (notequal P1 P3)
       (notequal P2 P1) (notequal P2 P3)
       (notequal P3 P1) (notequal P3 P2))
(:goal (AND (contents P1 I1 B) (contents P1 I2 A))))

