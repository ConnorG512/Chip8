#include "device.hpp"
#include "execute-instructions.hpp"

#include <cassert>
#include <type_traits>
#include <variant>

void Chip8::execute(DecodeTypes::List decode_list, Device &device)
{
  assert(decode_list.index() != std::variant_npos);

  std::visit(
      [&device](auto &&list) -> auto
      {
        using DecT = std::decay_t<decltype(list)>;

        if constexpr (std::is_same_v<DecT, DecodeTypes::ClearDisplay>)
        {
          device.screen_buffer.clear_screen();
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::ReturnFromSubroutine>)
        {
          // TODO
          return;
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::JumpAddress>)
        {
          device.program_counter_.set_counter(list.value);
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::SkipNextInstructionEqual>)
        {
          // TODO
          return;
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::SkipNextInstructionNotEqual>)
        {
          // TODO
          return;
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::SkipNextInstructionEqualRegister>)
        {
          // TODO
          return;
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::SetValueToRegister>)
        {
          device.registers_.at(list.register_id).assign_val(list.value);
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::AddValueToRegister>)
        {
          device.registers_.at(list.register_id).add_val(list.value);
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::RegisterToRegisterArith>)
        {
          // TODO
          return;
        }

        if constexpr (std::is_same_v<DecT, DecodeTypes::LoadIntoIndexRegister>)
        {
          device.index_register_.assign_val(list.value);
        }
      },
      decode_list);
}
