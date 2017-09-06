add_test(storage1-action0-should-exist ${insttest_PATH} "(go-out hoist0 depot0-1-1 loadarea)" ${CMAKE_CURRENT_SOURCE_DIR}/domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pfile01.pddl)
add_test(storage1-action1-should-exist ${insttest_PATH} "(lift hoist0 crate0 container-0-0 loadarea container0)" ${CMAKE_CURRENT_SOURCE_DIR}/domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pfile01.pddl)
add_test(storage1-action2-should-exist ${insttest_PATH} "(drop hoist0 crate0 depot0-1-1 loadarea depot0)" ${CMAKE_CURRENT_SOURCE_DIR}/domain.pddl ${CMAKE_CURRENT_SOURCE_DIR}/pfile01.pddl)
