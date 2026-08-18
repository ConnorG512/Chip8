#include "execute-instructions.hpp"
#include "app-renderer.hpp"
#include "program-counter.hpp"
#include "cpu.hpp"
#include "memory.hpp"

#include <iostream>
#include <string_view>

namespace
{
template <typename... Callable> struct visitor : Callable...
{
  using Callable::operator()...;
};

void print_unimplemented(std::string_view label) { std::cout << "Unimplemented instruction: " << label << '\n'; }
} // namespace

void Chip8::execute(DecodeTypes::List decode_list, Cpu &cpu, Memory &memory, ProgramCounter &pc, AppRenderer &renderer)
{
  std::visit(
      visitor{
          [&memory](DecodeTypes::ClearDisplay) -> auto { memory.scr_buf.clear_buffer(); },

          [](DecodeTypes::ReturnFromSubroutine) -> auto { print_unimplemented("return_from_subroutine"); },

          [&pc](DecodeTypes::JumpAddress jump_address) -> auto
          { pc.set_counter(jump_address.value); },

          [&cpu, &pc](DecodeTypes::SkipNextInstructionEqual skip_next_instructions_equal) -> auto
          {
            const auto register_id{skip_next_instructions_equal.register_id};

            if (cpu.registers.at(register_id).get_data() == skip_next_instructions_equal.value)
            {
              pc.increment_program();
            }
          },

          [](DecodeTypes::SkipNextInstructionNotEqual) -> auto
          { print_unimplemented("skip_next_instructions_not_equal"); },

          [](DecodeTypes::SkipNextInstructionEqualRegister) -> auto
          { print_unimplemented("skip_next_instructions_equal_register"); },

          [&cpu](DecodeTypes::SetValueToRegister set_value_to_register) -> auto
          { cpu.registers.at(set_value_to_register.register_id).assign_val(set_value_to_register.value); },

          [&cpu](DecodeTypes::AddValueToRegister add_value_to_register) -> auto
          { cpu.registers.at(add_value_to_register.register_id).add_val(add_value_to_register.value); },

          [](DecodeTypes::RegisterToRegisterArith) -> auto { print_unimplemented("register_to_register_arith"); },

          [&cpu](DecodeTypes::LoadIntoIndexRegister load_into_index_register) -> auto
          { cpu.index_register.assign_val(load_into_index_register.value); },

          [&cpu, &memory, &renderer](DecodeTypes::DrawToScreen draw_instruction) -> auto
          {
            for (auto reg : {draw_instruction.register_id_1, draw_instruction.register_id_2})
            {
              static constexpr auto max_register_count{15};
              contract_assert(reg <= max_register_count);
            }

            const auto reg_1_value{cpu.registers.at(draw_instruction.register_id_1).get_data()};
            const auto reg_2_value{cpu.registers.at(draw_instruction.register_id_2).get_data()};
            const auto value{draw_instruction.bytes_to_draw};

            renderer.prepare_fullscreen_texture(memory.scr_buf.create_new_screen_buffer(
                {.x = reg_1_value, .y = reg_2_value},
                memory.mem_buf.fetch_sprite_data(cpu.index_register.get_data(), value)));
          },
      },
      decode_list);
}
