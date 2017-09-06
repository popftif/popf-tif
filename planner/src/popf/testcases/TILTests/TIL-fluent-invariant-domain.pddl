
(define (domain test)
(:requirements :strips :equality :fluents :durative-actions :timed-initial-literals)
(:predicates 
    (can-start)
    (goal-met)
) 

(:functions (currentvalue)
        
)

(:durative-action meet_goal
   :parameters ()
   :duration (= ?duration 10)
   :condition (and (at start (can-start))
                   (over all (>= (currentvalue) 5))
                   (over all (<= (currentvalue) 7))
              )
   :effect (and 
                (at start (not (can-start)))
                (at end (goal-met))
                 
           )
) 

)


