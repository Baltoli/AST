add_executable(l1c
  src/main.cpp
  src/language.cpp)

target_link_libraries(l1c
  ast)

install(TARGETS l1c EXPORT ASTConfig
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
