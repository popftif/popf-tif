;; Earth Observation Scenario for the Kontiplan project
;; 
(define (domain eo-dynamic)
    (:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects ); :modules)
    (:types 
	observationsite - object	 ; an observationsite refers to a patch on ground before preprocessing
	patch - object ; a patch visible from a specific orbit scannable in a specific direction
	; an observationsite has multiple patches in the
	; planning problem - one for each direction and one
	; for each orbit 
	satellite - object 
	)

    ;    (:modules
    ;	(t_scan ?pat - patch ?sat - satellite cost scanTimeOfPatch@/Users/chiara/Work/Code/tfdm2013/tfd-develop/module_api/eo-dynamic/build/libEODynamic.dylib); = l_patch / v_scan
    ;	(t_target ?pat - patch ?sat - satellite cost targetingTimeOfPatch@/Users/chiara/Work/Code/tfdm2013/tfd-develop/module_api/eo-dynamic/build/libEODynamic.dylib)
    ;	(end_pose_reachable ?pat - patch ?sat - satellite conditionchecker endPoseAfterScanning@/Users/chiara/Work/Code/tfdm2013/tfd-develop/module_api/eo-dynamic/build/libEODynamic.dylib)
    ;	(scan_effects 
    ;	    ?pat - patch ?sat - satellite 
    ;	    (x-pos ?sat) 
    ;	    (roll-angle ?sat) (pitch-angle ?sat) (yaw-angle ?sat) 
    ;	    (roll-rate ?sat) (pitch-rate ?sat) (yaw-rate ?sat) 
    ;	    effect scanEffects@/Users/chiara/Work/Code/tfdm2013/tfd-develop/module_api/eo-dynamic/build/libEODynamic.dylib)   
    ;
    ;	(target_effects 
    ;	    ?p - patch ?s - satellite 
    ;	    (x-pos ?s) 
    ;	    (roll-angle ?s) (pitch-angle ?s) (yaw-angle ?s)
    ;	    (roll-rate ?s) (pitch-rate ?s) (yaw-rate ?s)
    ;	    effect targetEffects@/Users/chiara/Work/Code/tfdm2013/tfd-develop/module_api/eo-dynamic/build/libEODynamic.dylib) 
    ;	)

    (:predicates 
	(belongsto ?p - patch ?o - observationsite) ; the patch p is one instance of observationsite o
	(scannedby ?p - patch ?s - satellite)       ; since the positions of a patch are relative to a satellite, each patch 
	; can be scanned only by the corresponding satellite
	(dealt ?o - observationsite)  ; the obsevationsite has been scanned or was skipped
	(not-skipped ?o - observationsite)  ; the obsevationsite has been scanned or was skipped
	(not-dealt ?o - observationsite)  ; the obsevationsite has been scanned or was skipped
	(idle ?sat - satellite)   ; a Satellite may only scan one patch at
	; a time and has to be "idle" to do so
	(skip-osite-possible)     ; if this variable is true in the initial
	; state, scanning patches becomes a soft
	; goal with skipping-penalty specified by
	; "ignore-penalty"
	(reached ?p - patch ?sat - satellite) ; is set after a
	; successfull
	; "target-patch" action
	(pointing-nowhere ?sat - satellite)
	(not-pointing-nowhere ?sat - satellite)
	(not-ignored ?o - observationsite)	
	)

    (:functions 
	(x-entry ?p - patch)          ; x-coordinate of the start of the patch in Nadir Frame
	(y-entry ?p - patch)          ; y-coordinate of the start of the patch
	(z-entry ?p - patch)          ; z-coordinate of the start of the patch
	(x-exit ?p - patch)           ; x-coordinate of the end of the patch
	(y-exit ?p - patch)           ; y-coordinate of the end of the patch
	(z-exit ?p - patch)           ; z-coordinate of the end of the patch
	(scan-velocity ?p - patch)	 ; The patch knows its corresponding
	; satellite, and the instrument with
	; wich it wants to be
	; scanned. Therefore the
	; scan-velocity is attached to the
	; patch

	(ignore-penalty ?o - observationsite)   ; penatly obtained, if the planner
	; does not manage to scan the observationsite 
	(x-pos ?satl - satellite)        ; x coordinate of the satellite
	; position y and z coordinate are
	; always 0 after preprocessing,
	; height differences can be modeled
	; with the patch heigth (z-entry
	; ?p) and (z-exit ?p) if needed
	(x-horizon ?satl - satellite)   ; horizon of the problem, position after which the planning problem ends

	(roll-max-N ?sat - satellite)    ; maximal roll angle in Nadir frame (x-Axis)
	(pitch-max-N ?sat - satellite)   ; maximal pitch angle in Nadir frame (y-Axis)
	(ang-rate-x-max-N ?sat - satellite)  ; maximal angular rate around the roll axis in Nadir frame
	(ang-rate-y-max-N ?sat - satellite)  ; maximal angular rate around the pitch axis in Nadir frame
	(ang-rate-z-max-N ?sat - satellite)  ; maximal angular rate around the yaw axis in Nadir frame
	(ang-acc-max-N ?sat - satellite)  ; maximal angular acceleration in Nadir frame
	(roll-angle ?satl - satellite)      	; current roll angle 
	(pitch-angle ?satl - satellite)     	; current pich angle 
	(yaw-angle ?satl - satellite)     	; current yaw angle 
	(roll-rate ?satl - satellite)      	; current roll rate 
	(pitch-rate ?satl - satellite)     	; current pich rate 
	(yaw-rate ?satl - satellite)     	; current yaw rate 
	(subtrace-velocity ?satl - satellite) ; absolute value of the satellite |v_GT|
	;; added
	(t_scan ?patch - patch ?sat - satellite ?o - observationsite)
	(t_target ?path - patch ?sat - satellite ?o - observationsite)
	(end_pose_reachable ?patch - patch ?sat - satellite ?o - observationsite)
	(is-patching ?patch - patch ?sat - satellite ?o - observationsite)
	(is-scanning ?patch - patch ?sat - satellite ?o - observationsite)	
	(is-ignoring ?osite - observationsite)	
	(total-cost)	
	)

    ;    (:derived (all-idle) (and (skip-osite-possible)
    ;	    (forall (?s - satellite) (idle ?s))))
    ;    (:derived (available ?sat - satellite) (and (idle ?sat) (skip-osite-possible)))

    (:durative-action ignore-site  ; since scanning a patch is a
	; soft-goal, it is always possible
	; to ignore a patch - incurring at a
	; cost specified in the numeric
	; variable "ignore-penalty"
  	:parameters (?osite - observationsite)
  	:duration (= ?duration 1)
  	:condition (and
	    (at start (skip-osite-possible))
	    (at start (forall (?s - satellite) (idle ?s)))	    
	    (at start (not-ignored ?osite))	    	    
	    (at start (not-dealt ?osite))	    	    
	    (at start (forall (?patch - patch ?sat - satellite) (< (is-scanning ?patch ?sat ?osite) 100000)))	    
 	    (at start (forall (?sat - satellite) (< (x-pos ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (x-horizon ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (yaw-angle ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (pitch-angle ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (roll-angle ?sat) 1000000000)))	    
 	    (at start (forall (?sat - satellite) (< (yaw-rate ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (pitch-rate ?sat) 1000000000)))
 	    (at start (forall (?sat - satellite) (< (roll-rate ?sat) 1000000000)))
	    (at start (forall (?patch - patch ?s - satellite) (< (t_target ?patch ?s ?osite) 10000000)))
	    (at start (forall (?patch - patch ?s - satellite) (< (t_scan ?patch ?s ?osite) 10000000)))
	    (at start (< (is-ignoring ?osite) 1000000000))

	    )
  	:effect (and
	    (at start (not (skip-osite-possible)))
	    (at end (dealt ?osite))
	    (at end (not (not-dealt ?osite)))
	    (at end (skip-osite-possible))

	    (at end (increase (total-cost) (ignore-penalty ?osite)))
	    
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-patching ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-scanning ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?oo - observationsite) (at start (assign (is-ignoring ?oo) 0)))  ;; hack
	    (at end (assign (is-ignoring ?osite) 1))    ;; hack
	    
	    (forall (?sat - satellite ) (and
		    (at start (increase (x-horizon ?sat) 0))
 		    (at end (decrease (x-horizon ?sat) 0))	    
 		    (at start (increase (x-pos ?sat) 0))
 		    (at end (decrease (x-pos ?sat) 0))
		    (at start (increase (yaw-angle ?sat) 0))
		    (at end (decrease (yaw-angle ?sat) 0))
		    (at start (increase (pitch-angle ?sat) 0))
		    (at end (decrease (pitch-angle ?sat) 0))
		    (at start (increase (roll-angle ?sat) 0))
		    (at end (decrease (roll-angle ?sat) 0))
		    (at start (increase (yaw-rate ?sat) 0))
		    (at end (decrease (yaw-rate ?sat) 0))
		    (at start (increase (pitch-rate ?sat) 0))
		    (at end (decrease (pitch-rate ?sat) 0))
		    (at start (increase (roll-rate ?sat) 0))
		    (at end (decrease (roll-rate ?sat) 0)))
		)
	    (forall (?patch - patch ?sat - satellite )  (and
		    (at start (increase (t_scan ?patch ?sat ?osite) 0))
		    (at end (decrease (t_scan ?patch ?sat ?osite) 0))
		    (at start (increase (t_target ?patch ?sat ?osite) 0))
		    (at end (decrease (t_target ?patch ?sat ?osite) 0))))
	    (at start (not (not-ignored ?osite)))		
	    ))
    
    (:durative-action target-patch
	:parameters (?s - satellite ?p - patch ?o - observationsite)
	:duration (= ?duration 1)
	:condition (and 
	    (at start (belongsto ?p ?o))
	    (at start (scannedby ?p ?s))
	    (at start (> (subtrace-velocity ?s) 0))
	    (at start (idle ?s))
	    (at start (not-dealt ?o))
	    (at start (skip-osite-possible))
	    (at start (pointing-nowhere ?s))
	    (at start (< (is-patching ?p ?s ?o) 3)) ; hack	    	    
	    )
	:effect (and 
	    (at start (not (idle ?s)))
	    (at end (idle ?s))  
	    (at end (reached ?p ?s))
	    (at start (not (pointing-nowhere ?s)))
	    (at start (not-pointing-nowhere ?s))
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-patching ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-scanning ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?oo - observationsite) (at start (assign (is-ignoring ?oo) 0)))  ;; hack
	    (at end (assign (is-patching ?p ?s ?o) 1))    ;; hack
	    (at end (increase (total-cost)	(t_scan ?p ?s ?o)))
	    (at end (increase (end_pose_reachable ?p ?s ?o) 1))
	    
	    )
	)
    
    (:durative-action scan-patch
	:parameters (?s - satellite ?p - patch ?o - observationsite)
	:duration (= ?duration 1)
	:condition (and 
	    (at start (belongsto ?p ?o))
	    (at start (scannedby ?p ?s))
	    (at start (idle ?s))
	    (at start (skip-osite-possible))
	    (at start (not-dealt ?o))
	    ;; (at start (> (x-exit ?p) (x-entry ?p)))
	    ;; (at start (> (y-exit ?p) (y-entry ?p)))
	    (at start (reached ?p ?s))
	    (at start (not-pointing-nowhere ?s))
	    (at start (= (end_pose_reachable ?p ?s ?o) 1)) 	    
	    (at start (< (is-scanning ?p ?s ?o) 3)) ; hack	    
	    )				   
	:effect (and 
	    (at start (not (idle ?s)))
	    (at end (idle ?s))  
	    (at end (dealt ?o)) 
	    (at end (not-skipped ?o)) 
	    (at end (not (not-dealt ?o)))
	    (at end (pointing-nowhere ?s))
	    (at end (not (not-pointing-nowhere ?s)))
	    (at end (not (reached ?p ?s)))
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-patching ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?ss - satellite ?pp - patch ?oo - observationsite) (at start (assign (is-scanning ?pp ?ss ?oo) 0)))  ;; hack
	    (forall (?oo - observationsite) (at start (assign (is-ignoring ?oo) 0)))  ;; hack
	    (at end (assign (is-scanning ?p ?s ?o) 1))    ;; hack
	    (at end (decrease (total-cost)	(t_scan ?p ?s ?o)))
	    
	    ))


    )



