
(define (domain test)
(:requirements :strips :equality :fluents :durative-actions :timed-initial-literals)
(:functions
    (goal-variable)
) 

(:action meet_goal
   :parameters ()
   :precondition ()
   :effect (and (increase (goal-variable) 1))
) 

)


