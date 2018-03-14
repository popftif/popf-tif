# include(FindLibraryWithDebug)

if (CPLEX_INCLUDES AND CPLEX AND ILOCPLEX)
  set(CPLEX_FIND_QUIETLY TRUE)
endif (CPLEX_INCLUDES AND CPLEX AND ILOCPLEX)

find_path(CPLEX_INCLUDES
  NAMES
  ilcplex/cplex.h
  PATHS
  $ENV{CPLEXHOME}/cplex/include
)

find_library(CPLEX
  cplex
  PATHS
  $ENV{CPLEXHOME}/cplex/lib/x86-64_osx/static_pic/
)

find_library(ILOCPLEX
  ilocplex
  PATHS
  $ENV{CPLEXHOME}/cplex/lib/x86-64_osx/static_pic/
)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(cplex DEFAULT_MSG
                                  CPLEX_INCLUDES CPLEX ILOCPLEX)

mark_as_advanced(CPLEX_INCLUDES CPLEX ILOCPLEX)

