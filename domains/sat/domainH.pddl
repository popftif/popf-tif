(define (domain UAV)
    (:requirements :typing :durative-actions :fluents :timed-initial-literals :equality :conditional-effects)
    (:types spiral - pattern waypoint destination)

    (:predicates 
	(at ?p - waypoint) 
	(active ?p - pattern) 
	(beginAt ?w - waypoint  ?p - pattern) 
	(endAt ?w - waypoint ?p - pattern) 
	)
    (:functions 
;	(gamma ?p - pattern)
	(probability ?d - destination) ;; probability that the target is going towards d
	(previous-probability ?d - destination) ;; probability that the target is going towards d at time t-1
	(total-probability) ;; probability of finding the target by following current plan
	(heuristic-approximation ?p - pattern) ;; approximation
	(heuristic-expected ?p - pattern) ;; approximation expected time	
	(previous-total-probability) ;; probability of finding the target at time t-1 by following current plan
	(is-doing ?p - pattern) ;; added for external-solver
	(timefor ?p - pattern) 
	(distance ?p1 ?p2 - waypoint)
	(expected-time)
	(previous-expected-time)
	(n-pattern)
	(n-pattern-active ?p - pattern)
	(total-time-pattern)	
	)


    (:durative-action fly
	:parameters (?from ?tto - waypoint)
	:duration (= ?duration (distance ?from ?tto))
	:condition (and 
	    (at start (at ?from)) 
	    (at start (not (= ?from ?tto)))
	    )
	:effect (and 
	    (at start (not (at ?from))) 
	    (at end (at ?tto))
	    )
	)

    (:durative-action doSpiral
	:parameters (?from ?to - waypoint ?p - pattern)
	:duration (=?duration (timefor ?p))
	:condition (and 
	    (at start (beginAt ?from ?p)) 
	    (at start (endAt ?to ?p)) 
	    (at start (at ?from)) 
	    (at start (active ?p))
	    (at start (<= (heuristic-approximation ?p ) 100))
	    (at start (<= (heuristic-expected ?p ) 100))
	    ;(at start (<= (n-pattern-active ?p) 1000000))	    
	    )
	:effect (and 
	    (at end (at ?to)) 
	    (at start (not (at ?from)))
	    (forall (?pp - pattern) (and (at start (assign (is-doing ?pp) 0))))
	    (at end (assign (is-doing ?p) 1))
	    (forall (?d - destination) (and (at end (assign (previous-probability ?d) (probability ?d)))))
	    (at end (assign (previous-total-probability) (total-probability)))	    
	    (forall (?d - destination) (and (at end (increase (probability ?d) 0.001))))
	    (at end (increase (total-probability) (heuristic-approximation ?p)))
	    (forall (?pp - pattern) (at end (assign (heuristic-approximation ?pp) 0.001)))
	    (at end (assign (previous-expected-time) (expected-time)))	    
	    (at end (increase (expected-time) (heuristic-expected ?p)))
	    ;(forall (?pp - pattern) (at end (assign (heuristic-expected ?pp) (* (/ (n-pattern-active ?pp) (total-time-pattern)) (heuristic-approximation ?pp)))))
	    (forall (?pp - pattern) (at end (assign (heuristic-expected ?pp) 0.001)))
	    ;(at end (increase (n-pattern-active ?p) 0))
	    (at end (assign (n-pattern) (n-pattern-active ?p)))
	)
    )
)
