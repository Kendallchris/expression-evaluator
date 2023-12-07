cmake_minimum_required(VERSION 3.10)
project(GetEvalSteps)

set(CMAKE_CXX_STANDARD 14)

add_executable(Evaluator main.cpp evaluator.cpp evaluator.h test_scripts.cpp test_scripts.h)