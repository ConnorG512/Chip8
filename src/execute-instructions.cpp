#include "app-renderer.hpp"
#include "device.hpp"
#include "execute-instructions.hpp"

#include <array>
#include <cassert>
#include <iostream>
#include <string_view>
#include <variant>

namespace
{
template <typename... Callable> struct visitor : Callable...
{
  using Callable::operator()...;
};

void print_unimplemented(std::string_view label) { std::cout << "Unimplemented instruction: " << label << '\n'; }
} // namespace

void Chip8::execute(DecodeTypes::List decode_list, Device &device, AppRenderer &renderer)
{
  assert(decode_list.index() != std::variant_npos);

  std::visit(
      visitor{
          [&device](DecodeTypes::ClearDisplay) -> auto { device.screen_buffer_.clear_buffer(); },

          [](DecodeTypes::ReturnFromSubroutine) -> auto { print_unimplemented("return_from_subroutine"); },

          [&device](DecodeTypes::JumpAddress jump_address) -> auto
          { device.program_counter_.set_counter(jump_address.value); },

          [&device](DecodeTypes::SkipNextInstructionEqual skip_next_instructions_equal) -> auto
          {
            const auto register_id{skip_next_instructions_equal.register_id};

            if (device.registers_.at(register_id).get_data() == skip_next_instructions_equal.value)
            {
              device.program_counter_.increment_program();
            }
          },

          [](DecodeTypes::SkipNextInstructionNotEqual) -> auto
          { print_unimplemented("skip_next_instructions_not_equal"); },

          [](DecodeTypes::SkipNextInstructionEqualRegister) -> auto
          { print_unimplemented("skip_next_instructions_equal_register"); },

          [&device](DecodeTypes::SetValueToRegister set_value_to_register) -> auto
          { device.registers_.at(set_value_to_register.register_id).assign_val(set_value_to_register.value); },

          [&device](DecodeTypes::AddValueToRegister add_value_to_register) -> auto
          { device.registers_.at(add_value_to_register.register_id).add_val(add_value_to_register.value); },

          [](DecodeTypes::RegisterToRegisterArith) -> auto { print_unimplemented("register_to_register_arith"); },

          [&device](DecodeTypes::LoadIntoIndexRegister load_into_index_register) -> auto
          { device.index_register_.assign_val(load_into_index_register.value); },

          [&device, &renderer](DecodeTypes::DrawToScreen draw_instruction) -> auto
          {
            for (auto reg : {draw_instruction.register_id_1, draw_instruction.register_id_2})
            {
              static constexpr auto max_register_count{15};
              assert(reg <= max_register_count);
            }

            const auto reg_1_value{device.registers_.at(draw_instruction.register_id_1).get_data()};
            const auto reg_2_value{device.registers_.at(draw_instruction.register_id_2).get_data()};
            const auto value{draw_instruction.bytes_to_draw};

            renderer.prepare_fullscreen_texture(device.screen_buffer_.create_new_screen_buffer(
                {.x = reg_1_value, .y = reg_2_value},
                device.mem_buf_.fetch_sprite_data(device.index_register_.get_data(), value)));
          },
      },
      decode_list);
}
