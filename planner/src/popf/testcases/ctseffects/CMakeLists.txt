add_test(generator-solution-could-be-found ${popf2_BINARY_DIR}/popf2 -I -r -s -H -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/generator-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-plan)
add_test(generator-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/generator-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-problem.pddl)
add_test(generator-fill-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/generator-fill-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-fill-problem.pddl)
add_test(generator-fill-solution-could-be-found ${popf2_BINARY_DIR}/popf2 -I -r -s -H -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/generator-fill-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-fill-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/generator-fill-plan)
add_test(auv-solution-could-be-found ${popf2_BINARY_DIR}/popf2 -I -r -s -H -v17 ${CMAKE_CURRENT_SOURCE_DIR}/auv-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/auv-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/auv-plan)


add_test(satellite-cts-solution-could-be-found ${popf2_BINARY_DIR}/popf2 -I -r -s -H -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-problem-01.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-plan-01)
add_test(satellite-cts-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-problem-01.pddl)
add_test(settlers-cts-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/settlers-cts-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/settlers-cts-problem-02.pddl)
add_test(transformer-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -c -v1 ${CMAKE_CURRENT_SOURCE_DIR}/transformer-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/transformer-problem-01.pddl)

add_test(satellite-cts-07-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-domain-07.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-problem-07.pddl)
add_test(satellite-cts-07-integrated-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 -gmakectsinstantaneous ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-domain-07.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-cts-problem-07.pddl)

add_test(01-oilrefinery-can-be-solved ${popf2_BINARY_DIR}/popf2 -I -D -T -v1 ${CMAKE_CURRENT_SOURCE_DIR}/01-oilrefinery-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/01-oilrefinery-problem.pddl)

add_test(02-oil-refinary-validates ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-problem.pddl  -I -D -v1)
add_test(02-oil-refinary-TO-validates ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-problem.pddl  -I -D -v1 -T)
add_test(02-oil-read-plan-and-validate ${popf2_read_plan_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-problem.pddl ${CMAKE_CURRENT_SOURCE_DIR}/02-oilrefinery-sequence -I -D -v1)

