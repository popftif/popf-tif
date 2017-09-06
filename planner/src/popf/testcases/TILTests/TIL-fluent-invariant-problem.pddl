(define (problem testproblem)
(:domain test)

(:init
    (can-start)
    (= (currentvalue) 6)
    (at 2 (= (currentvalue) 10))
    (at 4 (= (currentvalue) 6))
)
(:goal (goal-met)
)
)

