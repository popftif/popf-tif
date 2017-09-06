# include(FindLibraryWithDebug)

if (CONCERT_INCLUDES AND CONCERT)
  set(CONCERT_FIND_QUIETLY TRUE)
endif (CONCERT_INCLUDES AND CONCERT)

find_path(CONCERT_INCLUDES
  NAMES
  ilconcert/iloenv.h
  PATHS
  /Users/chiara/Applications/IBM/ILOG/CPLEX_Studio1261/concert/include
)

find_library(CONCERT
  concert
  PATHS
  /Users/chiara/Applications/IBM/ILOG/CPLEX_Studio1261/concert/lib/x86-64_osx/static_pic/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(concert DEFAULT_MSG
                                  CONCERT_INCLUDES CONCERT)

mark_as_advanced(CONCERT_INCLUDES CONCERT)

