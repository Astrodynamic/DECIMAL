cmake_minimum_required(VERSION 3.28.3)
project(Decimal VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

set(HEADERS
  include/decimal.h
)

set(SOURCES
  source/decimal.cc
)

set(PROJECT_RESOURCES
  ${HEADERS}
  ${SOURCES}
)

add_library(${PROJECT_NAME}
  STATIC
  ${PROJECT_RESOURCES}
)

target_compile_features(${PROJECT_NAME}
  PUBLIC
  cxx_std_17
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE

  # -Wall
  # -Werror
  # -Wextra
  # -Wpedantic
)



add_executable(${PROJECT_NAME}_main
  main.cc
)

target_link_libraries(${PROJECT_NAME}_main
  ${PROJECT_NAME}
)