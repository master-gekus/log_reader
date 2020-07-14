cmake_minimum_required(VERSION 3.5)

if (NOT WIN32)
  message(FATAL_ERROR "This project works only on Windows platform!")
endif()

project(test_task LANGUAGES CXX)

add_subdirectory(log_reader)
add_subdirectory(test_app)
add_subdirectory(unit_tests)

