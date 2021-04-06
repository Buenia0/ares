#include <cv/cv.hpp>

namespace velvet::ColecoVision {

PSG psg;
#include "serialization.cpp"

auto PSG::load(Node::Object parent) -> void {
  node = parent->append<Node::Component>("PSG");

  stream = node->append<Node::Stream>("PSG");
  stream->setChannels(1);
  stream->setFrequency(system.colorburst() / 16.0);
  stream->addHighPassFilter(20.0, 1);
}

auto PSG::unload() -> void {
  node = {};
  stream = {};
}

auto PSG::main() -> void {
  auto samples = SN76489::clock();
  stream->sample(samples[0]);
  step(1);
}

auto PSG::step(uint clocks) -> void {
  Thread::step(clocks);
  Thread::synchronize(cpu);
}

auto PSG::power() -> void {
  SN76489::power();
  Thread::create(system.colorburst() / 16.0, {&PSG::main, this});
}

}
