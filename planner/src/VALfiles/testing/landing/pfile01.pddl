(define (problem KLM)
	(:domain landing)
	(:objects  FR6659_CARCASSONNE - plane
		main -runway)


	(:init (free main)
		(ready)
		(= (exponential-earliest FR6659_CARCASSONNE) 20)
		(= (exponential-target FR6659_CARCASSONNE) 30)
		(= (exponential-latest FR6659_CARCASSONNE) 40)
		(= (latePenalty FR6659_CARCASSONNE) 500)
		(= (latePenaltyRate FR6659_CARCASSONNE) 50)
		(= (earlyPenaltyRate FR6659_CARCASSONNE) 30)
		(= (total-cost) 0)
		(= (fake-duration) 0)
	)
(:constraints (and
	(within 50 (landed FR6659_CARCASSONNE))
))
(:metric minimize (total-cost))
)
