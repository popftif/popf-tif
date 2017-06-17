(define (problem test)
    (:domain eo-dynamic)
    (:objects
	sat1 - satellite
	osite-1 - observationsite 
	osite-2 - observationsite 
	osite-3 - observationsite 
	patch-1-1 - patch
	patch-2-1 - patch
	patch-3-1 - patch
	)

    (:init
	(skip-osite-possible)
	(pointing-nowhere sat1)
	(idle sat1)
	(= (x-pos sat1) 0)
	(= (x-horizon sat1) 7072000.000000)
	(= (roll-max-N sat1) 0.610865)
	(= (pitch-max-N sat1) 0.610865)
	(= (ang-rate-x-max-N sat1) 0.174533)
	(= (ang-rate-y-max-N sat1) 0.174533)
	(= (ang-rate-z-max-N sat1) 0.174533)
	(= (ang-acc-max-N sat1) 0.001155)
	(= (roll-angle sat1) 0.000000)
	(= (pitch-angle sat1) 0.000000)
	(= (yaw-angle sat1) 0.000000)
	(= (roll-rate sat1) 0.000000)
	(= (pitch-rate sat1) 0.000000)
	(= (yaw-rate sat1) 0.000000)
	(= (subTrace-velocity sat1) 6839.205052)

	(= (ignore-penalty osite-1) 100000)
	(= (ignore-penalty osite-2) 100000)
	(= (ignore-penalty osite-3) 100000)

	(belongsto patch-1-1 osite-1)
	(scannedby patch-1-1 sat1)
	(= (scan-velocity patch-1-1) 12000.000000)
	(= (x-entry patch-1-1) 1538739.900295)
	(= (y-entry patch-1-1) 228385.003327)
	(= (z-entry patch-1-1) 693863.000000)
	(= (x-exit  patch-1-1) 2541393.504133)
	(= (y-exit  patch-1-1) 271802.033861)
	(= (z-exit  patch-1-1) 693863.000000)

	(belongsto patch-2-1 osite-2)
	(scannedby patch-2-1 sat1)
	(= (scan-velocity patch-2-1) 6800.000000)
	(= (x-entry patch-2-1) 2653538.640903)
	(= (y-entry patch-2-1) 357971.092086)
	(= (z-entry patch-2-1) 693863.000000)
	(= (x-exit  patch-2-1) 3517046.837260)
	(= (y-exit  patch-2-1) -157505.657952)
	(= (z-exit  patch-2-1) 693863.000000)

	(belongsto patch-3-1 osite-3)
	(scannedby patch-3-1 sat1)
	(= (scan-velocity patch-3-1) 6000.000000)
	(= (x-entry patch-3-1) 4791671.658840)
	(= (y-entry patch-3-1) 268077.916505)
	(= (z-entry patch-3-1) 693863.000000)
	(= (x-exit  patch-3-1) 5092994.160199)
	(= (y-exit  patch-3-1) 264526.909465)
	(= (z-exit  patch-3-1) 693863.000000)

	(not-dealt osite-1)
	(not-dealt osite-2)
	(not-dealt osite-3)

	(not-ignored osite-1)
	(not-ignored osite-2)
	(not-ignored osite-3)

	(= (total-cost) 0)	
	
	)

    (:goal (and
	    (dealt osite-1)
	    (dealt osite-2)
	    (dealt osite-3)
	    ))

    (:metric minimize (total-cost))
    )