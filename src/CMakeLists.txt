cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ast VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
