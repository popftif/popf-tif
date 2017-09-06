add_test(pipesnt-11-can-be-solved-test-scheduling ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-11.pddl)
add_test(pipesnt-11-can-be-solved-cplex ${popf2_BINARY_DIR}/popf2-cplex -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-11.pddl)
add_test(pipesnt-11-can-be-solved-clp ${popf2_BINARY_DIR}/popf2-clp -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-11.pddl)
add_test(pipesnt-11-can-be-solved-stp ${popf2_BINARY_DIR}/popf2 -I -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-11.pddl)

add_test(pipesnt-12-can-be-solved-test-scheduling ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-12-can-be-solved-cplex ${popf2_BINARY_DIR}/popf2-cplex -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-12-can-be-solved-clp ${popf2_BINARY_DIR}/popf2-clp -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-12-can-be-solved-stp ${popf2_BINARY_DIR}/popf2 -I -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)

add_test(pipesnt-21-can-be-solved-test-scheduling ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-21-can-be-solved-cplex ${popf2_BINARY_DIR}/popf2-cplex -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-21-can-be-solved-clp ${popf2_BINARY_DIR}/popf2-clp -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)
add_test(pipesnt-21-can-be-solved-stp ${popf2_BINARY_DIR}/popf2 -I -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pipesnt-problem-12.pddl)


add_test(matchlift-02-can-be-solved-test-scheduling ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/matchlift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/matchlift-problem-02.pddl)

