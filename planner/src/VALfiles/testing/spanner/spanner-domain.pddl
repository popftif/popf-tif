(define (domain energydomain)
(:requirements :typing :fluents)
(:types 
	man nut - object
	location
)
(:predicates
        (at ?m - object ?l - location)
	(has_food ?l - location)
	(link ?l1 - location ?l2 - location)
	(nutlocation ?l - location)
)

(:functions
  (energy ?m - man)
  (fixednuts)
  (unfixednuts)
)

(:action walk 
        :parameters (?start - location ?end - location ?m - man)
        :precondition (and 
		      (>= (energy ?m) 1)
		      (at ?m ?start) 
		      (link ?start ?end)
		      )
        :effect (and (not (at ?m ?start)) (at ?m ?end) (decrease (energy ?m) 1))
)

(:action eat 
        :parameters (?l - location ?m - man)
        :precondition (and 
		      (at ?m ?l) 
		      (has_food ?l)
		      )
        :effect (and (increase (energy ?m) 1) )
)

(:action tighten_nut 
        :parameters (?l - location ?m - man)
        :precondition (and 
		      (at ?m ?l) 
		      (nutlocation ?l)
		      (>= (energy ?m) 1)
		      (>= (unfixednuts) 1)
		      )
        :effect (and (decrease (energy ?m) 1) (increase (fixednuts) 1) (decrease (unfixednuts) 1) )
)

)
