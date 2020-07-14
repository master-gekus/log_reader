cmake_minimum_required(VERSION 3.5)

if (NOT WIN32)
  message(FATAL_ERROR "This project works only on Windows platform!")
endif()

project(test_app LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  test_app.cpp
  ascii_string.h
  ascii_string.cpp
  )

target_link_libraries(${PROJECT_NAME}
  log_reader
  )
