cmake_minimum_required(VERSION 3.28)

project(Chip8 CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
