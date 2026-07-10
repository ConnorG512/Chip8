#include "register.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

auto main() -> int
{
  Chip8::Register<std::uint8_t> Reg0{};
  Chip8::Register<std::uint8_t> Reg1{};
  Chip8::Register<std::uint8_t> Reg2{};
  Chip8::Register<std::uint8_t> Reg3{};
  Chip8::Register<std::uint8_t> Reg4{};
  Chip8::Register<std::uint8_t> Reg5{};
  Chip8::Register<std::uint8_t> Reg6{};
  Chip8::Register<std::uint8_t> Reg7{};
  Chip8::Register<std::uint8_t> Reg8{};
  Chip8::Register<std::uint8_t> Reg9{};
  Chip8::Register<std::uint8_t> RegA{};
  Chip8::Register<std::uint8_t> RegB{};
  Chip8::Register<std::uint8_t> RegC{};
  Chip8::Register<std::uint8_t> RegD{};
  Chip8::Register<std::uint8_t> RegE{};
  Chip8::Register<std::uint8_t> RegF{};
  Chip8::Register<std::uint16_t> RegI{};
  Chip8::Register<std::uint16_t> RegPC{};

  try
  {
  }
  catch (std::exception &e)
  {
    std::cerr << "Exception Caught! Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cerr << "Unknown Exception Caught!" << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
