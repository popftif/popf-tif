(define (domain blocksworld)
    (:requirements :strips :typing :fluents :durative-actions :universal-preconditions :conditional-effects)
    (:types block column)
   

    (:predicates (clear ?x - block)
        (on-column ?x - block)
	(column-empty ?c - column)
        (arm-empty)
	(above ?x - block ?c - column)
        (holding ?x - block)
        (on ?x ?y - block)
	(precondition)	
	(inplan)
	)

    (:functions
	(weight-column ?c - column)
	(weight-block ?b - block)
	(height-column ?c - column)
	(maxheight ?c - column)
	(heuristic ?c ?c1 - column) 		
	)
	
    (:action pickup
	:parameters (?ob - block ?c - column)
	:precondition (and 
	    (clear ?ob)
	    (on-column ?ob)
	    (arm-empty)
	    (above ?ob ?c)
	    (< (weight-column ?c) 10000)
	    (forall (?cc - column) (and 
		    (<= (height-column ?cc) (maxheight ?cc))
		    (>= (height-column ?cc) 0)
		    )
		)
	    )
	:effect (and 
	    (column-empty ?c)
	    (not (above ?ob ?c))
	    (holding ?ob)
	    (not (clear ?ob))
	    (not (on-column ?ob))
            (not (arm-empty))
	    (decrease (weight-column ?c) (weight-block ?ob))
	    (forall (?cc - column) (and (increase (height-column ?cc) (heuristic ?c ?cc))))
	    )	
	)

    (:action putdown
	:parameters  (?ob  - block ?c - column)
	:precondition (and 
	    (holding ?ob)
	    (column-empty ?c)
	    (< (weight-column ?c) 10000)
	    (forall (?cc - column) (and 
		    (<= (height-column ?cc) (maxheight ?cc))
		    (>= (height-column ?cc) 0)
		    )
		))
	
	:effect (and 
	    (not (column-empty ?c))
	    (clear ?ob)
	    (arm-empty)
	    (on-column ?ob)
	    (above ?ob ?c)
	    (increase (weight-column ?c) (weight-block ?ob))
  	    (forall (?cc - column) (and (decrease (height-column ?cc) (heuristic ?c ?cc))))
	    (not (holding ?ob))))

    (:action stack
	:parameters  (?ob ?underob - block ?c - column)
	:precondition (and 
	    (clear ?underob)
	    (holding ?ob)
	    (above ?underob ?c)
	    (< (weight-column ?c) 10000)
	    (forall (?cc - column) (and 
		    (<= (height-column ?cc) (maxheight ?cc))
		    (>= (height-column ?cc) 0)
		    )
		))
	
	:effect (and 
	    (arm-empty)
	    (clear ?ob)
	    (on ?ob ?underob)
	    (above ?ob ?c)
      	    (increase (weight-column ?c) (weight-block ?ob))
  	    (forall (?cc - column) (and (decrease (height-column ?cc) (heuristic ?c ?cc))))
	    (not (clear ?underob))
	    (not (holding ?ob))))

    (:action unstack
	:parameters  (?ob ?underob - block ?c - column)
	:precondition (and 
	    (on ?ob ?underob)
	    (clear ?ob)
	    (arm-empty)
	    (above ?ob ?c)
	    (< (weight-column ?c) 10000)
	    (forall (?cc - column) (and 
		    (<= (height-column ?cc) (maxheight ?cc))
		    (>= (height-column ?cc) 0)
		    )
		))
	:effect (and 
	    (holding ?ob)
	    (clear ?underob)
	    (not (above ?ob ?c))
      	    (decrease (weight-column ?c) (weight-block ?ob))
  	    (forall (?cc - column) (and (increase (height-column ?cc) (heuristic ?c ?cc))))
	    (not (on ?ob ?underob))
	    (not (clear ?ob))
	    (not (arm-empty))))
    )

