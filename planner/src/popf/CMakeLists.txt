PROJECT(popf2)

set( CMAKE_MODULE_PATH    ${CMAKE_MODULE_PATH}
                          ${CMAKE_CURRENT_SOURCE_DIR}
                          ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                          ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules)

find_package(Clp)
find_package(CoinUtils)
find_package(Cbc)
find_package(Cgl)
find_package(OSI)
find_package(Concert)
find_package(Cplex)

IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -DIL_STD -I")
ENDIF()

set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")

if(STATIC_POPF)
set(CMAKE_CXX_LINK_FLAGS "-static ${CMAKE_CXX_LINK_FLAGS}")
endif(STATIC_POPF)

include_directories(${val_SOURCE_DIR} ${val_SOURCE_DIR}/parsing ${val_BINARY_DIR} ${CLP_INCLUDES}/coin ${CBC_INCLUDES}/coin ${CPLEX_INCLUDES} ${CONCERT_INCLUDES} )

set(popf2_build_srcs 
    ExternalSolver.cpp 
    LookAhead.cpp 
    ModifiedSearch.cpp
    Color.cpp 
    TimewindowsChecker.cpp 
    DotSearchSpace.cpp
    compressionsafescheduler.cpp
    totalordertransformer.cpp
    partialordertransformer.cpp
    FFSolver.cpp
    FFEvent.cpp
    globals.cpp
    lpscheduler.cpp
    RPGBuilder.cpp
    RPGBuilderAnalysis.cpp
    RPGBuilderEvaluation.cpp
    RPGBuilderNumerics.cpp
    temporalanalysis.cpp
    minimalstate.cpp
    temporalconstraints.cpp
    numericanalysis.cpp
    solver.cpp)

set(colin_build_srcs
    compressionsafescheduler.cpp
    colintotalordertransformer.cpp
    FFSolver.cpp
    FFEvent.cpp
    globals.cpp
    lpscheduler.cpp
    RPGBuilder.cpp
    RPGBuilderAnalysis.cpp
    RPGBuilderEvaluation.cpp
    RPGBuilderNumerics.cpp
    temporalanalysis.cpp
    minimalstate.cpp
    temporalconstraints.cpp
    numericanalysis.cpp
    solver.cpp)

add_library(POPF2Common STATIC ${popf2_build_srcs})
target_link_libraries(POPF2Common ParsePDDL Inst)

add_library(POPF3Common STATIC ${popf2_build_srcs})
target_link_libraries(POPF3Common ParsePDDL Inst)
SET_TARGET_PROPERTIES(POPF3Common PROPERTIES COMPILE_FLAGS "-DPOPF3ANALYSIS")

add_library(StochasticPOPF2Common STATIC ${popf2_build_srcs} StochasticDurations.cpp)
target_link_libraries(StochasticPOPF2Common ParsePDDL Inst)
SET_TARGET_PROPERTIES(StochasticPOPF2Common PROPERTIES COMPILE_FLAGS "-DSTOCHASTICDURATIONS -DPOPF3ANALYSIS")

add_library(ColinCommon STATIC ${colin_build_srcs})
target_link_libraries(ColinCommon ParsePDDL Inst)
SET_TARGET_PROPERTIES(ColinCommon PROPERTIES COMPILE_FLAGS "-DTOTALORDERSTATES -DPOPF3ANALYSIS")


