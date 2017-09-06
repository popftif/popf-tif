add_test(t3-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/t3-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/t3-problem.pddl)
add_test(t3-solution-could-be-found ${popf2_BINARY_DIR}/popf2 -I -r -s -H -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/t3-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/t3-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/t3-solution)

