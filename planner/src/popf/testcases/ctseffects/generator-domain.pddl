(define (domain generator2)
(:requirements :fluents :durative-actions :duration-inequalities :adl)
(:predicates (not-refueling ?g) (generator-ran) (not-generating ?g))
(:functions (fuel-level ?g) (capacity ?g))

(:durative-action generate
 :parameters (?g)
 :duration (= ?duration  100)		 
 :condition (and
		(over all (> (fuel-level ?g) 0))
		(at start (not-generating ?g))
	)
 :effect (and (decrease (fuel-level ?g) (* #t 1))
	      (at start (not (not-generating ?g)))
	      (at end (generator-ran))))

(:durative-action refuel
 :parameters (?g)
 :duration  (= ?duration  10) 
 :condition (and (at start (not-refueling ?g)) 
		 (over all (< (fuel-level ?g) (capacity ?g))))
 :effect (and (at start (not (not-refueling ?g)))
              (increase (fuel-level ?g) (* #t 2))
	      (at end (not-refueling ?g))
          )
)




)
