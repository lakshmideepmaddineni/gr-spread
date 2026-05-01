find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_SPREAD gnuradio-spread)

FIND_PATH(
    GR_SPREAD_INCLUDE_DIRS
    NAMES gnuradio/spread/api.h
    HINTS $ENV{SPREAD_DIR}/include
        ${PC_SPREAD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_SPREAD_LIBRARIES
    NAMES gnuradio-spread
    HINTS $ENV{SPREAD_DIR}/lib
        ${PC_SPREAD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-spreadTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_SPREAD DEFAULT_MSG GR_SPREAD_LIBRARIES GR_SPREAD_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_SPREAD_LIBRARIES GR_SPREAD_INCLUDE_DIRS)
