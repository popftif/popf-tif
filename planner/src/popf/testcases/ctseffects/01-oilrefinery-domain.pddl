(define (domain oilrefinery)
(:requirements :strips :typing :fluents :durative-actions :duration-inequalities)

(:types product tanker tank)

(:predicates 
  ;(tanker-for ?p - product)
  (tank-for ?p - product)
  (light-ends-tank ?t - tank)
  (naptha-tank ?t - tank)
  (kerosene-tank ?t - tank)
  (light-gasoil-tank ?t - tank)
  (pgo-tank ?t - tank)
  (inactive ?r - refinery)
  (refining ?r - refinery)

)

(:functions 
  (fuel-level ?t - tank) 
  (capacity ?t - tank)
  (tanker-fuel-level ?t - tanker) 
  (tanker-capacity ?t - tanker)

  (light-ends-percent ?o - oiltype)
  (naptha-percent ?o - oiltype)
  (kerosene-percent ?o - oiltype)
  (light-gasoil-percent ?o - oiltype)
  (pgo-percent ?o - oiltype)

  (cracking-rate)
  (tank-fill-rate)
  (barrel-fill-rate)

  (barrels-left)
)

(:durative-action refine
 :parameters (?r - refinery ?o - oiltype ?let ?nt ?kt ?lgot ?pgot - tank)
 :duration (and (>= ?duration  100) (<= ?duration 100000))
 :condition (and 
	      (at start (light-ends-tank ?let))
              (over all (<= (fuel-level ?let) (capacity ?let)))
	      (at start (naptha-tank ?nt))
              (over all (<= (fuel-level ?nt) (capacity ?nt)))
	      (at start (kerosene-tank ?kt))
              (over all (<= (fuel-level ?kt) (capacity ?kt)))
	      (at start (light-gasoil-tank ?lgot))
              (over all (<= (fuel-level ?lgot) (capacity ?lgot)))
	      (at start (pgo-tank ?pgot))
              (over all (<= (fuel-level ?pgot) (capacity ?pgot)))
	  )
 :effect (and 
	      (increase (fuel-level ?let) (* #t (light-ends-percent ?o)))
	      (increase (fuel-level ?nt) (* #t (naptha-percent ?o)))
	      (increase (fuel-level ?kt) (* #t (kerosene-percent ?o)))
	      (increase (fuel-level ?lgot) (* #t (light-gasoil-percent ?o)))
	      (increase (fuel-level ?pgot) (* #t (pgo-percent ?o)))
              (at start (not (inactive ?r)))
              (at start (refining ?r))
	  )
)

(:durative-action crack-gasoil
 :parameters (?lgot - tank ?nt - tank)
 :duration (and (>= ?duration  100) (<= ?duration 100000))
 :condition (and 
		(at start (light-gasoil-tank ?lgot))
		(at start (naptha-tank ?nt))
                (over all (<= (fuel-level ?lgot) (capacity ?lgot)))
                (over all (<= (fuel-level ?nt) (capacity ?nt)))
                (over all (>= (fuel-level ?lgot) 0))
	     )
  :effect (and 
	    (increase (fuel-level ?nt) (* #t (cracking-rate)))
	    (decrease (fuel-level ?lgot) (* #t (cracking-rate)))
  )

)

(:durative-action fill-tanker
 :parameters (?t - tank ?l - tanker)
 :duration (= ?duration  10)            
 :condition (and 
	      (over all (>= (fuel-level ?t) 0))
	    )
:effect (and 
	      (increase (tanker-fuel-level ?l) (*#t (tank-fill-rate)))
	      (decrease (fuel-level ?t) (*#t (tank-fill-rate)))
	)

)

(:durative-action store-in-barrel
 :parameters (?t - tank)
 :duration (= ?duration  10)            
 :condition (and 
	      (at start (>= (barrels-left) 1))
	      (over all (>= (fuel-level ?t) 0))
	    )
:effect (and 
	      (at start (decrease (barrels-left) 1))
	      (decrease (fuel-level ?t) (*#t (barrel-fill-rate)))
	)

)

)

