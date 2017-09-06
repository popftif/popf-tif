(define (problem auvprob1)
(:domain power)
(:objects
	auv1 auv2 - auv
	ship1 - ship
	torch1 - torch
	camera1 - camera
	w1 w2 w3 w4 w5 w6 w7 - waypoint
	fish1 fish2 - objective
	gulperauv2 - gulper
)
(:init
	(= (drift-rate) 25)
	(= (recharge-rate auv1) 10)
	
	(at auv1 w2)
	;(at auv1 w4)
	(equipped_for_imaging auv1)
	(available auv1)
	(on_board_camera camera1 auv1)
	;(= (energy auv1) 1000)
	(= (energy auv1) 100000)

	(= (recharge-rate auv1) 50)

	(at auv2 w3)
	;(at auv2 w5)
	(equipped_with_gulper auv2)
	(has_torch auv2)
	(on_board_torch torch1 auv2)
	(off torch1)
	(empty gulperauv2)
	(has_gulper auv2)
	(on_board_gulper gulperauv2 auv2)
	(available auv2)
	;(= (energy auv2) 1000)
	(= (energy auv2) 1000000)
	(= (recharge-rate auv2) 50)

        (at_water_sample w7)
	(visible_from_ship fish2 ship1)
	
	(visible_from fish1 w5)
	(visible_from fish1 w4)

	(visible_from fish2 w6)
	(visible_from fish2 w7)

	(= (light-level fish1) 0)
	(= (light-level fish2) 0)


	;(free w2)
	;(free w3)
	(free w4)
	(free w5)
	(free w6)
	(free w7)

	(can_traverse w2 w7)
	(can_traverse w7 w2)
	(can_traverse w2 w6)
	(can_traverse w6 w2)
	(can_traverse w2 w5)
	(can_traverse w5 w2)
	(can_traverse w2 w4)
	(can_traverse w4 w2)
	(can_traverse w3 w7)
	(can_traverse w7 w3)
	(can_traverse w3 w6)
	(can_traverse w6 w3)
	(can_traverse w3 w5)
	(can_traverse w5 w3)
	(can_traverse w4 w3)
	(can_traverse w6 w5)
	(can_traverse w5 w6)
	(at_surface w2)
	(at_surface w3)

	(= (distance w2 w7) 5)
	(= (distance w7 w2) 5)
	(= (distance w2 w6) 5)
	(= (distance w6 w2) 5)
	(= (distance w2 w5) 5)
	(= (distance w5 w2) 5)
	(= (distance w2 w4) 5)
	(= (distance w4 w2) 5)
	(= (distance w3 w7) 5)
	(= (distance w7 w3) 5)
	(= (distance w3 w6) 5)
	(= (distance w6 w3) 5)
	(= (distance w3 w5) 5)
	(= (distance w5 w3) 5)
	(= (distance w4 w3) 5)
	(= (distance w6 w5) 5)
	(= (distance w5 w6) 5)


	(is-ship w1)
	(has_light ship1)
	(off_light ship1)
	(channel_free)
	(= (drift-rate) 50)

	(calibration_target camera1 fish1)

	(= (distance-from auv1 fish1) 1000000)
	(= (distance-from auv1 fish2) 1000000)

)
(:goal (and
	(communicated_image_data fish1)
	;(have_image auv1 fish1)
	;(communicated_image_data fish2)
	;(have_image auv1 fish1)
	;(have_water_sample auv2 w7)
	
))
;(:metric minimize (planmetric))
)
