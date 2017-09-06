(define (domain civ) 
  (:requirements :fluents :typing :durative-actions :duration-inequalities) 
  (:types place vehicle - store 
	  resource) 
  (:predicates 
   (connected-by-land ?p1 - place ?p2 - place) 
   (connected-by-rail ?p1 - place ?p2 - place) 
   (connected-by-sea ?p1 - place ?p2 - place) 
   (woodland ?p - place) 
   (mountain ?p - place) 
   (metalliferous ?p - place) 
   (by-coast ?p - place) 
 
   (has-cabin ?p - place) 
   (has-coal-stack ?p - place) 
   (has-quarry ?p - place) 
   (has-mine ?p - place) 
   (has-sawmill ?p - place) 
   (has-ironworks ?p - place) 
   (has-docks ?p - place) 
   (has-wharf ?p - place) 
   (is-cart ?v - vehicle) 
   (is-train ?v - vehicle) 
   (is-ship ?v - vehicle) 
   (is-at ?v - vehicle ?p - place) 

   (potential ?v - vehicle)
   ) 
  (:functions 
   (available ?r - resource ?s - store)
   (space-in ?v - vehicle) 
	(labour)
	(resource-use)
	(pollution)
	(housing ?p - place)
   ) 
  (:constants timber wood coal stone iron ore - resource)
 
 
  ;; A.1: Loading and unloading. 
 
  (:durative-action load
   :parameters (?v - vehicle ?p - place ?r - resource) 
   :duration (= ?duration 1)
   :condition (and (over all (is-at ?v ?p))
		      (at start (> (available ?r ?p) 0)) 
		      (at start (> (space-in ?v) 0))) 
   :effect (and (at start (decrease (space-in ?v) 1))
		(at end (increase (available ?r ?v) 1))
		(at start (decrease (available ?r ?p) 1))
		(at start (increase (labour) 1))))
 
  (:durative-action unload
   :parameters (?v - vehicle ?p - place ?r - resource) 
   :duration (= ?duration 1)
   :condition (and (over all (is-at ?v ?p))
		      (at start (> (available ?r ?v) 0))) 
   :effect (and (at end (increase (space-in ?v) 1)) 
		(at start (decrease (available ?r ?v) 1))
		(at end (increase (available ?r ?p) 1))
		(at start (increase (labour) 1))))
 
  ;; A.2: Moving vehicles. 
  ;; Moving trains and ships consumes coal, which has to be 
  ;; loaded in the vehicle. 
 
  (:durative-action move-cart 
   :parameters (?v - vehicle ?p1 - place ?p2 - place) 
   :duration (= ?duration 5)
   :condition (and (over all (is-cart ?v)) 
		      (over all (connected-by-land ?p1 ?p2)) 
		      (at start (is-at ?v ?p1)))
   :effect (and (at start (not (is-at ?v ?p1))) 
		(at end (is-at ?v ?p2))
		(at start (increase (labour) 2))))
 
  (:durative-action move-train 
   :parameters (?v - vehicle ?p1 - place ?p2 - place) 
   :duration (= ?duration 5)
   :condition (and (over all (is-train ?v))
		      (over all (connected-by-rail ?p1 ?p2))
		      (at start (is-at ?v ?p1)) 
		      (at start (>= (available coal ?v) 1))) 
   :effect (and (at start (not (is-at ?v ?p1)))
		(at end (is-at ?v ?p2))
		(at start (decrease (available coal ?v) 1))
		(at start (increase (pollution) 1))
	)) 
 
  (:durative-action move-ship 
   :parameters (?v - vehicle ?p1 - place ?p2 - place) 
   :duration (= ?duration 10)
   :condition (and (over all (is-ship ?v))
		      (over all (connected-by-sea ?p1 ?p2))
		      (at start (is-at ?v ?p1))
		      (at start (>= (available coal ?v) 2)))
   :effect (and (at start (not (is-at ?v ?p1)))
		(at end (is-at ?v ?p2))
		(at start (decrease (available coal ?v) 2))
		(at start (increase (pollution) 2))
	)) 
 
  ;; B.1: Building structures. 
 
  (:durative-action build-cabin 
   :parameters (?p - place) 
   :duration (= ?duration 10)
   :condition (at start (woodland ?p))
   :effect (and (at start (increase (labour) 1))
		(at end (has-cabin ?p)))
  )
 
  (:durative-action build-quarry 
   :parameters (?p - place)
   :duration (= ?duration 10) 
   :condition (at start (mountain ?p))
   :effect (and (at start (increase (labour) 2))
		(at end (has-quarry ?p))))
 
  (:durative-action build-coal-stack 
   :parameters (?p - place) 
   :duration (= ?duration 10)
   :condition (at start (>= (available timber ?p) 1))
   :effect (and (at start (increase (labour) 2))
		(at start (decrease (available timber ?p) 1))
		(at end (has-coal-stack ?p)))) 
 
  (:durative-action build-sawmill 
   :parameters (?p - place) 
   :duration (= ?duration 10)
   :condition (at start (>= (available timber ?p) 2))
   :effect (and (at start (increase (labour) 2))
		(at start (decrease (available timber ?p) 2))
		(at end (has-sawmill ?p)))) 
 
  (:durative-action build-mine 
   :parameters (?p - place) 
   :duration (= ?duration 20)
   :condition (and (at start (metalliferous ?p)) 
		      (at start (>= (available wood ?p) 2)))
   :effect (and (at start (increase (labour) 3))
		(at start (decrease (available wood ?p) 2)) 
		(at end (has-mine ?p))))
 
  (:durative-action build-ironworks 
   :parameters (?p - place) 
   :duration (= ?duration 20)
   :condition (and (at start (>= (available stone ?p) 2))
		      (at start (>= (available wood ?p) 2)))
   :effect (and (at start (increase (labour) 3))
		(at start (decrease (available stone ?p) 2))
		(at start (decrease (available wood ?p) 2))
		(at end (has-ironworks ?p))))
 
  (:durative-action build-docks 
   :parameters (?p - place) 
   :duration (= ?duration 20)
   :condition (and (at start (by-coast ?p))
		      (at start (>= (available stone ?p) 2))
		      (at start (>= (available wood ?p) 2))) 
   :effect (and (at start (decrease (available stone ?p) 2))
		(at start (decrease (available wood ?p) 2))
		(at start (increase (labour) 2))
		(at end (has-docks ?p)))) 
 
  (:durative-action build-wharf 
   :parameters (?p - place) 
   :duration (= ?duration 10)
   :condition (and (at start (has-docks ?p)) 
		      (at start (>= (available stone ?p) 2))
		      (at start (>= (available iron ?p) 2)))
   :effect (and (at start (decrease (available stone ?p) 2))
		(at start (decrease (available iron ?p) 2))
		(at start (increase (labour) 2))
		(at end (has-wharf ?p))))
 
  (:durative-action build-rail 
   :parameters (?p1 - place ?p2 - place) 
   :duration (= ?duration 5)
   :condition (and (over all (connected-by-land ?p1 ?p2))
		      (at start (>= (available wood ?p1) 1))
		      (at start (>= (available iron ?p1) 1)))
   :effect (and (at start (decrease (available wood ?p1) 1))
		(at start (decrease (available iron ?p1) 1))
		(at start (increase (labour) 2))
		(at end (connected-by-rail ?p1 ?p2)))) 

  (:durative-action build-house
   :parameters (?p - place)
   :duration (= ?duration 20)
   :condition (and (at start (>= (available wood ?p) 1))
			(at start (>= (available stone ?p) 1)))
   :effect (and (at end (increase (housing ?p) 1))
		(at start (decrease (available wood ?p) 1))
		(at start (decrease (available stone ?p) 1))))
 
  ;; B.2: Building vehicles. 
 
  (:durative-action build-cart 
   :parameters (?p - place ?v - vehicle) 
   :duration (= ?duration 10)
   :condition (and (at start (>= (available timber ?p) 1)) (at start (potential ?v)))
   :effect (and (at start (decrease (available timber ?p) 1))
		(at end (is-at ?v ?p))
		(at end (is-cart ?v))
		(at start (not (potential ?v)))
		(at end (assign (space-in ?v) 1))
                (at end (assign (available timber ?v) 0))
                (at end (assign (available wood ?v) 0))
                (at end (assign (available coal ?v) 0))
                (at end (assign (available stone ?v) 0))
                (at end (assign (available iron ?v) 0))
                (at end (assign (available ore ?v) 0))
		(at start (increase (labour) 1))
           )
  ) 
 
  (:durative-action build-train 
   :parameters (?p - place ?v - vehicle) 
   :duration (= ?duration 20)
   :condition (and (at start (potential ?v)) (at start (>= (available iron ?p) 2)))
   :effect (and (at start (decrease (available iron ?p) 2))
                (at end (is-at ?v ?p))
                (at end (is-train ?v))
                (at start (not (potential ?v)))
                (at end (assign (space-in ?v) 5))
                (at end (assign (available timber ?v) 0))
                (at end (assign (available wood ?v) 0))
                (at end (assign (available coal ?v) 0))
                (at end (assign (available stone ?v) 0))
                (at end (assign (available iron ?v) 0))
                (at end (assign (available ore ?v) 0))
                (at start (increase (labour) 2))
           ) 
  )
 
  (:durative-action build-ship 
   :parameters (?p - place ?v - vehicle) 
   :duration (= ?duration 30)
   :condition (and (at start (potential ?v))
                      (at start (>= (available iron ?p) 4))
                      (at start (has-wharf ?p))
                 )
   :effect (and 
                (at start (decrease (available iron ?p) 4))
                (at end (is-at ?v ?p))
                (at end (is-ship ?v))
                (at start (not (potential ?v)))
                (at end (assign (space-in ?v) 10))
                (at end (assign (available timber ?v) 0))
                (at end (assign (available wood ?v) 0))
                (at end (assign (available coal ?v) 0))
                (at end (assign (available stone ?v) 0))
                (at end (assign (available iron ?v) 0))
                (at end (assign (available ore ?v) 0))
                (at start (increase (labour) 3))
           ) 
   )
 
  ;; C.1: Obtaining raw resources. 
 
  (:durative-action fell-timber 
   :parameters (?p - place)
   :duration (and (>= ?duration 1) (<= ?duration 100)) 
   :condition (at start (has-cabin ?p))
   :effect (and (at end (increase (available timber ?p) ?duration))
		(at start (increase (labour) ?duration)))
   ) 
 
  (:durative-action break-stone 
   :parameters (?p - place)
   :duration (and (>= ?duration 1) (<= ?duration 100))
   :condition (at start (has-quarry ?p))
   :effect (and (at end (increase (available stone ?p) ?duration))
		(at start (increase (labour) ?duration))
		(at start (increase (resource-use) ?duration))
		)) 
 
  (:durative-action mine-ore 
   :parameters (?p - place) 
   :duration (and (>= ?duration 2) (<= ?duration 200))
   :condition (at start (has-mine ?p))
   :effect (and (at end (increase (available ore ?p) (* ?duration 0.5)))
		(at start (increase (resource-use) ?duration))
	)) 
 
  ;; C.1: Refining resources. 
 
  (:durative-action burn-coal 
   :parameters (?p - place) 
   :duration (= ?duration 1)
   :condition (and (at start (has-coal-stack ?p))
		      (at start (>= (available timber ?p) 1)))
   :effect (and (at start (decrease (available timber ?p) 1))
		(at end (increase (available coal ?p) 1))
		(at start (increase (pollution) 1))))
 
  (:durative-action saw-wood 
   :parameters (?p - place) 
   :duration (= ?duration 1)
   :condition (and (at start (has-sawmill ?p))
		      (at start (>= (available timber ?p) 1)))
   :effect (and (at start (decrease (available timber ?p) 1))
		(at end (increase (available wood ?p) 1))))
 
  (:durative-action make-iron 
   :parameters (?p - place) 
   :duration (= ?duration 2)
   :condition (and (at start (has-ironworks ?p))
		      (at start (>= (available ore ?p) 1))
		      (at start (>= (available coal ?p) 2)))
   :effect (and (at start (decrease (available ore ?p) 1))
		(at start (decrease (available coal ?p) 2))
		(at end (increase (available iron ?p) 1))
		(at start (increase (pollution) 2))))
 
) 
