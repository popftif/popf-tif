(define (problem CafeProblem1)
	(:domain CafeDomain)
	(:objects 
		table1  - table
		tea1  - tea
		toast1  - toast
		socket1 - socket
		chef1 - chef
	)
	(:init
		(d_w_available table1)
		(chef_free chef1)
		(socket_free socket1)
	)
	(:goal
		(and
		(delivered tea1 table1)
		(delivered toast1 table1)
		)
	)
(:metric minimize (total_heat_lost))
)
