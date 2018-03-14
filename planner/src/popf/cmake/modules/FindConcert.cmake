# include(FindLibraryWithDebug)

if (CONCERT_INCLUDES AND CONCERT)
  set(CONCERT_FIND_QUIETLY TRUE)
endif (CONCERT_INCLUDES AND CONCERT)

find_path(CONCERT_INCLUDES
  NAMES
  ilconcert/iloenv.h
  PATHS
  $ENV{CPLEXHOME}/concert/include
)

find_library(CONCERT
  concert
  PATHS
  $ENV{CPLEXHOME}/concert/lib/x86-64_osx/static_pic/
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(concert DEFAULT_MSG
                                  CONCERT_INCLUDES CONCERT)

mark_as_advanced(CONCERT_INCLUDES CONCERT)

