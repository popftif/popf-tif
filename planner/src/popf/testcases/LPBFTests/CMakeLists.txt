#add_test(airport-temporal-defaults ${popf2_BINARY_DIR}/popf2 -D -I ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)
add_test(airport-temporal-old-heuristic ${popf2_BINARY_DIR}/popf2 -D -I -c ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)
add_test(airport-temporal-total-order ${popf2_BINARY_DIR}/popf2 -D -I -T ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)
#add_test(airport-temporal-defaults-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)
add_test(airport-temporal-old-heuristic-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k -c ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)
add_test(airport-temporal-total-order-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -T -I -k ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-temporal-problem.pddl)

#add_test(driverlog-time-defaults ${popf2_BINARY_DIR}/popf2 -D -I ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)
add_test(driverlog-time-old-heuristic ${popf2_BINARY_DIR}/popf2 -D -I -c ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)
add_test(driverlog-time-total-order ${popf2_BINARY_DIR}/popf2 -D -I -T ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)
#add_test(driverlog-time-defaults-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)
add_test(driverlog-time-old-heuristic-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k -c ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)
add_test(driverlog-time-total-order-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -T -I -k ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/driverlog-time-problem.pddl)

#add_test(rovers-time-defaults ${popf2_BINARY_DIR}/popf2 -D -I -2 ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)
add_test(rovers-time-old-heuristic ${popf2_BINARY_DIR}/popf2 -D -I -2 -c ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)
add_test(rovers-time-total-order ${popf2_BINARY_DIR}/popf2 -D -I -2 -T ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)
#add_test(rovers-time-defaults-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -2 -k ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)
add_test(rovers-time-old-heuristic-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -2 -k -c ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)
add_test(rovers-time-total-order-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -T -2 -I -k ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/rovers-time-problem.pddl)

#add_test(satellite-complex-defaults ${popf2_BINARY_DIR}/popf2 -D -I ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)
add_test(satellite-complex-old-heuristic ${popf2_BINARY_DIR}/popf2 -D -I -c ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)
add_test(satellite-complex-total-order ${popf2_BINARY_DIR}/popf2 -D -I -T ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)
#add_test(satellite-complex-defaults-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)
add_test(satellite-complex-old-heuristic-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -I -k -c ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)
add_test(satellite-complex-total-order-no-action-compression ${popf2_BINARY_DIR}/popf2 -D -T -I -k ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-complex-problem.pddl)


