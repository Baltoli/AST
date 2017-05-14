add_executable(print
  src/print.cpp)

target_link_libraries(print
  ast)

install(TARGETS print EXPORT ASTConfig
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
