(define (domain oilrefinery)
(:requirements :strips :typing :fluents :durative-actions :duration-inequalities)

(:types product tanker tank processor location oiltype
        refinery component - processor
        cracker splitter platformer blender - component)

(:predicates 
  ;(tanker-for ?p - product)
  (tank-for ?p - product ?t - tank)
  (connected ?p - processor ?t - tank)
  (inactive ?r - processor)
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

  (constituentpercentage ?p - product ?o - (either oiltype product))

  (refine-rate ?r - refinery)
  (blendinputrate ?c - processor ?p - product)

  (rate ?c - component)
  (tank-fill-rate)
  (barrel-fill-rate)

  (barrels-left)
  (free-hoses)
)

(:constants nht naptha lpg c4 tops platformate ccg ulg92 ulg97 - product
            kerosene untreatedcgo gasoil - product
            lco hco bitumen fueloil - product
            bythehoses - location)

(:durative-action refine
 :parameters (?r - refinery ?o - oiltype ?nt ?kt ?uc ?rt - tank)
 :duration (and (>= ?duration  100)
		 (<= ?duration 100000000))
 :condition (and 
          (at start (inactive ?r))
          (at start (tank-for nht ?nt))
          (at start (connected ?r ?nt))
          (over all (<= (fuel-level ?nt) (capacity ?nt)))

          (at start (tank-for kerosene ?kt))
          (at start (connected ?r ?kt))
          (over all (<= (fuel-level ?kt) (capacity ?kt)))

          (at start (tank-for untreatedcgo ?uc))
          (at start (connected ?r ?uc))
          (over all (<= (fuel-level ?uc) (capacity ?uc)))

          (at start (tank-for bitumen ?rt))
          (at start (connected ?r ?rt))
          (over all (<= (fuel-level ?rt) (capacity ?rt)))
	  )
 :effect (and 
            (increase (fuel-level ?nt) (* #t (* 0.01 (* (refine-rate ?r) (constituentpercentage nht ?o)))))	      
            (increase (fuel-level ?kt) (* #t (* 0.01 (* (refine-rate ?r) (constituentpercentage kerosene ?o)))))
            (increase (fuel-level ?uc) (* #t (* 0.01 (* (refine-rate ?r) (constituentpercentage untreatedcgo ?o)))))
            (increase (fuel-level ?rt) (* #t (* 0.01 (* (refine-rate ?r) (constituentpercentage bitumen ?o)))))
	      
            (at start (not (inactive ?r)))
            (at start (refining ?r))
            (at end (not (refining ?r)))
            ;(at end (inactive ?r))
	  )
)


(:durative-action split-nht
 :parameters (?r - refinery ?c - splitter ?nhtt ?lpgt ?c4t ?tt ?nt - tank)
 :duration (and (>= ?duration  10)
         (<= ?duration 100000000))       
 :condition (and 
          (at start (inactive ?c))

          (at start (connected ?r ?nhtt))
          (over all (refining ?r))

          (at start (tank-for nht ?nhtt))
          (at start (connected ?c ?nhtt))

          (at start (tank-for lpg ?lpgt))
          (at start (connected ?c ?lpgt))

          (at start (tank-for c4 ?c4t))
          (at start (connected ?c ?c4t))

          (at start (tank-for tops ?tt))
          (at start (connected ?c ?tt))

          (at start (tank-for naptha ?nt))
          (at start (connected ?c ?nt))

          (over all (<= (fuel-level ?lpgt) (capacity ?lpgt)))
          (over all (<= (fuel-level ?c4t) (capacity ?c4t)))
          (over all (<= (fuel-level ?tt) (capacity ?tt)))
          (over all (<= (fuel-level ?nt) (capacity ?nt)))

          (over all (>= (fuel-level ?nhtt) (minimum-level ?nhtt)))
         )
  :effect (and 
        (at start (not (inactive ?c)))
        (increase (fuel-level ?lpgt) (* #t (* (rate ?c) (* 0.01 (constituentpercentage lpg nht)))))
        (increase (fuel-level ?c4t) (* #t (* (rate ?c) (* 0.01 (constituentpercentage c4 nht)))))
        (increase (fuel-level ?tt) (* #t (* (rate ?c) (* 0.01 (constituentpercentage tops nht)))))
        (increase (fuel-level ?nt) (* #t (* (rate ?c) (* 0.01 (constituentpercentage naptha nht)))))
        (decrease (fuel-level ?nhtt) (* #t (rate ?c)))
        ;(at end (inactive ?c))
  )

)


(:durative-action crack-residue
 :parameters (?r - refinery ?c - cracker ?rt ?lpgt ?ccgt ?lcot ?hcot - tank )
 :duration (and (>= ?duration  100)
		 (<= ?duration 100000000))       

 :condition (and 

          (over all (refining ?r))

          (at start (inactive ?c))

          (at start (tank-for bitumen ?rt))
          (at start (connected ?c ?rt))

          (at start (tank-for lpg ?lpgt))
          (at start (connected ?c ?lpgt))

          (at start (tank-for ccg ?ccgt))
          (at start (connected ?c ?ccgt))

          (at start (tank-for lco ?lcot))
          (at start (connected ?c ?lcot))

          (at start (tank-for hco ?hcot))
          (at start (connected ?c ?hcot))



          (over all (<= (fuel-level ?lpgt) (capacity ?lpgt)))
          (over all (<= (fuel-level ?ccgt) (capacity ?ccgt)))
          (over all (<= (fuel-level ?lcot) (capacity ?lcot)))
          (over all (<= (fuel-level ?hcot) (capacity ?hcot)))

          (over all (>= (fuel-level ?rt) (minimum-level ?rt)))
	     )
  :effect (and 
        (at start (not (inactive ?c)))

        (increase (fuel-level ?lpgt) (* #t (* (rate ?c) (* 0.01 (constituentpercentage lpg bitumen)))))
        (increase (fuel-level ?ccgt) (* #t (* (rate ?c) (* 0.01 (constituentpercentage ccg bitumen)))))
        (increase (fuel-level ?lcot) (* #t (* (rate ?c) (* 0.01 (constituentpercentage lco bitumen)))))
        (increase (fuel-level ?hcot) (* #t (* (rate ?c) (* 0.01 (constituentpercentage hco bitumen)))))

	    (decrease (fuel-level ?rt) (* #t (rate ?c)))

        ;(at end (inactive ?c))
  )

)

(:durative-action run-platformer
 :parameters (?r - refinery ?c - platformer ?nt ?pt - tank)
 :duration (and (>= ?duration  10)
         (<= ?duration 100000000))       
 :condition (and 

          (over all (refining ?r))

          (at start (inactive ?c))

          (at start (tank-for naptha ?nt))
          (at start (connected ?c ?nt))

          (at start (tank-for platformate ?pt))
          (at start (connected ?c ?pt))

          (over all (<= (fuel-level ?pt) (capacity ?pt)))
          (over all (>= (fuel-level ?nt) (minimum-level ?nt)))
         )
  :effect (and 
        (at start (not (inactive ?c)))

        (decrease (fuel-level ?nt) (* #t (rate ?c)))
        (increase (fuel-level ?pt) (* #t (rate ?c)))

        ;(at end (inactive ?c))
  )

)


(:durative-action run-blender
 :parameters (?r - refinery ?c - blender ?c4t ?pt ?tt ?nt ?ccgt ?regt ?premt - tank)
 :duration (and (>= ?duration  100)
         (<= ?duration 100000000))       
 :condition (and 
          (over all (refining ?r))
          (at start (inactive ?c))

          (at start (tank-for c4 ?c4t))
          (at start (connected ?c ?c4t))

          (at start (tank-for platformate ?pt))
          (at start (connected ?c ?pt))

          (at start (tank-for naptha ?nt))
          (at start (connected ?c ?nt))

          (at start (tank-for ccg ?ccgt))
          (at start (connected ?c ?ccgt))

          (at start (tank-for tops ?tt))
          (at start (connected ?c ?tt))

          (at start (tank-for ulg92 ?regt))
          (at start (connected ?c ?regt))

          (at start (tank-for ulg97 ?premt))
          (at start (connected ?c ?premt))

          (over all (>= (fuel-level ?c4t) (minimum-level ?nt)))
          (over all (>= (fuel-level ?pt) (minimum-level ?pt)))
          (over all (>= (fuel-level ?tt) (minimum-level ?tt)))
          (over all (>= (fuel-level ?nt) (minimum-level ?nt)))
          (over all (>= (fuel-level ?ccgt) (minimum-level ?ccgt)))

          (over all (<= (fuel-level ?regt) (capacity ?regt)))
          (over all (<= (fuel-level ?premt) (capacity ?premt)))

         )
  :effect (and 
        (at start (not (inactive ?c)))

        
        (decrease (fuel-level ?c4t) (* #t (blendinputrate ?c c4)))
        (decrease (fuel-level ?pt) (* #t (blendinputrate ?c platformate)))
        (decrease (fuel-level ?tt) (* #t (blendinputrate ?c tops)))
        (decrease (fuel-level ?nt) (* #t (blendinputrate ?c naptha)))
        (decrease (fuel-level ?ccgt) (* #t (blendinputrate ?c ccg)))


        (increase (fuel-level ?premt) (* #t (* 0.5 (+ (blendinputrate ?c c4)
                                                      (+ (blendinputrate ?c platformate)
                                                         (+ (blendinputrate ?c tops)
                                                            (+ (blendinputrate ?c naptha)
                                                               (blendinputrate ?c ccg))))))))

        (increase (fuel-level ?regt) (* #t (* 0.5 (+ (blendinputrate ?c c4)
                                                      (+ (blendinputrate ?c platformate)
                                                         (+ (blendinputrate ?c tops)
                                                            (+ (blendinputrate ?c naptha)
                                                               (blendinputrate ?c ccg))))))))

        ;(at end (inactive ?c))
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

(:durative-action fill-fuel-oil-tanker
 :parameters (?l - tanker ?lcot ?hcot - tank); ?bt - tank)
 :duration (= ?duration  5)            
 :condition (and 
          (over all (at ?l bythehoses))
          (at start (tanker-is-for ?l fueloil))
          (at start (tank-for lco ?lcot))
          (at start (tank-for hco ?hcot))
          ;(at start (tank-for bitumen ?bt))

          (at start (can-fill ?l))
          (over all (>= (fuel-level ?lcot) (minimum-level ?lcot)))
          (over all (>= (fuel-level ?hcot) (minimum-level ?hcot)))
          ;(over all (>= (fuel-level ?bt) (minimum-level ?bt)))
          (over all (<= (tanker-fuel-level ?l) (tanker-capacity ?l)))
        )
:effect (and           
          (at start (not (can-fill ?l)))
          (increase (tanker-fuel-level ?l) (*#t (tank-fill-rate)))
          (decrease (fuel-level ?lcot) (*#t (* (/ 20 50) (tank-fill-rate))))
          (decrease (fuel-level ?hcot) (*#t (* (/ 30 50) (tank-fill-rate))))
          ;(decrease (fuel-level ?bt)   (*#t (* (/ 1 51) (tank-fill-rate))))
    )

)

(:durative-action tanker-leaves-hoses
 :parameters (?l - tanker ?dest - location)
 :duration (= ?duration  2)            
 :condition (and 
          (at start (at ?l bythehoses))
          (at start (adjacent bythehoses ?dest))
          (at start (>= (tanker-fuel-level ?l) (tanker-capacity ?l)))
        )
:effect (and 
          (at start (not (at ?l bythehoses)))
          (at start (increase (free-hoses) 1))
          (at end   (at ?l ?dest))          
    )

)

(:durative-action tanker-approaches-hoses
 :parameters (?l - tanker ?from - location)
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

;(:durative-action store-in-barrel
; :parameters (?t - tank)
; :duration (= ?duration  10)            
; :condition (and 
;	      (at start (>= (barrels-left) 1))
;	      (over all (>= (fuel-level ?t) (minimum-level ?t)))
;	    )
;:effect (and 
;	      (at start (decrease (barrels-left) 1))
;	      (decrease (fuel-level ?t) (*#t (barrel-fill-rate)))
;	)
;
;)

)

