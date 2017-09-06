(define (domain generator2)
(:requirements :fluents :durative-actions :duration-inequalities :adl)
(:predicates (not-refueling ?g) (generator-ran) (not-generating ?g)
             (not-done-fill ?g) (done-fill ?g)
)
(:functions (fuel-level ?g) (capacity ?g))

(:durative-action fill
 :parameters (?g)
 :duration (= ?duration 180)
 :condition (and
		(at start (not-done-fill ?g))
		(over all (<= (fuel-level ?g) (capacity ?g)))
	    )
 :effect (and
		(at start (not (not-done-fill ?g)))
		(increase (fuel-level ?g) (* #t 0.5))
		(at end (done-fill ?g))
	)
)
	
(:durative-action generate
 :parameters (?g)
 :duration (= ?duration  100)		 
 :condition (and
        (at start (>= (fuel-level ?g) 10))
		(over all (>= (fuel-level ?g) 0))
		(at start (not-generating ?g))
	)
 :effect (and (decrease (fuel-level ?g) (* #t 1))
	      (at start (not (not-generating ?g)))
	      (at end (generator-ran))))

(:durative-action refuel
 :parameters (?g)
 :duration  (= ?duration  10) 
 :condition (and (at start (done-fill ?g))
		 (at start (not-refueling ?g)) 
		 (over all (<= (fuel-level ?g) (capacity ?g))))
 :effect (and (at start (not (not-refueling ?g)))
              (increase (fuel-level ?g) (* #t 2))
	      (at end (not-refueling ?g))
          )
)




)
