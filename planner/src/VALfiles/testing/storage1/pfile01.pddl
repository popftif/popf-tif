; Map of the Depots:    
; * 
;-- 
; 0: depot0 area
; *: Depot access point
; =: Transit area

(define (problem storage-1)
(:domain Storage-Propositional)
(:objects
	depot0-1-1 container-0-0 - storearea
	hoist0 - hoist
	crate0 - crate
	container0 - container
	depot0 - depot
	loadarea - transitarea)

(:init
	(insa depot0-1-1 depot0)
	(on crate0 container-0-0)
	(incr crate0 container0)
	(insa container-0-0 container0)
	(connected loadarea container-0-0) 
	(connected container-0-0 loadarea)  
	(connected depot0-1-1 loadarea)
	(connected loadarea depot0-1-1)    
	(at hoist0 depot0-1-1)
	(available hoist0))

(:goal (and
	(incr crate0 depot0)))
)
