add_test(driverlogshift1-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-01.pddl)

add_test(driverlogshift2-plan-could-be-found ${popf2_BINARY_DIR}/popf2 -r -s -I -D -v1 -T ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-02.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-plan-02)
#add_test(driverlogshift2-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-02.pddl)

add_test(driverlogshift3-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-03.pddl)
#add_test(driverlogshift4-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-04.pddl)
#add_test(driverlogshift5-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-05.pddl)
#add_test(driverlogshift6-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-06.pddl)
#add_test(driverlogshift7-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-07.pddl)
#add_test(driverlogshift8-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-08.pddl)
add_test(driverlogshift9-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlogshift-problem-09.pddl)

