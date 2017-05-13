add_executable(astc
  src/astc.cpp)

target_link_libraries(astc
  ast)

install(TARGETS astc EXPORT ASTConfig
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
