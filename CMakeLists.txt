cmake_minimum_required(VERSION 3.28)

project(Chip8 CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

find_program(CLANG_TIDY_EXEC "clang-tidy")
if(CLANG_TIDY_EXEC)
  message(STATUS "Clang Tidy found... Path: ${CLANG_TIDY_EXEC}")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXEC};-p=${CMAKE_BINARY_DIR}")
elseif(NOT CLANG_TIDY_EXEC)
  message(STATUS "Clang tidy could not be found! Cannot run analysis.")
endif()

add_executable(chip-8 
  src/main.cpp
  src/timer.cpp
)

target_link_libraries(chip-8 PRIVATE
  # Libraries:
)

target_include_directories(chip-8 PRIVATE
  # Include directories:
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(TARGETS chip-8 RUNTIME DESTINATION bin)
