cmake_minimum_required(VERSION 3.28)

project(Chip8 CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Options: 
option(ENABLE_SANITIZE "Enable sanitize tooling." OFF)
option(ENABLE_GGDB "Enable ggdb." OFF)

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

# Link Libraries:
target_link_libraries(chip-8 PRIVATE
  # Libraries:
)

# Add Warning flags:
target_compile_options(chip-8 PRIVATE -Wall -Wextra -Wpedantic)

if(ENABLE_GGDB)
  message(STATUS "Enabling -ggdb")
  target_compile_options(chip-8 PRIVATE "-ggdb")
endif()

if(ENABLE_SANITIZE)
  message(STATUS "Enabling sanitizers...")
  target_compile_options(chip-8 PRIVATE "-fsanitize=address,undefined")
  target_link_options(chip-8 PRIVATE -fsanitize=address,undefined)
endif()

# Include Directories:
target_include_directories(chip-8 PRIVATE
  # Include directories:
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(TARGETS chip-8 RUNTIME DESTINATION bin)
