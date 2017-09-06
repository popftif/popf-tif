add_test(satellite-time-TILs ${popf2_BINARY_DIR}/popf2 -I -D -c -r -s ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-plan)
add_test(satellite-complextime-TILs ${popf2_BINARY_DIR}/popf2 -I -D -c -r -s ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-plan)

add_test(simple-TIL-fluents ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf3-cplex ${CMAKE_CURRENT_SOURCE_DIR}/simple-TIL-fluent-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/simple-TIL-fluent-problem.pddl)
add_test(invariants-with-TIL-fluents ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf3-cplex ${CMAKE_CURRENT_SOURCE_DIR}/TIL-fluent-invariant-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/TIL-fluent-invariant-problem.pddl)

add_test(TIL-propositional-goal-persistence ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf3-cplex ${CMAKE_CURRENT_SOURCE_DIR}/TIL-propositional-goal-persistence-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/TIL-propositional-goal-persistence-problem.pddl)
add_test(TIL-numeric-goal-persistence ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf3-cplex ${CMAKE_CURRENT_SOURCE_DIR}/TIL-numeric-goal-persistence-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/TIL-numeric-goal-persistence-problem.pddl)
add_test(TIL-numeric-and-propositional-goal-persistence ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf3-cplex ${CMAKE_CURRENT_SOURCE_DIR}/TIL-numeric-and-propositional-goal-persistence-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/TIL-numeric-and-propositional-goal-persistence-problem.pddl)
