
(define (domain test)
(:requirements :strips :equality :fluents :durative-actions :timed-initial-literals)
(:predicates 
    (goal-met)
) 

(:action meet_goal
   :parameters ()
   :precondition ()
   :effect (goal-met)
) 

)