if (CLP_INCLUDES AND CBC_INCLUDES)
    ADD_EXECUTABLE(popf2-clp popfMain.cpp solver-clp.cpp)
    
    target_link_libraries(popf2-clp
        POPF2Common
        ${CBC_SOLVER_LIBRARY} ${CBC_LIBRARY} ${CGL_LIBRARIES} ${OSICLP_LIBRARIES} ${OSI_LIBRARIES} ${CLP_LIBRARIES}  ${COINUTILS_LIBRARIES}
    )

    ADD_EXECUTABLE(popf3-clp popfMain.cpp solver-clp.cpp)
    
    target_link_libraries(popf3-clp
        POPF3Common
        ${CBC_SOLVER_LIBRARY} ${CBC_LIBRARY} ${CGL_LIBRARIES} ${OSICLP_LIBRARIES} ${OSI_LIBRARIES} ${CLP_LIBRARIES}  ${COINUTILS_LIBRARIES} bz2 z dl
    )
    SET_TARGET_PROPERTIES(popf3-clp PROPERTIES COMPILE_FLAGS "-DPOPF3ANALYSIS")

    ADD_EXECUTABLE(colin-clp popfMain.cpp solver-clp.cpp)

    target_link_libraries(colin-clp
        ColinCommon
        ${CBC_SOLVER_LIBRARY} ${CBC_LIBRARY} ${CGL_LIBRARIES} ${OSICLP_LIBRARIES} ${OSI_LIBRARIES} ${CLP_LIBRARIES}  ${COINUTILS_LIBRARIES} z bz2
    )
    SET_TARGET_PROPERTIES(colin-clp PROPERTIES COMPILE_FLAGS "-DTOTALORDERSTATES -DPOPF3ANALYSIS -DBUILDINGCOLIN")



endif(CLP_INCLUDES AND CBC_INCLUDES)

if(CPLEX AND ILOCPLEX AND CONCERT AND CPLEX_INCLUDES AND CONCERT_INCLUDES)
  ADD_EXECUTABLE(popf2-cplex popfMain.cpp solver-cpx.cpp)
    
    target_link_libraries(popf2-cplex    
        POPF2Common
        ${ILOCPLEX} ${CPLEX} ${CONCERT} pthread
    )

    ADD_EXECUTABLE(popf3-cplex popfMain.cpp solver-cpx.cpp)
    
    target_link_libraries(popf3-cplex    
            POPF3Common
            ${CONCERT} ${ILOCPLEX} ${CPLEX} pthread m
    )
    SET_TARGET_PROPERTIES(popf3-cplex PROPERTIES COMPILE_FLAGS "-DPOPF3ANALYSIS")
    
    ADD_EXECUTABLE(colin-cplex popfMain.cpp solver-cpx.cpp)

    target_link_libraries(colin-cplex
        ColinCommon
        ${ILOCPLEX} ${CPLEX} ${CONCERT} pthread
    )
    SET_TARGET_PROPERTIES(colin-cplex PROPERTIES COMPILE_FLAGS "-DTOTALORDERSTATES -DPOPF3ANALYSIS")
    
endif(CPLEX AND ILOCPLEX AND CONCERT AND CPLEX_INCLUDES AND CONCERT_INCLUDES)

if(CPLEX AND ILOCPLEX AND CONCERT AND CPLEX_INCLUDES AND CONCERT_INCLUDES AND CLP_INCLUDES AND CBC_INCLUDES)
    ADD_EXECUTABLE(colin-both popfMain.cpp solver-cpx.cpp solver-clp.cpp solver-both.cpp)

    target_link_libraries(colin-both
        ColinCommon
        ${CBC_SOLVER_LIBRARY} ${CBC_LIBRARY} ${CGL_LIBRARIES} ${OSICLP_LIBRARIES} ${OSI_LIBRARIES} ${CLP_LIBRARIES}  ${COINUTILS_LIBRARIES}
        ${ILOCPLEX} ${CPLEX} ${CONCERT} pthread
    )
    SET_TARGET_PROPERTIES(colin-both PROPERTIES COMPILE_FLAGS "-DTOTALORDERSTATES -DPOPF3ANALYSIS -DMULTIPLESOLVERS")
endif(CPLEX AND ILOCPLEX AND CONCERT AND CPLEX_INCLUDES AND CONCERT_INCLUDES AND CLP_INCLUDES AND CBC_INCLUDES)

enable_testing()
add_subdirectory(testcases)
