(define (problem pfile1)
(:domain blocksworld)
(:objects
B0 B1 B2 B3 B4 - block
C0 - column
)
(:init
(arm-empty)

(= (weight-block B0) 5)
(above B0 C0)
(on-column B0)
(= (weight-block B1) 9)
(above B1 C0)
(on B1 B0)
(= (weight-block B2) 7)
(above B2 C0)
(on B2 B1)
(= (weight-block B3) 2)
(above B3 C0)
(on B3 B2)
(= (weight-block B4) 4)
(above B4 C0)
(on B4 B3)
(clear B4)
(= (weight-column C0) 27)
(= (maxheight C0) 10)
(= (height-column C0) 9)
)
(:goal
(and (on-column B0)
	    (<= (height-column C0) (maxheight C0))
	    (>= (height-column C0) 0)
)))
