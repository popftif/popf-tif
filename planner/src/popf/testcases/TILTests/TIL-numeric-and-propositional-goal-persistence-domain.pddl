
(define (domain test)
(:requirements :strips :equality :fluents :durative-actions :timed-initial-literals)
(:predicates
    (goal-met)
)

(:functions
    (goal-variable)
) 

(:action meet_goal_variable
   :parameters ()
   :precondition ()
   :effect (and (increase (goal-variable) 1))
) 

(:action meet_goal
   :parameters ()
   :precondition ()
   :effect (and (goal-met))
) 


)


