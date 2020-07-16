cmake_minimum_required(VERSION 3.5)

if (NOT WIN32)
  message(FATAL_ERROR "This project works only on Windows platform!")
endif()

project(log_reader LANGUAGES CXX)

set(LOG_READER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LOG_READER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LOG_READER_SOURCES
  ${LOG_READER_INCLUDE_DIR}/log_reader.h
  ${LOG_READER_SOURCE_DIR}/log_reader.cpp
  ${LOG_READER_INCLUDE_DIR}/log_reader_result.h
  ${LOG_READER_SOURCE_DIR}/log_reader_result.cpp
  ${LOG_READER_SOURCE_DIR}/log_reader_string_result.h
  ${LOG_READER_SOURCE_DIR}/log_reader_string_result.cpp
  ${LOG_READER_SOURCE_DIR}/pattern.h
  ${LOG_READER_SOURCE_DIR}/pattern.cpp
  ${LOG_READER_SOURCE_DIR}/pattern_element.h
  ${LOG_READER_SOURCE_DIR}/pattern_element.cpp
  ${LOG_READER_SOURCE_DIR}/search_stream.h
  ${LOG_READER_SOURCE_DIR}/search_stream.cpp
  ${LOG_READER_SOURCE_DIR}/search_engine.h
  ${LOG_READER_SOURCE_DIR}/search_engine.cpp
  ${LOG_READER_SOURCE_DIR}/search_stream_file_generic.h
  ${LOG_READER_SOURCE_DIR}/search_stream_file_generic.cpp
  ${LOG_READER_SOURCE_DIR}/search_stream_file_direct.h
  ${LOG_READER_SOURCE_DIR}/search_stream_file_direct.cpp
  )

add_library(${PROJECT_NAME} STATIC
  ${LOG_READER_SOURCES}
 )

target_include_directories(${PROJECT_NAME} PUBLIC
  ${LOG_READER_INCLUDE_DIR}
  )

target_include_directories(${PROJECT_NAME} PRIVATE
  ${LOG_READER_SOURCE_DIR}
  )

set(LOG_READER_SOURCES ${LOG_READER_SOURCES} PARENT_SCOPE)
set(LOG_READER_INCLUDE_DIRS
  ${LOG_READER_INCLUDE_DIR}
  ${LOG_READER_SOURCE_DIR}
  PARENT_SCOPE)
