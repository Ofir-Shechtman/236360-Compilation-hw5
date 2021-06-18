cmake_minimum_required(VERSION 3.13)
project(hw5)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw5 RegisterManager.cpp semantics.cpp SymbolTable.cpp parser.tab.cpp bp.cpp hw3_output.cpp lex.yy.cpp llvm_funcs.cpp )