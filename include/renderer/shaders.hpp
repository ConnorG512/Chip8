#pragma once

namespace Chip8
{
// C++ 26 #embed uses C style arrays.
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p1967r14.html#design-familiar
//NOLINTBEGIN
const char basic_vertex[] = {
#embed "../../shaders/basic.vert"
};

const char basic_fragment[] = {
#embed "../../shaders/basic.frag"
};
//NOLINTEND
} // namespace Chip8
