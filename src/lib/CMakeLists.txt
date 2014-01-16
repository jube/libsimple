
set(LIBSIMPLE_SRC
  log.cc
)

add_library(simple0 SHARED
  ${LIBSIMPLE_SRC}
)

install(
  TARGETS simple0
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
