#include <md/md.hpp>

namespace velvet::MegaDrive {

PSG psg;
#include "serialization.cpp"

auto PSG::load(Node::Object parent) -> void {
  node = parent->append<Node::Component>("PSG");

  stream = node->append<Node::Stream>("PSG");
  stream->setChannels(1);
  stream->setFrequency(system.frequency() / 15.0 / 16.0);
  stream->addHighPassFilter(  20.0, 1);
  stream->addLowPassFilter (2840.0, 1);
}

auto PSG::unload() -> void {
  node = {};
  stream = {};
}

auto PSG::main() -> void {
  auto samples = SN76489::clock();
  stream->sample(samples[0] * 0.625);
  step(16);
}

auto PSG::step(uint clocks) -> void {
  Thread::step(clocks);
  Thread::synchronize(cpu, apu);
}

auto PSG::power(bool reset) -> void {
  SN76489::power();
  Thread::create(system.frequency() / 15.0, {&PSG::main, this});
}

}
