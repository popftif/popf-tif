add_test(satellite-complex-partial-order ${popf2_BINARY_DIR}/popf2 -I -Q -c ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-problem.pddl)
add_test(satellite-complex-total-order ${popf2_BINARY_DIR}/popf2 -I -Q -T ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-problem.pddl)

add_test(airport-05-partial-order ${popf2_BINARY_DIR}/popf2 -I -Q -c ${CMAKE_CURRENT_SOURCE_DIR}/airport-05-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-05-problem.pddl)
add_test(airport-05-total-order ${popf2_BINARY_DIR}/popf2 -I -Q -T ${CMAKE_CURRENT_SOURCE_DIR}/airport-05-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-05-problem.pddl)

add_test(landing-partial-order ${popf2_BINARY_DIR}/popf2 -I -Q -c ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-problem.pddl)
add_test(landing-total-order ${popf2_BINARY_DIR}/popf2 -I -Q -T ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-problem.pddl)

add_test(cafe-partial-order ${popf2_BINARY_DIR}/popf2 -I -Q -c ${CMAKE_CURRENT_SOURCE_DIR}/cafe-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/cafe-problem.pddl)
add_test(cafe-total-order ${popf2_BINARY_DIR}/popf2 -I -Q -T ${CMAKE_CURRENT_SOURCE_DIR}/cafe-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/cafe-problem.pddl)

add_test(landing-05-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-05-problem.pddl -I -Q -T)
add_test(landing-05-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-05-problem.pddl -Q -T)

add_test(satellite-05-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-05-problem.pddl -I -Q -T)
add_test(satellite-05-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-05-problem.pddl -Q -T)
add_test(satellite-05-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-05-problem.pddl -Q -T -I -k)
add_test(satellite-05-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-05-problem.pddl -Q -T -k)

add_test(airport-03-partial-order ${popf2_BINARY_DIR}/popf2 -I -Q -c ${CMAKE_CURRENT_SOURCE_DIR}/airport-03-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-03-problem.pddl)
add_test(airport-03-total-order ${popf2_BINARY_DIR}/popf2 -I -Q -T ${CMAKE_CURRENT_SOURCE_DIR}/airport-03-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/airport-03-problem.pddl)

add_test(satellite-min-07-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-07-problem.pddl -I -Q -T)
add_test(satellite-min-07-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-07-problem.pddl -Q -T)
add_test(satellite-min-07-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-07-problem.pddl -Q -T -I -k)
add_test(satellite-min-07-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-07-problem.pddl -Q -T -k)

#add_test(landing-17-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-17-problem.pddl -I -Q -T)
#add_test(landing-17-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/landing-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/landing-17-problem.pddl -Q -T)

add_test(satellite-min-11-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-11-problem.pddl -I -Q -T)
add_test(satellite-min-11-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-11-problem.pddl -Q -T)
add_test(satellite-min-11-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-11-problem.pddl -Q -T -I -k)
add_test(satellite-min-11-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-11-problem.pddl -Q -T -k)

add_test(satellite-min-01-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-01-problem.pddl -I -Q -T)
add_test(satellite-min-01-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-01-problem.pddl -Q -T)
add_test(satellite-min-01-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-01-problem.pddl -Q -T -I -k)
add_test(satellite-min-01-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-01-problem.pddl -Q -T -k)

add_test(satellite-min-02-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-02-problem.pddl -I -Q -T)
add_test(satellite-min-02-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-02-problem.pddl -Q -T)
add_test(satellite-min-02-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-02-problem.pddl -Q -T -I -k)
add_test(satellite-min-02-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-02-problem.pddl -Q -T -k)

add_test(satellite-min-03-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-03-problem.pddl -I -Q -T)
add_test(satellite-min-03-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-03-problem.pddl -Q -T)
add_test(satellite-min-03-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-03-problem.pddl -Q -T -I -k)
add_test(satellite-min-03-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-03-problem.pddl -Q -T -k)

add_test(satellite-min-04-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-04-problem.pddl -I -Q -T)
add_test(satellite-min-04-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-04-problem.pddl -Q -T)
add_test(satellite-min-04-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-04-problem.pddl -Q -T -I -k)
add_test(satellite-min-04-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-04-problem.pddl -Q -T -k)

add_test(satellite-min-05-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-05-problem.pddl -I -Q -T)
add_test(satellite-min-05-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-05-problem.pddl -Q -T)
add_test(satellite-min-05-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-05-problem.pddl -Q -T -I -k)
add_test(satellite-min-05-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-05-problem.pddl -Q -T -k)

#add_test(satellite-min-06-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-06-problem.pddl -I -Q -T)
#add_test(satellite-min-06-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-06-problem.pddl -Q -T)
#add_test(satellite-min-06-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-06-problem.pddl -Q -T -I -k)
#add_test(satellite-min-06-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-06-problem.pddl -Q -T -k)

add_test(satellite-min-08-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-08-problem.pddl -I -Q -T)
add_test(satellite-min-08-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-08-problem.pddl -Q -T)
add_test(satellite-min-08-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-08-problem.pddl -Q -T -I -k)
add_test(satellite-min-08-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-08-problem.pddl -Q -T -k)

add_test(satellite-min-09-total-order-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-09-problem.pddl -I -Q -T)
add_test(satellite-min-09-total-order-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-09-problem.pddl -Q -T)
add_test(satellite-min-09-total-order-no-compression-BF-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-09-problem.pddl -Q -T -I -k)
add_test(satellite-min-09-total-order-no-compression-validate ${popf2_then_validate} ${val_BINARY_DIR}/validate ${popf2_BINARY_DIR}/popf2 ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/satellite-min-09-problem.pddl -Q -T -k)
