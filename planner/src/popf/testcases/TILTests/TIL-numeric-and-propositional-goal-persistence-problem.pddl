(define (problem testproblem)
(:domain test)

(:init
    (= (goal-variable) 1)
    (at 10 (= (goal-variable) 0))
    (at 20 (not (goal-met)))
)
(:goal (and (>= (goal-variable) 1)
            (goal-met)
       )
)
)

