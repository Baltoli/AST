project(libast VERSION 0.1 LANGUAGES CXX)

add_library(ast
  src/ast.cpp
  src/ast_print.cpp
  src/parser.cpp)

target_compile_features(ast PUBLIC
  cxx_auto_type 
  cxx_return_type_deduction)

target_include_directories(ast PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE src)

install(TARGETS ast EXPORT ASTConfig
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ASTConfig DESTINATION share/AST/cmake)
export(TARGETS ast FILE ASTConfig.cmake)

add_executable(testast
  test/test.cpp
  test/ast.cpp
  test/ast_print.cpp
  test/parser.cpp)

target_link_libraries(testast
  ast)

add_test(TestAST testast)
