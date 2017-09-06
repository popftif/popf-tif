
(define (domain test)
(:requirements :strips :equality :fluents :durative-actions :timed-initial-literals)
(:predicates 
    (goal-met)
) 

(:functions (currentvalue)
        
)

(:action meet_goal
   :parameters ()
   :precondition (and (>= (currentvalue) 5)
                      (<= (currentvalue) 7)
                 )
   :effect (goal-met)
) 

)


