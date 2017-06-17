(define (problem test)
    (:domain eo-dynamic)
    (:objects
	sat1 - satellite
	osite-1 - observationsite 
	osite-2 - observationsite 
	osite-3 - observationsite 
	osite-4 - observationsite 
	osite-5 - observationsite 
	osite-6 - observationsite 
	osite-7 - observationsite 
	osite-8 - observationsite 
	osite-9 - observationsite 
	patch-1-1 - patch
	patch-2-1 - patch
	patch-3-1 - patch
	patch-4-1 - patch
	patch-5-1 - patch
	patch-7-1 - patch
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
	(= (ang-acc-max-N sat1) 0.000385)
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
	(= (ignore-penalty osite-4) 100000)
	(= (ignore-penalty osite-5) 100000)
	(= (ignore-penalty osite-6) 100000)
	(= (ignore-penalty osite-7) 100000)
	(= (ignore-penalty osite-8) 100000)
	(= (ignore-penalty osite-9) 100000)

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

	(belongsto patch-4-1 osite-4)
	(scannedby patch-4-1 sat1)
	(= (scan-velocity patch-4-1) 6000.000000)
	(= (x-entry patch-4-1) 5013737.373884)
	(= (y-entry patch-4-1) 90282.343447)
	(= (z-entry patch-4-1) 693863.000000)
	(= (x-exit  patch-4-1) 5314356.872157)
	(= (y-exit  patch-4-1) 85130.689807)
	(= (z-exit  patch-4-1) 693863.000000)

	(belongsto patch-5-1 osite-5)
	(scannedby patch-5-1 sat1)
	(= (scan-velocity patch-5-1) 6800.000000)
	(= (x-entry patch-5-1) 3829431.945463)
	(= (y-entry patch-5-1) 204788.628261)
	(= (z-entry patch-5-1) 693863.000000)
	(= (x-exit  patch-5-1) 4307856.387679)
	(= (y-exit  patch-5-1) 53921.172743)
	(= (z-exit  patch-5-1) 693863.000000)

	(belongsto patch-7-1 osite-7)
	(scannedby patch-7-1 sat1)
	(= (scan-velocity patch-7-1) 6800.000000)
	(= (x-entry patch-7-1) 2207668.086809)
	(= (y-entry patch-7-1) -205016.532981)
	(= (z-entry patch-7-1) 693863.000000)
	(= (x-exit  patch-7-1) 3176597.231111)
	(= (y-exit  patch-7-1) 45396.269807)
	(= (z-exit  patch-7-1) 693863.000000)

	(not-dealt osite-1)
	(not-dealt osite-2)
	(not-dealt osite-3)
	(not-dealt osite-4)
	(not-dealt osite-5)
	(not-dealt osite-6)
	(not-dealt osite-7)
	(not-dealt osite-8)
	(not-dealt osite-9)

	(not-ignored osite-1)
	(not-ignored osite-2)
	(not-ignored osite-3)	
	(not-ignored osite-4)	
	(not-ignored osite-5)	
	(not-ignored osite-6)	
	(not-ignored osite-7)	
	(not-ignored osite-8)	
	(not-ignored osite-9)	

	(= (total-cost) 0)	
	)

    (:goal (and
	    (dealt osite-1)
	    (dealt osite-2)
	    (dealt osite-3)
	    (dealt osite-4)
	    (dealt osite-5)
	    (dealt osite-6)
	    (dealt osite-7)
	    (dealt osite-8)
	    (dealt osite-9)
	    ))

    (:metric minimize (total-cost))
    )