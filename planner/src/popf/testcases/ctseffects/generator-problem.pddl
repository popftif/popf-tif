(define (problem run-generator2)
    (:domain generator)
    (:objects generator)
    (:init 	(= (fuel-level generator)  90)
		(= (capacity generator)  90)
		(not-refueling generator)
		(not-generating generator)
     )  
     (:goal (generator-ran))
) 