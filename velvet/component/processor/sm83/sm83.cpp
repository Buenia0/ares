#include <velvet/velvet.hpp>
#include "sm83.hpp"

namespace velvet {

#include "registers.hpp"
#include "memory.cpp"
#include "algorithms.cpp"
#include "instruction.cpp"
#include "instructions.cpp"
#include "serialization.cpp"
#include "disassembler.cpp"

auto SM83::power() -> void {
  r = {};
}

}
