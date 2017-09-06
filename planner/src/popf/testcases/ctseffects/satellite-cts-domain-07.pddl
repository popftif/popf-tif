
(define (domain satellite)
  (:requirements :strips :equality :typing :fluents :durative-actions)
(:types satellite direction instrument mode)
 (:predicates 
               (on_board ?i - instrument ?s - satellite)
	       (supports ?i - instrument ?m - mode)
	       (pointing ?s - satellite ?d - direction)
	       (power_on ?i - instrument)
	       (calibrated ?i - instrument)
	       (have_image ?d - direction ?m - mode)
	       (calibration_target ?i - instrument ?d - direction)             
	       (canincrease) (candecrease) (increasing) (decreasing) (not-increasing) (not-decreasing) (canfinishincrease) (canfinishdecrease)
               (canfinishflat) (canflat) (flat) (not-flat)
	       
	      (want ?d - direction ?m - mode)
)
 
 

  (:functions (slew_time ?a ?b - direction)
            (calibration_time ?a - instrument ?d - direction)
		(data_capacity ?s - satellite)
		(data ?d - direction ?m - mode)
		(costof ?m - mode)
		(data-stored)
	       (power_avail ?s - satellite)
		(powered)

	)
(:constants
 	satellite0 - satellite
 	satellite1 - satellite
 	satellite2 - satellite
 	satellite3 - satellite
)

(:durative-action power-increasing
:parameters ()
:duration (= ?duration 240)
:condition (and
  (at start (<= (powered) 1))
  (at start (canincrease))
  (at end   (canfinishincrease))
(over all (>= (power_avail satellite0) 0))
(over all (>= (power_avail satellite1) 0))
(over all (>= (power_avail satellite2) 0))
(over all (>= (power_avail satellite3) 0))
  )
:effect
  (and
  (at start (increase (powered) 1))
  (at end (decrease (powered) 1))

  (at start (not (not-increasing)))  
  (at end (not-increasing))  

  (at start (increasing))
  (at end (not (increasing)))

  (at start   (not (canincrease)))
  (at start (canflat))
  (at end     (not (canfinishincrease)))

(increase (power_avail satellite0) (* #t 0.05))
(increase (power_avail satellite1) (* #t 0.05))
(increase (power_avail satellite2) (* #t 0.05))
(increase (power_avail satellite3) (* #t 0.05))
)
)

(:durative-action power-level
:parameters ()
:duration (= ?duration 10000)
:condition (and
  (at start (canflat))
;  (at end   (canfinishflat))
  (at start (<= (powered) 1))
(over all (>= (power_avail satellite0) 0))
(over all (>= (power_avail satellite1) 0))
(over all (>= (power_avail satellite2) 0))
(over all (>= (power_avail satellite3) 0))
  )
:effect
  (and
  (at start (candecrease))
  (at start (canfinishincrease))

  (at start (increase (powered) 1))
  (at end (decrease (powered) 1))

  (at start (not (not-flat)))  
  (at end (not-flat))  

  (at start (flat))
  (at end (not (flat)))

  (at start   (not (canflat)))
 ; (at start   (candecrease))
  (at end     (not (canfinishflat)))

)
)




(:durative-action power-decreasing
:parameters ()
:duration (= ?duration 240)
:condition
(and
  (at start (candecrease))
  (at start (<= (powered) 1))
(over all (>= (power_avail satellite0) 0))
(over all (>= (power_avail satellite1) 0))
(over all (>= (power_avail satellite2) 0))
(over all (>= (power_avail satellite3) 0))
)
:effect
(and 

  (at start (canfinishflat))
  (at start (increase (powered) 1))
  (at end (decrease (powered) 1))
  (at start (not (not-decreasing)))  
  (at end (not-decreasing))  

  (at start (decreasing))
  (at end (not (decreasing)))

  (at start   (not (candecrease)))
;  (at end     (not (canfinishdecrease)))

(decrease (power_avail satellite0) (* #t 0.05))
(decrease (power_avail satellite1) (* #t 0.05))
(decrease (power_avail satellite2) (* #t 0.05))
(decrease (power_avail satellite3) (* #t 0.05))
)

)




 
  (:durative-action switch_on
   :parameters (?i - instrument ?s - satellite)
   :duration (= ?duration 2)
   :condition (and (over all (on_board ?i ?s)) (over all (>= (powered) 1))
                      (at start (>= (power_avail ?s) 1))
   )
   :effect (and (at end (power_on ?i))
                (at start (not (calibrated ?i)))
                (at start (decrease (power_avail ?s) 1))
           )
          
  )

 
  (:durative-action switch_off
   :parameters (?i - instrument ?s - satellite)
   :duration (= ?duration 1)
   :condition (and (over all (on_board ?i ?s))(over all (>= (powered) 1))
                      (at start (power_on ?i)) 
                  )
   :effect (and (at start (not (power_on ?i)))
                (at end (increase (power_avail ?s) 1))
           )
  )

  (:durative-action calibrate
   :parameters (?s - satellite ?i - instrument ?d - direction)
   :duration (= ?duration (calibration_time ?i ?d))
   :condition (and (over all (on_board ?i ?s))(over all (>= (powered) 1))
		      (over all (calibration_target ?i ?d))
                      (at start (pointing ?s ?d))
                      (over all (power_on ?i))
                      (at start (>= (power_avail ?s) 1))
                  )
   :effect (and
		(at end (calibrated ?i)) 
		(at start (decrease (power_avail ?s) 1))
		(at end (increase (power_avail ?s) 1))
	  )
  )


  (:durative-action take_image
   :parameters (?s - satellite ?d - direction ?i - instrument ?m - mode)
   :duration (= ?duration 7)
   :condition (and (over all (calibrated ?i))(over all (>= (powered) 1))
                      (over all (on_board ?i ?s))
                      (over all (supports ?i ?m) )
                      (over all (power_on ?i))
                      (over all (pointing ?s ?d))
		      (at start (>= (power_avail ?s) (costof ?m)))
                      (at end (power_on ?i))
		    (at start (want ?d ?m))
; 			  (at start (>= (data_capacity ?s) (data ?d ?m)))
               )
   :effect (and 
		(at start (not (want ?d ?m)))
;		(at start (decrease (data_capacity ?s) (data ?d ?m)))
		(at end (have_image ?d ?m))
		(at start (decrease (power_avail ?s) (costof ?m)))
		(at end (increase (power_avail ?s) (costof ?m)))
;		(at end (increase (data-stored) (data ?d ?m)))
		)
  )

  (:durative-action turn_to
   :parameters (?s - satellite ?d_new - direction ?d_prev - direction)
   :duration (= ?duration (slew_time ?d_prev ?d_new))
   :condition (and (at start (pointing ?s ?d_prev)) (over all (>= (powered) 1))
              )
   :effect (and  (at end (pointing ?s ?d_new))
                 (at start (not (pointing ?s ?d_prev)))
           )
  )

)
