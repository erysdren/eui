
# necessary includes
include(GNUInstallDirs)

# configure pkg-config script
configure_file(${PROJECT_SOURCE_DIR}/cmake/eui.pc.in ${PROJECT_BINARY_DIR}/eui.pc @ONLY)

# do install
install(TARGETS eui DESTINATION ${CMAKE_INSTALL_LIBDIR}/eui)
install(FILES ${EUI_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/eui)
install(FILES ${PROJECT_BINARY_DIR}/eui.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
