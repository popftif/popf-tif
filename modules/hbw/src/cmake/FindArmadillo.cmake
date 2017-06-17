find_path(ARMADILLO_INCLUDES
  NAMES
  armadillo
  PATHS
  $ENV{ARMADILLODIR}/include
  ${INCLUDE_INSTALL_DIR}
)


find_library(ARMADILLO_LIBRARIES
  armadillo
  PATHS
  $ENV{ARMADILLODIR}/lib
  ${LIB_INSTALL_DIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(armadillo DEFAULT_MSG
                                  ARMADILLO_INCLUDES ARMADILLO_LIBRARIES)

mark_as_advanced(ARMADILLO_INCLUDES ARMADILLO_LIBRARIES)

