cmake_minimum_required(VERSION 3.5)

if (NOT WIN32)
  message(FATAL_ERROR "This project works only on Windows platform!")
endif()

project(log_reader LANGUAGES CXX)

set(LOG_READER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/log_reader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/log_reader.cpp
  )

add_library(${PROJECT_NAME} STATIC
  ${LOG_READER_SOURCES}
 )

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

set(LOG_READER_SOURCES ${LOG_READER_SOURCES} PARENT_SCOPE)
set(LOG_READER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
