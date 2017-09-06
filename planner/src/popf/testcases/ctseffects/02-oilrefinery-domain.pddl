(define (domain oilrefinery)
(:requirements :strips :typing :fluents :durative-actions :duration-inequalities)

(:types product tanker tank processor location
        refinery component - processor
        cracker - component)

(:predicates 
  ;(tanker-for ?p - product)
  (tank-for ?p - product ?t - tank)
  (connected ?p - processor ?t - tank)
  (inactive ?r - refinery)
  (refining ?r - refinery)
  (adjacent ?lone ?ltwo - location)
  (at ?t - tanker ?l - location)
  (tanker-is-for ?t - tanker ?p - product)
  (can-fill ?t - tanker)

)

(:functions 
  (fuel-level ?t - tank) 
  (minimum-level ?t - tank) 
  (capacity ?t - tank)
  (tanker-fuel-level ?t - tanker) 
  (tanker-capacity ?t - tanker)

  (light-ends-percent ?o - oiltype)
  (naptha-percent ?o - oiltype)
  (kerosene-percent ?o - oiltype)
  (light-gasoil-percent ?o - oiltype)
  (pgo-percent ?o - oiltype)
  (refine-rate ?r - refinery)

  (cracking-rate ?c - cracker)
  (tank-fill-rate)
  (barrel-fill-rate)

  (barrels-left)
  (free-hoses)
)

(:constants light-ends naptha kerosene light-gasoil pgo - product
            bythehoses - location)

(:durative-action refine
 :parameters (?r - refinery ?o - oiltype ?let ?nt ?kt ?lgot ?pgot - tank)
 :duration (and (>= ?duration  100)
		 (<= ?duration 100000000))
 :condition (and 
          (at start (tank-for light-ends ?let))
          (at start (connected ?r ?let))
          (over all (<= (fuel-level ?let) (capacity ?let)))

          (at start (tank-for naptha ?nt))
          (at start (connected ?r ?nt))
          (over all (<= (fuel-level ?nt) (capacity ?nt)))

          (at start (tank-for kerosene ?kt))
          (at start (connected ?r ?kt))
          (over all (<= (fuel-level ?kt) (capacity ?kt)))

          (at start (tank-for light-gasoil ?lgot))
          (at start (connected ?r ?lgot))
          (over all (<= (fuel-level ?lgot) (capacity ?lgot)))

          (at start (tank-for pgo ?pgot))
          (at start (connected ?r ?pgot))
          (over all (<= (fuel-level ?pgot) (capacity ?pgot)))
	  )
 :effect (and 
	      (increase (fuel-level ?let) (* #t (* (refine-rate ?r) (light-ends-percent ?o))))
	      (increase (fuel-level ?nt) (* #t (* (refine-rate ?r) (naptha-percent ?o))))
	      (increase (fuel-level ?kt) (* #t (* (refine-rate ?r) (kerosene-percent ?o))))
	      (increase (fuel-level ?lgot) (* #t (* (refine-rate ?r) (light-gasoil-percent ?o))))
	      (increase (fuel-level ?pgot) (* #t (* (refine-rate ?r) (pgo-percent ?o))))
              (at start (not (inactive ?r)))
              (at start (refining ?r))
	  )
)

(:durative-action crack-gasoil
 :parameters (?c - cracker ?lgot - tank ?nt - tank)
 :duration (and (>= ?duration  100)
		 (<= ?duration 100000000))       
 :condition (and 
          (at start (tank-for light-gasoil ?lgot))
          (at start (connected ?c ?lgot))

          (at start (tank-for naptha ?nt))
          (at start (connected ?c ?nt))

          (over all (<= (fuel-level ?lgot) (capacity ?lgot)))
          (over all (<= (fuel-level ?nt) (capacity ?nt)))
          (over all (>= (fuel-level ?lgot) (minimum-level ?lgot)))
	     )
  :effect (and 
	    (increase (fuel-level ?nt) (* #t (cracking-rate ?c)))
	    (decrease (fuel-level ?lgot) (* #t (cracking-rate ?c)))
  )

)

(:durative-action fill-tanker
 :parameters (?t - tank ?l - tanker ?p - product)
 :duration (= ?duration  10)            
 :condition (and 
          (over all (at ?l bythehoses))
          (at start (tanker-is-for ?l ?p))
          (at start (tank-for ?p ?t))
          (at start (can-fill ?l))
	      (over all (>= (fuel-level ?t) (minimum-level ?t)))
          (over all (<= (tanker-fuel-level ?l) (tanker-capacity ?l)))
	    )
:effect (and           
          (at start (not (can-fill ?l)))
	      (increase (tanker-fuel-level ?l) (*#t (tank-fill-rate)))
	      (decrease (fuel-level ?t) (*#t (tank-fill-rate)))
	)

)

(:durative-action tanker-leaves-hoses
 :parameters (?l - tanker ?dest - location)
 :duration (= ?duration  2)            
 :condition (and 
          (at start (at ?l bythehoses))
          (at start (adjacent bythehoses ?dest))
        )
:effect (and 
          (at start (not (at ?l bythehoses)))
          (at start (increase (free-hoses) 1))
          (at end   (at ?l ?dest))          
    )

)

(:durative-action tanker-approaches-hoses
 :parameters (?t - tank ?l - tanker ?from - location)
 :duration (= ?duration  2)            
 :condition (and 
          (at start (at ?l ?from))
          (at start (>= (free-hoses) 1))
          (at start (adjacent ?from bythehoses))
          (at start (<= (tanker-fuel-level ?l) (tanker-capacity ?l)))
        )
:effect (and 
          (at start (not (at ?l ?from)))
          (at start (decrease (free-hoses) 1))
          (at end   (at ?l bythehoses))          
          (at end   (can-fill ?l))
    )
)

(:durative-action store-in-barrel
 :parameters (?t - tank)
 :duration (= ?duration  10)            
 :condition (and 
	      (at start (>= (barrels-left) 1))
	      (over all (>= (fuel-level ?t) (minimum-level ?t)))
	    )
:effect (and 
	      (at start (decrease (barrels-left) 1))
	      (decrease (fuel-level ?t) (*#t (barrel-fill-rate)))
	)

)

)

