(define (problem testproblem)
(:domain test)

(:init
    (= (goal-variable) 1)
    (at 10 (= (goal-variable) 0))
)
(:goal (>= (goal-variable) 1)
)
)

