#include <velvet/velvet.hpp>
#include "arm7tdmi.hpp"

namespace velvet {

#include "registers.cpp"
#include "memory.cpp"
#include "algorithms.cpp"
#include "instruction.cpp"
#include "instructions-arm.cpp"
#include "instructions-thumb.cpp"
#include "serialization.cpp"
#include "disassembler.cpp"

ARM7TDMI::ARM7TDMI() {
  initialize();
}

auto ARM7TDMI::power() -> void {
  processor = {};
  processor.r15.modify = [&] { pipeline.reload = true; };
  pipeline = {};
  carry = 0;
  irq = 0;
  cpsr().f = 1;
  exception(PSR::SVC, 0x00);
}

auto ARM7TDMI::initialize() -> void {
  armInitialize();
  thumbInitialize();
}

auto ARM7TDMI::setThumb(bool isthumb) -> void {
  isThumbModeActive = isthumb;
  initialize();
}

}
